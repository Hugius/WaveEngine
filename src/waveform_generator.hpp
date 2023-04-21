#pragma once

#include "waveform.hpp"
#include "waveform_type.hpp"
#include "tone.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class WaveformGenerator final
{
public:
	const vector<shared_ptr<Waveform>> generateWaveforms(const shared_ptr<Tone> & tone, const int duration) const;
	const vector<double> extractSamplesFromWaveform(const shared_ptr<Waveform> & waveform);

	const shared_ptr<Waveform> combineWaveforms(const vector<shared_ptr<Waveform>> & waveforms) const;

private:
	const shared_ptr<Waveform> _generateWaveform(const int duration, const double amplitude, const double frequency, const WaveformType type) const;
	const shared_ptr<Waveform> _generateSineWaveform(const int duration, const double amplitude, const double frequency) const;
	const shared_ptr<Waveform> _generateSquareWaveform(const int duration, const double amplitude, const double frequency) const;
	const shared_ptr<Waveform> _generateTriangleWaveform(const int duration, const double amplitude, const double frequency) const;
	const shared_ptr<Waveform> _generateSawtoothWaveform(const int duration, const double amplitude, const double frequency) const;

	static inline const int CHANNEL_COUNT = 2;
	static inline const int SAMPLES_PER_SECOND = 44100;
	static inline const int BYTES_PER_SECOND = 176400;
	static inline const int BYTES_PER_BLOCK = 4;
	static inline const int BITS_PER_SAMPLE = 16;
};