#pragma once

#include "gui_manager.hpp"
#include "waveform_generator.hpp"
#include "audio_player.hpp"
#include "audio_manager.hpp"

class WaveformMenu final
{
public:
	WaveformMenu();

	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<WaveformGenerator> & waveformGenerator);
	void inject(const shared_ptr<AudioPlayer> & audioPlayer);
	void inject(const shared_ptr<AudioManager> & audioManager);
	void update();

private:
	void _updatePlayback();
	void _updateNotes();
	void _setGuiVisible(const bool value);
	void _refreshWaveformVisualization();

	const vector<shared_ptr<Audio>> _generateWaveforms(const int duration) const;

	static inline const double OCTAVE_AMPLITUDE_STEP = 1000.0;

	vector<int> _sineAmplitudes = {};
	vector<int> _squareAmplitudes = {};
	vector<int> _triangleAmplitudes = {};
	vector<int> _sawtoothAmplitudes = {};

	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<WaveformGenerator> _waveformGenerator = nullptr;
	shared_ptr<AudioPlayer> _audioPlayer = nullptr;
	shared_ptr<AudioManager> _audioManager = nullptr;

	int _octave = 4;

	bool _isEnabled = false;
};