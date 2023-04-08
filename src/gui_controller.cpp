#include "gui_controller.hpp"
#include "tools.hpp"

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


	/*else if(_guiManager->getElement("waveforms_100")->isPressed() ||
			_guiManager->getElement("waveforms_200")->isPressed() ||
			_guiManager->getElement("waveforms_300")->isPressed() ||
			_guiManager->getElement("waveforms_400")->isPressed() ||
			_guiManager->getElement("waveforms_500")->isPressed() ||
			_guiManager->getElement("waveforms_600")->isPressed() ||
			_guiManager->getElement("waveforms_700")->isPressed() ||
			_guiManager->getElement("waveforms_800")->isPressed() ||
			_guiManager->getElement("waveforms_900")->isPressed())
	{
		vector<shared_ptr<Audio>> soundWaves = {};

		if(_guiManager->getElement("waveforms_100")->isToggled())
		{
			soundWaves.push_back(_waveformGenerator->generateSineWave(100, 30000, 100));
		}
		if(_guiManager->getElement("waveforms_200")->isToggled())
		{
			soundWaves.push_back(_waveformGenerator->generateSineWave(100, 30000, 200));
		}
		if(_guiManager->getElement("waveforms_300")->isToggled())
		{
			soundWaves.push_back(_waveformGenerator->generateSineWave(100, 30000, 300));
		}
		if(_guiManager->getElement("waveforms_400")->isToggled())
		{
			soundWaves.push_back(_waveformGenerator->generateSineWave(100, 30000, 400));
		}
		if(_guiManager->getElement("waveforms_500")->isToggled())
		{
			soundWaves.push_back(_waveformGenerator->generateSineWave(100, 30000, 500));
		}
		if(_guiManager->getElement("waveforms_600")->isToggled())
		{
			soundWaves.push_back(_waveformGenerator->generateSineWave(100, 30000, 600));
		}
		if(_guiManager->getElement("waveforms_700")->isToggled())
		{
			soundWaves.push_back(_waveformGenerator->generateSineWave(100, 30000, 700));
		}
		if(_guiManager->getElement("waveforms_800")->isToggled())
		{
			soundWaves.push_back(_waveformGenerator->generateSineWave(100, 30000, 800));
		}
		if(_guiManager->getElement("waveforms_900")->isToggled())
		{
			soundWaves.push_back(_waveformGenerator->generateSineWave(100, 30000, 900));
		}

		_audioPlayer->start(_waveformGenerator->combineSoundWaves(soundWaves));
	}*/
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
		_guiManager->getGuiElement("waveforms_sin")->setVisible(true);
		_guiManager->getGuiElement("waveforms_sin_decr")->setVisible(true);
		_guiManager->getGuiElement("waveforms_sin_incr")->setVisible(true);
		_guiManager->getGuiElement("waveforms_sqr")->setVisible(true);
		_guiManager->getGuiElement("waveforms_sqr_decr")->setVisible(true);
		_guiManager->getGuiElement("waveforms_sqr_incr")->setVisible(true);
		_guiManager->getGuiElement("waveforms_tri")->setVisible(true);
		_guiManager->getGuiElement("waveforms_tri_decr")->setVisible(true);
		_guiManager->getGuiElement("waveforms_tri_incr")->setVisible(true);
		_guiManager->getGuiElement("waveforms_saw")->setVisible(true);
		_guiManager->getGuiElement("waveforms_saw_decr")->setVisible(true);
		_guiManager->getGuiElement("waveforms_saw_incr")->setVisible(true);
	}
	else if(_guiManager->getGuiElement("exit")->isPressed())
	{
		exit(0);
	}
	else if(_guiManager->getGuiElement("waveforms_close")->isPressed())
	{
		_guiManager->getGuiElement("waveforms_menu")->setVisible(false);
		_guiManager->getGuiElement("waveforms_close")->setVisible(false);
		_guiManager->getGuiElement("waveforms_sin")->setVisible(false);
		_guiManager->getGuiElement("waveforms_sin_decr")->setVisible(false);
		_guiManager->getGuiElement("waveforms_sin_incr")->setVisible(false);
		_guiManager->getGuiElement("waveforms_sqr")->setVisible(false);
		_guiManager->getGuiElement("waveforms_sqr_decr")->setVisible(false);
		_guiManager->getGuiElement("waveforms_sqr_incr")->setVisible(false);
		_guiManager->getGuiElement("waveforms_tri")->setVisible(false);
		_guiManager->getGuiElement("waveforms_tri_decr")->setVisible(false);
		_guiManager->getGuiElement("waveforms_tri_incr")->setVisible(false);
		_guiManager->getGuiElement("waveforms_saw")->setVisible(false);
		_guiManager->getGuiElement("waveforms_saw_decr")->setVisible(false);
		_guiManager->getGuiElement("waveforms_saw_incr")->setVisible(false);
	}
}

void GuiController::_updateWaveformMenu()
{
	const float maxAmplitude = _waveformGenerator->getMaxAmplitude();
	const float amplitudeStep = maxAmplitude / 10.0f;

	if(_guiManager->getGuiElement("waveforms_sin_decr")->isPressed())
	{
		_sineAmplitude -= amplitudeStep;
		_sineAmplitude = max(0.0f, _sineAmplitude);

		_audioPlayer->start(_waveformGenerator->generateSineWave(100, _sineAmplitude, 440));
	}
	else if(_guiManager->getGuiElement("waveforms_sin_incr")->isPressed())
	{
		_sineAmplitude += amplitudeStep;
		_sineAmplitude = min(maxAmplitude, _sineAmplitude);

		_audioPlayer->start(_waveformGenerator->generateSineWave(100, _sineAmplitude, 440));
	}
}