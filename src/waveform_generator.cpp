#pragma warning(disable:6386)
#pragma warning(disable:6001)

#include "waveform_generator.hpp"
#include "mathematics.hpp"
#include "audio_constants.hpp"

using std::make_shared;

const shared_ptr<Audio> WaveformGenerator::generateSineWave(const int duration, const double amplitude, const double frequency) const
{
	return _generateSoundWave(duration, amplitude, frequency, WaveformType::SINE);
}

const shared_ptr<Audio> WaveformGenerator::generateSquareWave(const int duration, const double amplitude, const double frequency) const
{
	return _generateSoundWave(duration, amplitude, frequency, WaveformType::SQUARE);
}

const shared_ptr<Audio> WaveformGenerator::generateTriangleWave(const int duration, const double amplitude, const double frequency) const
{
	return _generateSoundWave(duration, amplitude, frequency, WaveformType::TRIANGLE);
}

const shared_ptr<Audio> WaveformGenerator::generateSawtoothWave(const int duration, const double amplitude, const double frequency) const
{
	return _generateSoundWave(duration, amplitude, frequency, WaveformType::SAWTOOTH);
}

const shared_ptr<Audio> WaveformGenerator::_generateSoundWave(const int duration, const double amplitude, const double frequency, const WaveformType type) const
{
	if(duration < AudioConstants::MIN_DURATION || duration > AudioConstants::MAX_DURATION)
	{
		abort();
	}

	if(amplitude < AudioConstants::MIN_AMPLITUDE || amplitude > AudioConstants::MAX_AMPLITUDE)
	{
		abort();
	}

	if(frequency < AudioConstants::MIN_FREQUENCY || frequency > AudioConstants::MAX_FREQUENCY)
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
				sample = static_cast<short>(amplitude * sinf(2.0 * pi * frequency * time));

				break;
			}
			case WaveformType::SQUARE:
			{
				sample = static_cast<short>(amplitude * Mathematics::getSignum(sinf(2.0 * pi * frequency * time)));

				break;
			}
			case WaveformType::TRIANGLE:
			{
				sample = static_cast<short>(amplitude * (1.0 - 4.0 * fabsf(roundf(frequency * time - 0.25) - (frequency * time - 0.25))));

				break;
			}
			case WaveformType::SAWTOOTH:
			{
				sample = static_cast<short>(amplitude * (2.0 * (frequency * time - floorf(frequency * time + 0.5))));

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

	return make_shared<Audio>(bytes, byteCount, CHANNEL_COUNT, SAMPLES_PER_SECOND, BYTES_PER_SECOND, BYTES_PER_BLOCK, BITS_PER_SAMPLE);
}

const shared_ptr<Audio> WaveformGenerator::combineSoundWaves(const vector<shared_ptr<Audio>> & soundWaves) const
{
	if(soundWaves.empty())
	{
		abort();
	}

	for(const shared_ptr<Audio> & soundWave : soundWaves)
	{
		if(soundWave->getHeader()->dwBufferLength != soundWaves[0]->getHeader()->dwBufferLength)
		{
			abort();
		}
	}

	const int byteCount = soundWaves[0]->getHeader()->dwBufferLength;
	const int sampleCount = byteCount / BYTES_PER_BLOCK;
	unsigned char * bytes = new unsigned char[byteCount];

	for(int index = 0; index < sampleCount; index++)
	{
		const int byteIndex = index * BYTES_PER_BLOCK;
		short newBytePair = 0;

		for(const shared_ptr<Audio> & soundWave : soundWaves)
		{
			const unsigned char firstByte = soundWave->getHeader()->lpData[byteIndex + 0];
			const unsigned char secondByte = soundWave->getHeader()->lpData[byteIndex + 1];
			const short bytePair = static_cast<short>(firstByte) | static_cast<short>(secondByte) << 8;

			newBytePair += bytePair;
		}

		const unsigned char newFirstByte = static_cast<unsigned char>(newBytePair);
		const unsigned char newSecondByte = static_cast<unsigned char>(newBytePair >> 8);

		bytes[byteIndex + 0] = newFirstByte;  // L
		bytes[byteIndex + 1] = newSecondByte; // L
		bytes[byteIndex + 2] = newFirstByte;  // R
		bytes[byteIndex + 3] = newSecondByte; // R
	}

	return make_shared<Audio>(bytes, byteCount, CHANNEL_COUNT, SAMPLES_PER_SECOND, BYTES_PER_SECOND, BYTES_PER_BLOCK, BITS_PER_SAMPLE);
}