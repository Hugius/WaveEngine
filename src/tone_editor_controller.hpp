#pragma once

#include "gui_manager.hpp"
#include "waveform_generator.hpp"
#include "waveform_player.hpp"
#include "tone_manager.hpp"

class ToneEditorController final
{
public:
	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<WaveformGenerator> & waveformGenerator);
	void inject(const shared_ptr<WaveformPlayer> & waveformPlayer);
	void inject(const shared_ptr<ToneManager> & toneManager);
	void update();
	void enable();

private:
	void _updatePlaybackGui();
	void _updateAmplitudeGui(const string & type, vector<int> & amplitudes, vector<bool> & toggles);
	void _refreshWaveformVisualization();
	void _setGuiVisible(const bool value);

	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<WaveformGenerator> _waveformGenerator = nullptr;
	shared_ptr<WaveformPlayer> _waveformPlayer = nullptr;
	shared_ptr<ToneManager> _toneManager = nullptr;

	bool _isEnabled = false;
};