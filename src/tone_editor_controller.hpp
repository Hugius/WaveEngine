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
	void update();
	void setGuiVisible(const bool value);
	void setEnabled(const bool value);
	void setTone(const shared_ptr<Tone> & tone);

private:
	void _updatePlaybackGui();
	void _updateOctaveGui();
	void _updateAmplitudeGui(const string & type, vector<int> & amplitudes);
	void _refreshWaveformVisualization();

	const vector<shared_ptr<Waveform>> _generateWaveforms(const int duration) const;

	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<WaveformGenerator> _waveformGenerator = nullptr;
	shared_ptr<WaveformPlayer> _waveformPlayer = nullptr;
	shared_ptr<Tone> _tone = nullptr;

	bool _isEnabled = false;
};