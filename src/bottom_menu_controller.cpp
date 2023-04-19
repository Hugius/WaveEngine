#include "bottom_menu_controller.hpp"

void BottomMenuController::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;
}

void BottomMenuController::inject(const shared_ptr<ToneManager> & toneManager)
{
	_toneManager = toneManager;
}

void BottomMenuController::update()
{
	if(_guiManager->getGuiButton("bottom_menu_create")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("bottom_menu_delete")->isPressed())
	{

	}
}