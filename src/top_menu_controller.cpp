#include "top_menu_controller.hpp"
#include "tools.hpp"

void TopMenuController::update()
{
	if(_guiManager->getGuiButton("top_menu_new")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("top_menu_load")->isPressed())
	{
		Tools::chooseWindowsExplorerFile(Tools::getRootDirectoryPath() + "projects\\", "wavproj");
	}
	else if(_guiManager->getGuiButton("top_menu_tone")->isPressed())
	{
		_toneEditorController->enable();
	}
	else if(_guiManager->getGuiButton("top_menu_export")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("top_menu_exit")->isPressed())
	{
		exit(0);
	}

	const int toneCount = _toneTemplateManager->getToneTemplateCount();

	_guiManager->getGuiButton("top_menu_tone")->setHoverable(toneCount != 0);
	_guiManager->getGuiButton("top_menu_tone")->setPressable(toneCount != 0);
}

void TopMenuController::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;
}

void TopMenuController::inject(const shared_ptr<ToneTemplateManager> & toneTemplateManager)
{
	_toneTemplateManager = toneTemplateManager;
}

void TopMenuController::inject(const shared_ptr<ToneEditorController> & toneEditorController)
{
	_toneEditorController = toneEditorController;
}