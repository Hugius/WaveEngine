#pragma warning(disable:6386)
#pragma warning(disable:6001)

#include "waveform_generator.hpp"
#include "mathematics.hpp"
#include "tone_constants.hpp"

using std::make_shared;

const shared_ptr<Waveform> WaveformGenerator::_generateSineWaveform(const int duration, const double amplitude, const double frequency) const
{
	return _generateWaveform(duration, amplitude, frequency, WaveformType::SINE);
}

const shared_ptr<Waveform> WaveformGenerator::_generateSquareWaveform(const int duration, const double amplitude, const double frequency) const
{
	return _generateWaveform(duration, amplitude, frequency, WaveformType::SQUARE);
}

const shared_ptr<Waveform> WaveformGenerator::_generateTriangleWaveform(const int duration, const double amplitude, const double frequency) const
{
	return _generateWaveform(duration, amplitude, frequency, WaveformType::TRIANGLE);
}

const shared_ptr<Waveform> WaveformGenerator::_generateSawtoothWaveform(const int duration, const double amplitude, const double frequency) const
{
	return _generateWaveform(duration, amplitude, frequency, WaveformType::SAWTOOTH);
}

const shared_ptr<Waveform> WaveformGenerator::_generateWaveform(const int duration, const double amplitude, const double frequency, const WaveformType type) const
{
	if(duration < 10)
	{
		abort();
	}

	if(amplitude < 0.0)
	{
		abort();
	}

	if(frequency < 0.0)
	{
		abort();
	}

	const double pi = Mathematics::getPi();
	const double delta = 1.0 / static_cast<double>(SAMPLES_PER_SECOND);
	const int sampleCount = duration * SAMPLES_PER_SECOND / 100;
	const int byteCount = duration * BYTES_PER_SECOND / 100;
	unsigned char * bytes = new unsigned char[byteCount];
	double time = 0.0;

	for(int index = 0; index < sampleCount; index++)
	{
		short sample;
		switch(type)
		{
			case WaveformType::SINE:
			{
				sample = static_cast<short>(amplitude * sin(2.0 * pi * frequency * time));

				break;
			}
			case WaveformType::SQUARE:
			{
				sample = static_cast<short>(amplitude * Mathematics::getSignum(sin(2.0 * pi * frequency * time)));

				break;
			}
			case WaveformType::TRIANGLE:
			{
				sample = static_cast<short>(amplitude * (1.0 - 4.0 * abs(round(frequency * time - 0.25) - (frequency * time - 0.25))));

				break;
			}
			case WaveformType::SAWTOOTH:
			{
				sample = static_cast<short>(amplitude * (2.0 * (frequency * time - floor(frequency * time + 0.5))));

				break;
			}
		}

		const unsigned char firstByte = static_cast<unsigned char>(sample);
		const unsigned char secondByte = static_cast<unsigned char>(sample >> 8);
		const int byteIndex = index * BYTES_PER_BLOCK;

		bytes[byteIndex + 0] = firstByte;  // L
		bytes[byteIndex + 1] = secondByte; // L
		bytes[byteIndex + 2] = firstByte;  // R
		bytes[byteIndex + 3] = secondByte; // R

		time += delta;
	}

	return make_shared<Waveform>(bytes, byteCount, CHANNEL_COUNT, SAMPLES_PER_SECOND, BYTES_PER_SECOND, BYTES_PER_BLOCK, BITS_PER_SAMPLE);
}

const shared_ptr<Waveform> WaveformGenerator::combineWaveforms(const vector<shared_ptr<Waveform>> & waveforms) const
{
	if(waveforms.empty())
	{
		abort();
	}

	for(const shared_ptr<Waveform> & waveform : waveforms)
	{
		if(waveform == nullptr)
		{
			abort();
		}

		if(waveform->getHeader()->dwBufferLength != waveforms.front()->getHeader()->dwBufferLength)
		{
			abort();
		}
	}

	const int byteCount = waveforms.front()->getHeader()->dwBufferLength;
	const int sampleCount = byteCount / BYTES_PER_BLOCK;
	unsigned char * bytes = new unsigned char[byteCount];

	for(int index = 0; index < sampleCount; index++)
	{
		const int byteIndex = index * BYTES_PER_BLOCK;
		short newBytePair = 0;

		for(const shared_ptr<Waveform> & waveform : waveforms)
		{
			const unsigned char firstByte = waveform->getHeader()->lpData[byteIndex + 0];
			const unsigned char secondByte = waveform->getHeader()->lpData[byteIndex + 1];
			const short bytePair = static_cast<short>(firstByte | secondByte << 8);

			newBytePair += bytePair;
		}

		const unsigned char newFirstByte = static_cast<unsigned char>(newBytePair);
		const unsigned char newSecondByte = static_cast<unsigned char>(newBytePair >> 8);

		bytes[byteIndex + 0] = newFirstByte;  // L
		bytes[byteIndex + 1] = newSecondByte; // L
		bytes[byteIndex + 2] = newFirstByte;  // R
		bytes[byteIndex + 3] = newSecondByte; // R
	}

	return make_shared<Waveform>(bytes, byteCount, CHANNEL_COUNT, SAMPLES_PER_SECOND, BYTES_PER_SECOND, BYTES_PER_BLOCK, BITS_PER_SAMPLE);
}

const vector<double> WaveformGenerator::extractSamplesFromWaveform(const shared_ptr<Waveform> & waveform)
{
	if(waveform == nullptr)
	{
		abort();
	}

	const int sampleCount = static_cast<int>(waveform->getHeader()->dwBufferLength / BYTES_PER_BLOCK);

	vector<double> samples = {};

	for(int index = 0; index < sampleCount; index++)
	{
		const int byteIndex = index * BYTES_PER_BLOCK;
		const unsigned char firstByte = waveform->getHeader()->lpData[byteIndex + 0]; // L
		const unsigned char secondByte = waveform->getHeader()->lpData[byteIndex + 1]; // L
		const short bytePair = static_cast<short>(firstByte | secondByte << 8);

		samples.push_back(static_cast<double>(bytePair));
	}

	return samples;
}

const vector<shared_ptr<Waveform>> WaveformGenerator::generateWaveforms(const shared_ptr<Tone> & tone) const
{
	if(tone == nullptr)
	{
		abort();
	}

	const shared_ptr<ToneTemplate> toneTemplate = tone->getToneTemplate();

	vector<shared_ptr<Waveform>> waveforms = {};

	for(int index = 0; index < ToneConstants::OCTAVE_COUNT; index++)
	{
		const double frequency = ToneConstants::NOTE_FREQUENCIES.at(tone->getNoteIndex()) * pow(2.0, static_cast<double>(index));

		if(toneTemplate->sineToggles.at(index) && toneTemplate->sineAmplitudes.at(index) != 0)
		{
			const double amplitude = static_cast<double>(toneTemplate->sineAmplitudes.at(index)) * ToneConstants::AMPLITUDE_STEP;
			const shared_ptr<Waveform> waveform = _generateSineWaveform(toneTemplate->duration, amplitude, frequency);

			waveforms.push_back(waveform);
		}

		if(toneTemplate->squareToggles.at(index) && toneTemplate->squareAmplitudes.at(index) != 0)
		{
			const double amplitude = static_cast<double>(toneTemplate->squareAmplitudes.at(index)) * ToneConstants::AMPLITUDE_STEP;
			const shared_ptr<Waveform> waveform = _generateSquareWaveform(toneTemplate->duration, amplitude, frequency);

			waveforms.push_back(waveform);
		}

		if(toneTemplate->triangleToggles.at(index) && toneTemplate->triangleAmplitudes.at(index) != 0)
		{
			const double amplitude = static_cast<double>(toneTemplate->triangleAmplitudes.at(index)) * ToneConstants::AMPLITUDE_STEP;
			const shared_ptr<Waveform> waveform = _generateTriangleWaveform(toneTemplate->duration, amplitude, frequency);

			waveforms.push_back(waveform);
		}

		if(toneTemplate->sawtoothToggles.at(index) && toneTemplate->sawtoothAmplitudes.at(index) != 0)
		{
			const double amplitude = static_cast<double>(toneTemplate->sawtoothAmplitudes.at(index)) * ToneConstants::AMPLITUDE_STEP;
			const shared_ptr<Waveform> waveform = _generateSawtoothWaveform(toneTemplate->duration, amplitude, frequency);

			waveforms.push_back(waveform);
		}
	}

	return waveforms;
}