#include "gui_controller.hpp"
#include "tools.hpp"
#include "audio_constants.hpp"

using std::to_string;

void GuiController::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;
}

void GuiController::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	_waveformGenerator = waveformGenerator;
}

void GuiController::inject(const shared_ptr<AudioPlayer> & audioPlayer)
{
	_audioPlayer = audioPlayer;
}

void GuiController::inject(const shared_ptr<AudioManager> & audioManager)
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
		_guiManager->getGuiElement("waveforms_sin_phs")->setVisible(true);
		_guiManager->getGuiElement("waveforms_sin_amp")->setVisible(true);
		_guiManager->getGuiElement("waveforms_sin_typ")->setVisible(true);
		_guiManager->getGuiElement("waveforms_sqr_phs")->setVisible(true);
		_guiManager->getGuiElement("waveforms_sqr_amp")->setVisible(true);
		_guiManager->getGuiElement("waveforms_sqr_typ")->setVisible(true);
		_guiManager->getGuiElement("waveforms_tri_phs")->setVisible(true);
		_guiManager->getGuiElement("waveforms_tri_amp")->setVisible(true);
		_guiManager->getGuiElement("waveforms_tri_typ")->setVisible(true);
		_guiManager->getGuiElement("waveforms_saw_phs")->setVisible(true);
		_guiManager->getGuiElement("waveforms_saw_amp")->setVisible(true);
		_guiManager->getGuiElement("waveforms_saw_typ")->setVisible(true);

		for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
		{
			_guiManager->getGuiElement("waveforms_sin_phs" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_sin_amp" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_sin_tgl" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_sqr_phs" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_sqr_amp" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_sqr_tgl" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_tri_phs" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_tri_amp" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_tri_tgl" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_saw_phs" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_saw_amp" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_saw_tgl" + to_string(index))->setVisible(true);
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
		_guiManager->getGuiElement("waveforms_sin_phs")->setVisible(false);
		_guiManager->getGuiElement("waveforms_sin_amp")->setVisible(false);
		_guiManager->getGuiElement("waveforms_sin_typ")->setVisible(false);
		_guiManager->getGuiElement("waveforms_sqr_phs")->setVisible(false);
		_guiManager->getGuiElement("waveforms_sqr_amp")->setVisible(false);
		_guiManager->getGuiElement("waveforms_sqr_typ")->setVisible(false);
		_guiManager->getGuiElement("waveforms_tri_phs")->setVisible(false);
		_guiManager->getGuiElement("waveforms_tri_amp")->setVisible(false);
		_guiManager->getGuiElement("waveforms_tri_typ")->setVisible(false);
		_guiManager->getGuiElement("waveforms_saw_phs")->setVisible(false);
		_guiManager->getGuiElement("waveforms_saw_amp")->setVisible(false);
		_guiManager->getGuiElement("waveforms_saw_typ")->setVisible(false);

		for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
		{
			_guiManager->getGuiElement("waveforms_sin_phs" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_sin_amp" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_sin_tgl" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_sqr_phs" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_sqr_amp" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_sqr_tgl" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_tri_phs" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_tri_amp" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_tri_tgl" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_saw_phs" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_saw_amp" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_saw_tgl" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_note" + to_string(index))->setVisible(false);
		}

		if(_audioPlayer->isStarted())
		{
			_audioPlayer->stop();
		}
	}
	else if(_guiManager->getGuiElement("waveforms_play")->isPressed())
	{
		vector<shared_ptr<Audio>> soundWaves = {};

		for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
		{
			if(_guiManager->getGuiElement("waveforms_sin" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateSineWave(1000, 5000, AudioConstants::NOTE_FREQUENCIES[index]));
			}
			if(_guiManager->getGuiElement("waveforms_sqr" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateSquareWave(1000, 5000, AudioConstants::NOTE_FREQUENCIES[index]));
			}
			if(_guiManager->getGuiElement("waveforms_tri" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateTriangleWave(1000, 5000, AudioConstants::NOTE_FREQUENCIES[index]));
			}
			if(_guiManager->getGuiElement("waveforms_saw" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateSawtoothWave(1000, 5000, AudioConstants::NOTE_FREQUENCIES[index]));
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