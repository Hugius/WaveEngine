#pragma warning(disable:6386)
#pragma warning(disable:6001)

#include "waveform_generator.hpp"
#include "mathematics.hpp"
#include "shared.hpp"

using std::make_shared;

const shared_ptr<Waveform> WaveformGenerator::_generateWaveform(const int duration, const int attack, const int release, const double amplitude, const double frequency, const WaveformType type) const
{
	if(duration < 1)
	{
		abort();
	}

	if(attack < 0.0)
	{
		abort();
	}

	if(attack > release)
	{
		abort();
	}

	if(attack > duration)
	{
		abort();
	}

	if(release < 0.0)
	{
		abort();
	}

	if(release < attack)
	{
		abort();
	}

	if(release > duration)
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
	const int durationSampleCount = duration * SAMPLES_PER_SECOND / 100;
	const int attackSampleCount = attack * SAMPLES_PER_SECOND / 100;
	const int releaseSampleCount = release * SAMPLES_PER_SECOND / 100;
	const int byteCount = duration * BYTES_PER_SECOND / 100;
	unsigned char * bytes = new unsigned char[byteCount];
	double time = 0.0;

	for(int index = 0; index < durationSampleCount; index++)
	{
		double envelope = 1.0;

		if(index + 1 < attackSampleCount)
		{
			envelope = static_cast<double>(index - 1) / static_cast<double>(attackSampleCount);
		}

		if(index + 1 > releaseSampleCount)
		{
			envelope = static_cast<double>(durationSampleCount - index - 1) / static_cast<double>(durationSampleCount - releaseSampleCount);
		}

		short sample;

		switch(type)
		{
			case WaveformType::SINE:
			{
				sample = static_cast<short>(envelope * amplitude * sin(2.0 * pi * frequency * time));

				break;
			}
			case WaveformType::SQUARE:
			{
				sample = static_cast<short>(envelope * amplitude * Mathematics::getSignum(sin(2.0 * pi * frequency * time)));

				break;
			}
			case WaveformType::TRIANGLE:
			{
				sample = static_cast<short>(envelope * amplitude * (1.0 - 4.0 * abs(round(frequency * time - 0.25) - (frequency * time - 0.25))));

				break;
			}
			case WaveformType::SAWTOOTH:
			{
				sample = static_cast<short>(envelope * amplitude * (2.0 * (frequency * time - floor(frequency * time + 0.5))));

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

const shared_ptr<Waveform> WaveformGenerator::_combineWaveforms(const vector<shared_ptr<Waveform>> & waveforms) const
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

const vector<double> WaveformGenerator::extractSamplesFromWaveform(const shared_ptr<Waveform> & waveform) const
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

const shared_ptr<Waveform> WaveformGenerator::generateWaveform(const shared_ptr<Tone> & tone) const
{
	if(tone == nullptr)
	{
		abort();
	}

	const shared_ptr<ToneTemplate> toneTemplate = tone->getToneTemplate();

	vector<shared_ptr<Waveform>> waveforms = {};

	for(int index = 0; index < Shared::OCTAVE_COUNT; index++)
	{
		const double frequency = NOTE_FREQUENCIES.at(tone->getNoteIndex()) * pow(2.0, static_cast<double>(index));

		if(toneTemplate->getSineToggles().at(index) && toneTemplate->getSineAmplitudes().at(index) != 0)
		{
			const double amplitude = static_cast<double>(toneTemplate->getSineAmplitudes().at(index)) * AMPLITUDE_STEP;
			const shared_ptr<Waveform> waveform = _generateWaveform(toneTemplate->getDuration(), toneTemplate->getAttack(), toneTemplate->getRelease(), amplitude, frequency, WaveformType::SINE);

			waveforms.push_back(waveform);
		}

		if(toneTemplate->getSquareToggles().at(index) && toneTemplate->getSquareAmplitudes().at(index) != 0)
		{
			const double amplitude = static_cast<double>(toneTemplate->getSquareAmplitudes().at(index)) * AMPLITUDE_STEP;
			const shared_ptr<Waveform> waveform = _generateWaveform(toneTemplate->getDuration(), toneTemplate->getAttack(), toneTemplate->getRelease(), amplitude, frequency, WaveformType::SQUARE);

			waveforms.push_back(waveform);
		}

		if(toneTemplate->getTriangleToggles().at(index) && toneTemplate->getTriangleAmplitudes().at(index) != 0)
		{
			const double amplitude = static_cast<double>(toneTemplate->getTriangleAmplitudes().at(index)) * AMPLITUDE_STEP;
			const shared_ptr<Waveform> waveform = _generateWaveform(toneTemplate->getDuration(), toneTemplate->getAttack(), toneTemplate->getRelease(), amplitude, frequency, WaveformType::TRIANGLE);

			waveforms.push_back(waveform);
		}

		if(toneTemplate->getSawtoothToggles().at(index) && toneTemplate->getSawtoothAmplitudes().at(index) != 0)
		{
			const double amplitude = static_cast<double>(toneTemplate->getSawtoothAmplitudes().at(index)) * AMPLITUDE_STEP;
			const shared_ptr<Waveform> waveform = _generateWaveform(toneTemplate->getDuration(), toneTemplate->getAttack(), toneTemplate->getRelease(), amplitude, frequency, WaveformType::SAWTOOTH);

			waveforms.push_back(waveform);
		}
	}

	if(waveforms.empty())
	{
		return nullptr;
	}

	return _combineWaveforms(waveforms);
}