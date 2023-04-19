#include "top_menu_controller.hpp"
#include "tools.hpp"

using std::make_unique;

void TopMenuController::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;
}

void TopMenuController::inject(const shared_ptr<ToneManager> & toneManager)
{
	_toneManager = toneManager;
}

void TopMenuController::inject(const shared_ptr<ToneEditor> & toneEditor)
{
	_toneEditor = toneEditor;
}

void TopMenuController::update()
{
	if(_guiManager->getGuiButton("top_menu_new")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("top_menu_load")->isPressed())
	{
		Tools::chooseWindowsExplorerFile(Tools::getRootDirectoryPath() + "projects\\", "wavproj");
	}
	else if(_guiManager->getGuiButton("top_menu_save")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("top_menu_tone")->isPressed())
	{
		_toneEditor->setGuiVisible(true);
		_toneEditor->setEnabled(true);
	}
	else if(_guiManager->getGuiButton("top_menu_export")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("top_menu_exit")->isPressed())
	{
		exit(0);
	}

	_toneEditor->update();

	_guiManager->getGuiButton("top_menu_tone")->setHoverable(_currentToneIndex != -1);

	if(_guiManager->getGuiButton("bottom_menu_create")->isPressed())
	{

	}
}