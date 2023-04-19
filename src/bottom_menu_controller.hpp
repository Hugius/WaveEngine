#pragma once

#include "tone_editor_controller.hpp"

using std::unique_ptr;

class BottomMenuController final
{
public:
	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<ToneManager> & toneManager);
	void update();

private:
	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<ToneManager> _toneManager = nullptr;
};