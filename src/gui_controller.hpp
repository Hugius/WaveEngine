#pragma once

#include "gui_manager.hpp"
#include "input_handler.hpp"
#include "waveform_generator.hpp"
#include "audio_player.hpp"
#include "audio_manager.hpp"

class GuiController final
{
public:
	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<WaveformGenerator> & waveformGenerator);
	void inject(const shared_ptr<AudioPlayer> & audioPlayer);
	void inject(const shared_ptr<AudioManager> & audioManager);
	void update();

private:
	void _updateMainMenu();
	void _updateWaveformMenu();

	static inline double AMPLITUDE_STEP = 1000.0;

	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<WaveformGenerator> _waveformGenerator = nullptr;
	shared_ptr<AudioPlayer> _audioPlayer = nullptr;
	shared_ptr<AudioManager> _audioManager = nullptr;

	double _sineAmplitude = 0.0f;
	double _squareAmplitude = 0.0f;
	double _triangleAmplitude = 0.0f;
	double _sawtoothAmplitude = 0.0f;
};