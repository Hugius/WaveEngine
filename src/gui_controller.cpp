#include "gui_controller.hpp"
#include "tools.hpp"

using std::make_unique;

GuiController::GuiController()
	:
	_toneMenu(make_unique<ToneMenu>())
{

}

void GuiController::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;

	_toneMenu->inject(_guiManager);
}

void GuiController::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	_toneMenu->inject(waveformGenerator);
}

void GuiController::inject(const shared_ptr<WaveformPlayer> & waveformPlayer)
{
	_toneMenu->inject(waveformPlayer);
}

void GuiController::inject(const shared_ptr<WaveformManager> & waveformManager)
{
	_toneMenu->inject(waveformManager);
}

void GuiController::update()
{
	if(_guiManager->getGuiButton("main_menu_new")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("main_menu_load")->isPressed())
	{
		Tools::chooseWindowsExplorerFile(Tools::getRootDirectoryPath() + "projects\\", "wavproj");
	}
	else if(_guiManager->getGuiButton("main_menu_save")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("main_menu_waveform")->isPressed())
	{
		_toneMenu->setGuiVisible(true);
		_toneMenu->setEnabled(true);
	}
	else if(_guiManager->getGuiButton("main_menu_export")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("main_menu_exit")->isPressed())
	{
		exit(0);
	}

	_toneMenu->update();
}