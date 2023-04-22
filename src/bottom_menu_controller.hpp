#pragma once

#include "tone_editor_controller.hpp"

using std::unique_ptr;

class BottomMenuController final
{
public:
	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<ToneManager> & toneManager);
	void inject(const shared_ptr<WaveformGenerator> & waveformGenerator);
	void update();

private:
	void _refreshWaveformVisualization();

	static inline const int MAX_TONES = 99;

	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<ToneManager> _toneManager = nullptr;
	shared_ptr<WaveformGenerator> _waveformGenerator = nullptr;
};