#pragma once

#include "waveform.hpp"

#include <memory>
#include <string>
#include <unordered_map>

using std::shared_ptr;
using std::string;
using std::unordered_map;

class WaveformManager final
{
public:
	void addWaveform(const string & id, const shared_ptr<Waveform> & waveform);

	const shared_ptr<Waveform> & getWaveform(const string & id) const;
	const unordered_map<string, shared_ptr<Waveform>> & getWaveforms() const;

private:
	const bool _isWaveformExisting(const string & id) const;

	unordered_map<string, shared_ptr<Waveform>> _waveforms = {};
};