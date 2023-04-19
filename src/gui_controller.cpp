#include "gui_controller.hpp"
#include "tools.hpp"

using std::make_unique;

GuiController::GuiController()
	:
	_toneEditor(make_unique<ToneEditor>())
{

}

void GuiController::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;

	_toneEditor->inject(_guiManager);
}

void GuiController::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	_toneEditor->inject(waveformGenerator);
}

void GuiController::inject(const shared_ptr<WaveformPlayer> & waveformPlayer)
{
	_toneEditor->inject(waveformPlayer);
}

void GuiController::inject(const shared_ptr<ToneManager> & toneManager)
{
	_toneEditor->inject(toneManager);
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
	else if(_guiManager->getGuiButton("main_menu_tone")->isPressed())
	{
		_toneEditor->setGuiVisible(true);
		_toneEditor->setEnabled(true);
	}
	else if(_guiManager->getGuiButton("main_menu_export")->isPressed())
	{

	}
	else if(_guiManager->getGuiButton("main_menu_exit")->isPressed())
	{
		exit(0);
	}

	_toneEditor->update();
}