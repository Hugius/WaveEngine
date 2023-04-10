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
	else if(_guiManager->getGuiButton("waveforms")->isPressed())
	{
		_guiManager->getGuiRectangle("waveforms_menu")->setVisible(true);
		_guiManager->getGuiButton("waveforms_close")->setVisible(true);
		_guiManager->getGuiButton("waveforms_play")->setVisible(true);

		for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
		{
			_guiManager->getGuiButton("waveforms_sin_decr" + to_string(index))->setVisible(true);
			_guiManager->getGuiLabel("waveforms_sin_val" + to_string(index))->setVisible(true);
			_guiManager->getGuiButton("waveforms_sin_incr" + to_string(index))->setVisible(true);
			_guiManager->getGuiButton("waveforms_sin_tgl" + to_string(index))->setVisible(true);
			_guiManager->getGuiButton("waveforms_sqr_decr" + to_string(index))->setVisible(true);
			_guiManager->getGuiLabel("waveforms_sqr_val" + to_string(index))->setVisible(true);
			_guiManager->getGuiButton("waveforms_sqr_incr" + to_string(index))->setVisible(true);
			_guiManager->getGuiButton("waveforms_sqr_tgl" + to_string(index))->setVisible(true);
			_guiManager->getGuiButton("waveforms_tri_decr" + to_string(index))->setVisible(true);
			_guiManager->getGuiLabel("waveforms_tri_val" + to_string(index))->setVisible(true);
			_guiManager->getGuiButton("waveforms_tri_incr" + to_string(index))->setVisible(true);
			_guiManager->getGuiButton("waveforms_tri_tgl" + to_string(index))->setVisible(true);
			_guiManager->getGuiButton("waveforms_saw_decr" + to_string(index))->setVisible(true);
			_guiManager->getGuiLabel("waveforms_saw_val" + to_string(index))->setVisible(true);
			_guiManager->getGuiButton("waveforms_saw_incr" + to_string(index))->setVisible(true);
			_guiManager->getGuiButton("waveforms_saw_tgl" + to_string(index))->setVisible(true);
			_guiManager->getGuiLabel("waveforms_note" + to_string(index))->setVisible(true);
		}
	}
	else if(_guiManager->getGuiButton("exit")->isPressed())
	{
		exit(0);
	}
}

void GuiController::_updateWaveformMenu()
{
	if(_guiManager->getGuiButton("waveforms_close")->isPressed())
	{
		_guiManager->getGuiRectangle("waveforms_menu")->setVisible(false);
		_guiManager->getGuiButton("waveforms_close")->setVisible(false);
		_guiManager->getGuiButton("waveforms_play")->setVisible(false);

		for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
		{
			_guiManager->getGuiButton("waveforms_sin_decr" + to_string(index))->setVisible(false);
			_guiManager->getGuiLabel("waveforms_sin_val" + to_string(index))->setVisible(false);
			_guiManager->getGuiButton("waveforms_sin_incr" + to_string(index))->setVisible(false);
			_guiManager->getGuiButton("waveforms_sin_tgl" + to_string(index))->setVisible(false);
			_guiManager->getGuiButton("waveforms_sqr_decr" + to_string(index))->setVisible(false);
			_guiManager->getGuiLabel("waveforms_sqr_val" + to_string(index))->setVisible(false);
			_guiManager->getGuiButton("waveforms_sqr_incr" + to_string(index))->setVisible(false);
			_guiManager->getGuiButton("waveforms_sqr_tgl" + to_string(index))->setVisible(false);
			_guiManager->getGuiButton("waveforms_tri_decr" + to_string(index))->setVisible(false);
			_guiManager->getGuiLabel("waveforms_tri_val" + to_string(index))->setVisible(false);
			_guiManager->getGuiButton("waveforms_tri_incr" + to_string(index))->setVisible(false);
			_guiManager->getGuiButton("waveforms_tri_tgl" + to_string(index))->setVisible(false);
			_guiManager->getGuiButton("waveforms_saw_decr" + to_string(index))->setVisible(false);
			_guiManager->getGuiLabel("waveforms_saw_val" + to_string(index))->setVisible(false);
			_guiManager->getGuiButton("waveforms_saw_incr" + to_string(index))->setVisible(false);
			_guiManager->getGuiButton("waveforms_saw_tgl" + to_string(index))->setVisible(false);
			_guiManager->getGuiLabel("waveforms_note" + to_string(index))->setVisible(false);
		}

		if(_audioPlayer->isStarted())
		{
			_audioPlayer->stop();
		}
	}
	else if(_guiManager->getGuiButton("waveforms_play")->isPressed())
	{
		vector<shared_ptr<Audio>> soundWaves = {};

		for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
		{
			if(_guiManager->getGuiButton("waveforms_sin" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateSineWave(1000, 5000, AudioConstants::NOTE_FREQUENCIES[index]));
			}
			if(_guiManager->getGuiButton("waveforms_sqr" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateSquareWave(1000, 5000, AudioConstants::NOTE_FREQUENCIES[index]));
			}
			if(_guiManager->getGuiButton("waveforms_tri" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateTriangleWave(1000, 5000, AudioConstants::NOTE_FREQUENCIES[index]));
			}
			if(_guiManager->getGuiButton("waveforms_saw" + to_string(index))->isToggled())
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