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
	//_updateWaveformMenu();
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

		for(int index = 0; index < 12; index++)
		{
			_guiManager->getGuiElement("waveforms_sin" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_sqr" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_tri" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_saw" + to_string(index))->setVisible(true);
			_guiManager->getGuiElement("waveforms_note" + to_string(index))->setVisible(true);
		}
		//_guiManager->getGuiElement("waveforms_sin")->setVisible(true);
		//_guiManager->getGuiElement("waveforms_sin_decr")->setVisible(true);
		//_guiManager->getGuiElement("waveforms_sin_incr")->setVisible(true);
		//_guiManager->getGuiElement("waveforms_sqr")->setVisible(true);
		//_guiManager->getGuiElement("waveforms_sqr_decr")->setVisible(true);
		//_guiManager->getGuiElement("waveforms_sqr_incr")->setVisible(true);
		//_guiManager->getGuiElement("waveforms_tri")->setVisible(true);
		//_guiManager->getGuiElement("waveforms_tri_decr")->setVisible(true);
		//_guiManager->getGuiElement("waveforms_tri_incr")->setVisible(true);
		//_guiManager->getGuiElement("waveforms_saw")->setVisible(true);
		//_guiManager->getGuiElement("waveforms_saw_decr")->setVisible(true);
		//_guiManager->getGuiElement("waveforms_saw_incr")->setVisible(true);
	}
	else if(_guiManager->getGuiElement("exit")->isPressed())
	{
		exit(0);
	}
	else if(_guiManager->getGuiElement("waveforms_close")->isPressed())
	{
		_guiManager->getGuiElement("waveforms_menu")->setVisible(false);
		_guiManager->getGuiElement("waveforms_close")->setVisible(false);

		for(int index = 0; index < 12; index++)
		{
			_guiManager->getGuiElement("waveforms_sin" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_sqr" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_tri" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_saw" + to_string(index))->setVisible(false);
			_guiManager->getGuiElement("waveforms_note" + to_string(index))->setVisible(false);
		}
		//_guiManager->getGuiElement("waveforms_sin")->setVisible(false);
		//_guiManager->getGuiElement("waveforms_sin_decr")->setVisible(false);
		//_guiManager->getGuiElement("waveforms_sin_incr")->setVisible(false);
		//_guiManager->getGuiElement("waveforms_sqr")->setVisible(false);
		//_guiManager->getGuiElement("waveforms_sqr_decr")->setVisible(false);
		//_guiManager->getGuiElement("waveforms_sqr_incr")->setVisible(false);
		//_guiManager->getGuiElement("waveforms_tri")->setVisible(false);
		//_guiManager->getGuiElement("waveforms_tri_decr")->setVisible(false);
		//_guiManager->getGuiElement("waveforms_tri_incr")->setVisible(false);
		//_guiManager->getGuiElement("waveforms_saw")->setVisible(false);
		//_guiManager->getGuiElement("waveforms_saw_decr")->setVisible(false);
		//_guiManager->getGuiElement("waveforms_saw_incr")->setVisible(false);
	}
}

void GuiController::_updateWaveformMenu()
{
	const int maxAmplitude = _waveformGenerator->getMaxAmplitude();
	const int amplitudeStep = maxAmplitude / 10;

	bool isPressed = true;

	if(_guiManager->getGuiElement("waveforms_sin_decr")->isPressed())
	{
		_sineAmplitude -= amplitudeStep;
		_sineAmplitude = max(0, _sineAmplitude);
	}
	else if(_guiManager->getGuiElement("waveforms_sin_incr")->isPressed())
	{
		_sineAmplitude += amplitudeStep;
		_sineAmplitude = min(maxAmplitude, _sineAmplitude);
	}
	else if(_guiManager->getGuiElement("waveforms_sqr_decr")->isPressed())
	{
		_squareAmplitude -= amplitudeStep;
		_squareAmplitude = max(0, _squareAmplitude);
	}
	else if(_guiManager->getGuiElement("waveforms_sqr_incr")->isPressed())
	{
		_squareAmplitude += amplitudeStep;
		_squareAmplitude = min(maxAmplitude, _squareAmplitude);
	}
	else if(_guiManager->getGuiElement("waveforms_tri_decr")->isPressed())
	{
		_triangleAmplitude -= amplitudeStep;
		_triangleAmplitude = max(0, _triangleAmplitude);
	}
	else if(_guiManager->getGuiElement("waveforms_tri_incr")->isPressed())
	{
		_triangleAmplitude += amplitudeStep;
		_triangleAmplitude = min(maxAmplitude, _triangleAmplitude);
	}
	else if(_guiManager->getGuiElement("waveforms_saw_decr")->isPressed())
	{
		_sawtoothAmplitude -= amplitudeStep;
		_sawtoothAmplitude = max(0, _sawtoothAmplitude);
	}
	else if(_guiManager->getGuiElement("waveforms_saw_incr")->isPressed())
	{
		_sawtoothAmplitude += amplitudeStep;
		_sawtoothAmplitude = min(maxAmplitude, _sawtoothAmplitude);
	}
	else
	{
		isPressed = false;
	}

	if(isPressed)
	{
		if(_audioPlayer->isStarted())
		{
			_audioPlayer->stop();
		}

		vector<shared_ptr<Audio>> soundWaves = {};

		soundWaves.push_back(_waveformGenerator->generateSineWave(1000, _sineAmplitude, 440));
		soundWaves.push_back(_waveformGenerator->generateSquareWave(1000, _squareAmplitude, 440));
		soundWaves.push_back(_waveformGenerator->generateTriangleWave(1000, _triangleAmplitude, 440));
		soundWaves.push_back(_waveformGenerator->generateSawtoothWave(1000, _sawtoothAmplitude, 440));

		_audioPlayer->start(_waveformGenerator->combineSoundWaves(soundWaves));
	}
}