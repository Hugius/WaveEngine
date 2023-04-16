#include "gui_controller.hpp"
#include "tools.hpp"

using std::make_unique;

GuiController::GuiController()
	:
	_waveformMenu(make_unique<WaveformMenu>())
{

}

void GuiController::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;

	_waveformMenu->inject(_guiManager);
}

void GuiController::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	_waveformMenu->inject(waveformGenerator);
}

void GuiController::inject(const shared_ptr<AudioPlayer> & audioPlayer)
{
	_waveformMenu->inject(audioPlayer);
}

void GuiController::inject(const shared_ptr<AudioManager> & audioManager)
{
	_waveformMenu->inject(audioManager);
}

void GuiController::update()
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
	else if(_guiManager->getGuiButton("top_menu_waveform")->isPressed())
	{
		_waveformMenu->setGuiVisible(true);
		_waveformMenu->setEnabled(true);
	}
	else if(_guiManager->getGuiButton("top_menu_export")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("top_menu_exit")->isPressed())
	{
		exit(0);
	}

	_waveformMenu->update();
}