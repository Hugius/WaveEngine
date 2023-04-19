#include "bottom_menu_controller.hpp"

using std::make_shared;

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
		_toneManager->addTone(make_shared<Tone>());
	}
	else if(_guiManager->getGuiButton("bottom_menu_delete")->isPressed())
	{

	}
}