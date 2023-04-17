#pragma once

#include "gui_manager.hpp"
#include "waveform_generator.hpp"
#include "waveform_player.hpp"
#include "waveform_manager.hpp"

class ToneMenu final
{
public:
	ToneMenu();

	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<WaveformGenerator> & waveformGenerator);
	void inject(const shared_ptr<WaveformPlayer> & waveformPlayer);
	void inject(const shared_ptr<WaveformManager> & waveformManager);
	void update();
	void setGuiVisible(const bool value);
	void setEnabled(const bool value);

private:
	void _updatePlaybackGui();
	void _updateOctaveGui();
	void _updateAmplitudeGui(const string & type, vector<int> & amplitudes);
	void _refreshWaveformVisualization();

	const vector<shared_ptr<Waveform>> _generateWaveforms(const int duration) const;

	static inline const double OCTAVE_AMPLITUDE_STEP = 1000.0;

	vector<int> _sineAmplitudes = {};
	vector<int> _squareAmplitudes = {};
	vector<int> _triangleAmplitudes = {};
	vector<int> _sawtoothAmplitudes = {};

	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<WaveformGenerator> _waveformGenerator = nullptr;
	shared_ptr<WaveformPlayer> _waveformPlayer = nullptr;
	shared_ptr<WaveformManager> _waveformManager = nullptr;

	int _octave = 0;

	bool _isEnabled = false;
};