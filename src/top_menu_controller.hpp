#pragma once

#include "tone_editor_controller.hpp"

class TopMenuController final
{
public:
	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<ToneTemplateManager> & toneTemplateManager);
	void inject(const shared_ptr<ToneEditorController> & toneEditorController);
	void update();

private:
	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<ToneTemplateManager> _toneTemplateManager = nullptr;
	shared_ptr<ToneEditorController> _toneEditorController = nullptr;
};