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
	const vector<double> extractSamplesFromWaveform(const shared_ptr<Waveform> & waveform);

	const shared_ptr<Waveform> generateWaveform(const shared_ptr<Tone> & tone) const;

private:
	const shared_ptr<Waveform> _generateWaveform(const int duration, const int release, const double amplitude, const double frequency, const WaveformType type) const;
	const shared_ptr<Waveform> _generateSineWaveform(const int duration, const int release, const double amplitude, const double frequency) const;
	const shared_ptr<Waveform> _generateSquareWaveform(const int duration, const int release, const double amplitude, const double frequency) const;
	const shared_ptr<Waveform> _generateTriangleWaveform(const int duration, const int release, const double amplitude, const double frequency) const;
	const shared_ptr<Waveform> _generateSawtoothWaveform(const int duration, const int release, const double amplitude, const double frequency) const;
	const shared_ptr<Waveform> _combineWaveforms(const vector<shared_ptr<Waveform>> & waveforms) const;

	static inline const array<double, SharedConstants::NOTE_COUNT> NOTE_FREQUENCIES = {16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87};

	static inline const double AMPLITUDE_STEP = 1000.0;

	static inline const int CHANNEL_COUNT = 2;
	static inline const int SAMPLES_PER_SECOND = 44100;
	static inline const int BYTES_PER_SECOND = 176400;
	static inline const int BYTES_PER_BLOCK = 4;
	static inline const int BITS_PER_SAMPLE = 16;
};