#pragma once

#include "waveform_menu.hpp"

using std::unique_ptr;

class GuiController final
{
public:
	GuiController();

	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<WaveformGenerator> & waveformGenerator);
	void inject(const shared_ptr<WaveformPlayer> & waveformPlayer);
	void inject(const shared_ptr<WaveformManager> & waveformManager);
	void update();

private:
	const unique_ptr<WaveformMenu> _waveformMenu;

	shared_ptr<GuiManager> _guiManager = nullptr;
};