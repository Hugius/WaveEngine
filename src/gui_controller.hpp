#pragma once

#include "gui_manager.hpp"
#include "input_handler.hpp"
#include "waveform_generator.hpp"
#include "audio_player.hpp"

class GuiController final
{
public:
	void inject(const shared_ptr<GuiManager> guiManager);
	void inject(const shared_ptr<WaveformGenerator> waveformGenerator);
	void inject(const shared_ptr<AudioPlayer> audioPlayer);
	void update();

private:
	void _updateMainMenu();
	void _updateWaveformMenu();

	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<WaveformGenerator> _waveformGenerator = nullptr;
	shared_ptr<AudioPlayer> _audioPlayer = nullptr;

	float _sineAmplitude = 0.0f;
	float _squareAmplitude = 0.0f;
	float _triangleAmplitude = 0.0f;
	float _sawtoothAmplitude = 0.0f;
};