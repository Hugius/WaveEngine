#include "gui_controller.hpp"
#include "tools.hpp"

void GuiController::inject(const shared_ptr<GuiManager> guiManager)
{
	_guiManager = guiManager;
}

void GuiController::inject(const shared_ptr<WaveformGenerator> waveformGenerator)
{
	_waveformGenerator = waveformGenerator;
}

void GuiController::inject(const shared_ptr<AudioPlayer> audioPlayer)
{
	_audioPlayer = audioPlayer;
}

void GuiController::update()
{
	if(_guiManager->getElement("new")->isPressed())
	{

	}
	else if(_guiManager->getElement("load")->isPressed())
	{
		Tools::chooseWindowsExplorerFile(Tools::getRootDirectoryPath() + "projects\\", "wavproj");
	}
	else if(_guiManager->getElement("save")->isPressed())
	{

	}
	else if(_guiManager->getElement("waveforms")->isPressed())
	{
		//_audioPlayer->start(_waveformGenerator->generateSawtoothWave(1000, 30000, 30));

		_guiManager->getElement("waveforms_menu")->setVisible(true);
		_guiManager->getElement("waveforms_close")->setVisible(true);
		_guiManager->getElement("waveforms_100")->setVisible(true);
		_guiManager->getElement("waveforms_200")->setVisible(true);
		_guiManager->getElement("waveforms_300")->setVisible(true);
		_guiManager->getElement("waveforms_400")->setVisible(true);
		_guiManager->getElement("waveforms_500")->setVisible(true);
		_guiManager->getElement("waveforms_600")->setVisible(true);
		_guiManager->getElement("waveforms_700")->setVisible(true);
		_guiManager->getElement("waveforms_800")->setVisible(true);
		_guiManager->getElement("waveforms_900")->setVisible(true);
	}
	else if(_guiManager->getElement("exit")->isPressed())
	{
		exit(0);
	}
	else if(_guiManager->getElement("waveforms_close")->isPressed())
	{
		_guiManager->getElement("waveforms_menu")->setVisible(false);
		_guiManager->getElement("waveforms_close")->setVisible(false);
		_guiManager->getElement("waveforms_100")->setVisible(false);
		_guiManager->getElement("waveforms_200")->setVisible(false);
		_guiManager->getElement("waveforms_300")->setVisible(false);
		_guiManager->getElement("waveforms_400")->setVisible(false);
		_guiManager->getElement("waveforms_500")->setVisible(false);
		_guiManager->getElement("waveforms_600")->setVisible(false);
		_guiManager->getElement("waveforms_700")->setVisible(false);
		_guiManager->getElement("waveforms_800")->setVisible(false);
		_guiManager->getElement("waveforms_900")->setVisible(false);
	}
}