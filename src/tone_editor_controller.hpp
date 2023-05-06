#pragma once

#include "gui_manager.hpp"
#include "waveform_generator.hpp"
#include "waveform_player.hpp"
#include "tone_template_manager.hpp"

#include <array>

using std::array;

class ToneEditorController final
{
public:
	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<WaveformGenerator> & waveformGenerator);
	void inject(const shared_ptr<WaveformPlayer> & waveformPlayer);
	void inject(const shared_ptr<ToneTemplateManager> & toneTemplateManager);
	void update();
	void enable();

private:
	void _updateNoteGui();
	void _updateDurationGui();
	void _updateAmplitudeGui(const string & type, array<int, ToneConstants::OCTAVE_COUNT> & amplitudes, array<bool, ToneConstants::OCTAVE_COUNT> & toggles);
	void _refreshWaveformVisualization();
	void _setGuiVisible(const bool value);

	static inline const int MIN_DURATION = 10;
	static inline const int MAX_DURATION = 500;
	static inline const int DURATION_STEP = 10;

	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<WaveformGenerator> _waveformGenerator = nullptr;
	shared_ptr<WaveformPlayer> _waveformPlayer = nullptr;
	shared_ptr<ToneTemplateManager> _toneTemplateManager = nullptr;

	bool _isEnabled = false;
};