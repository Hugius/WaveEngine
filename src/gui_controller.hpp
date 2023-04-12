#pragma once

#include "waveform_menu.hpp"

using std::unique_ptr;

class GuiController final
{
public:
	GuiController();

	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<WaveformGenerator> & waveformGenerator);
	void inject(const shared_ptr<AudioPlayer> & audioPlayer);
	void inject(const shared_ptr<AudioManager> & audioManager);
	void update();

private:
	unique_ptr<WaveformMenu> _waveformMenu = nullptr;
	shared_ptr<GuiManager> _guiManager = nullptr;
};