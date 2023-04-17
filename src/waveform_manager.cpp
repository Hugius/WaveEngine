#include "waveform_manager.hpp"

void WaveformManager::addWaveform(const string & id, const shared_ptr<Waveform> & waveform)
{
	if(_isWaveformExisting(id))
	{
		abort();
	}

	_waveforms.insert({id, waveform});
}

const shared_ptr<Waveform> & WaveformManager::getWaveform(const string & id) const
{
	if(!_isWaveformExisting(id))
	{
		abort();
	}

	return _waveforms.at(id);
}

const unordered_map<string, shared_ptr<Waveform>> & WaveformManager::getWaveforms() const
{
	return _waveforms;
}

const bool WaveformManager::_isWaveformExisting(const string & id) const
{
	return _waveforms.find(id) != _waveforms.end();
}