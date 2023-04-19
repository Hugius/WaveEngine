#pragma once

#include "tone_editor.hpp"

using std::unique_ptr;

class TopMenuController final
{
public:
	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<ToneManager> & toneManager);
	void inject(const shared_ptr<ToneEditor> & toneEditor);
	void update();

private:
	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<ToneManager> _toneManager = nullptr;
	shared_ptr<ToneEditor> _toneEditor = nullptr;

	int _currentToneIndex = -1;
};