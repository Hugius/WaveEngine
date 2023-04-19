#pragma once

#include "tone_editor_controller.hpp"

using std::unique_ptr;

class TopMenuController final
{
public:
	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<ToneManager> & toneManager);
	void inject(const shared_ptr<ToneEditorController> & toneEditorController);
	void update();

private:
	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<ToneManager> _toneManager = nullptr;
	shared_ptr<ToneEditorController> _toneEditorController = nullptr;

	int _currentToneIndex = -1;
};