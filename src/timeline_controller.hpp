#pragma once

#include "gui_manager.hpp"
#include "waveform_generator.hpp"
#include "waveform_player.hpp"
#include "tone_template_manager.hpp"
#include "tone_manager.hpp"

#include <array>

using std::array;

class TimelineController final
{
public:
	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<ToneTemplateManager> & toneTemplateManager);
	void inject(const shared_ptr<WaveformGenerator> & waveformGenerator);
	void inject(const shared_ptr<ToneManager> & toneManager);
	void update();

private:
	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<ToneTemplateManager> _toneTemplateManager = nullptr;
	shared_ptr<WaveformGenerator> _waveformGenerator = nullptr;
	shared_ptr<ToneManager> _toneManager = nullptr;

	bool _isEnabled = false;
};