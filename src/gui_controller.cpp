#include "gui_controller.hpp"
#include "tools.hpp"

using std::make_shared;

GuiController::GuiController()
{
	_waveformEditor = make_shared<WaveformMenu>();
}

void GuiController::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;

	_waveformEditor->inject(_guiManager);
}

void GuiController::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	_waveformEditor->inject(waveformGenerator);
}

void GuiController::inject(const shared_ptr<AudioPlayer> & audioPlayer)
{
	_waveformEditor->inject(audioPlayer);
}

void GuiController::inject(const shared_ptr<AudioManager> & audioManager)
{
	_waveformEditor->inject(audioManager);
}

void GuiController::update()
{
	if(_guiManager->getGuiButton("new")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("load")->isPressed())
	{
		Tools::chooseWindowsExplorerFile(Tools::getRootDirectoryPath() + "projects\\", "wavproj");
	}
	else if(_guiManager->getGuiButton("save")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("exit")->isPressed())
	{
		exit(0);
	}

	_waveformEditor->update();
}