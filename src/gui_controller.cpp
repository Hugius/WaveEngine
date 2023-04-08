#include "gui_controller.hpp"
#include "tools.hpp"
#include "audio_constants.hpp"

using std::to_string;

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

void GuiController::inject(const shared_ptr<AudioManager> audioManager)
{
	_audioManager = audioManager;
}

void GuiController::update()
{
	_updateMainMenu();
	_updateWaveformMenu();
}

void GuiController::_updateMainMenu()
{
	if(_guiManager->getGuiElement("new")->isPressed())
	{

	}
	else if(_guiManager->getGuiElement("load")->isPressed())
	{
		Tools::chooseWindowsExplorerFile(Tools::getRootDirectoryPath() + "projects\\", "wavproj");
	}
	else if(_guiManager->getGuiElement("save")->isPressed())
	{

	}
	else if(_guiManager->getGuiElement("waveforms")->isPressed())
	{
		_guiManager->getGuiElement("waveforms_menu")->setVisible(true);
		_guiManager->getGuiElement("waveforms_close")->setVisible(true);
		_guiManager->getGuiElement("waveforms_play")->setVisible(true);

		for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
		{
			_guiManager->getGuiElement("waveforms_sin" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_sqr" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_tri" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_saw" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_note" + to_string(index))->setVisible(true);
		}
	}
	else if(_guiManager->getGuiElement("exit")->isPressed())
	{
		exit(0);
	}
}

void GuiController::_updateWaveformMenu()
{
	if(_guiManager->getGuiElement("waveforms_close")->isPressed())
	{
		_guiManager->getGuiElement("waveforms_menu")->setVisible(false);
		_guiManager->getGuiElement("waveforms_close")->setVisible(false);
		_guiManager->getGuiElement("waveforms_play")->setVisible(false);

		for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
		{
			_guiManager->getGuiElement("waveforms_sin" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_sqr" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_tri" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_saw" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_note" + to_string(index))->setVisible(false);
		}
	}
	else if(_guiManager->getGuiElement("waveforms_play")->isPressed())
	{
		vector<shared_ptr<Audio>> soundWaves = {};

		for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
		{
			if(_guiManager->getGuiElement("waveforms_sin" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateSineWave(10000, 5000, AudioConstants::NOTE_FREQUENCIES[index]));
			}
			if(_guiManager->getGuiElement("waveforms_sqr" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateSquareWave(10000, 5000, AudioConstants::NOTE_FREQUENCIES[index]));
			}
			if(_guiManager->getGuiElement("waveforms_tri" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateTriangleWave(10000, 5000, AudioConstants::NOTE_FREQUENCIES[index]));
			}
			if(_guiManager->getGuiElement("waveforms_saw" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateSawtoothWave(10000, 5000, AudioConstants::NOTE_FREQUENCIES[index]));
			}
		}

		if(_audioPlayer->isStarted())
		{
			_audioPlayer->stop();
		}

		if(!soundWaves.empty())
		{
			_audioPlayer->start(_waveformGenerator->combineSoundWaves(soundWaves));
		}
	}
}