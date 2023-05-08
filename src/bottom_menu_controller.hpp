#pragma once

#include "tone_editor_controller.hpp"

class BottomMenuController final
{
public:
	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<ToneTemplateManager> & toneTemplateManager);
	void inject(const shared_ptr<WaveformGenerator> & waveformGenerator);
	void update();

private:
	void _refreshWaveformVisualization();

	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<ToneTemplateManager> _toneTemplateManager = nullptr;
	shared_ptr<WaveformGenerator> _waveformGenerator = nullptr;
};