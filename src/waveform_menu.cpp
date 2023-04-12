#include "waveform_menu.hpp"
#include "audio_constants.hpp"

using std::to_string;

WaveformMenu::WaveformMenu()
{
	for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
	{
		_sineAmplitudes.push_back(0);
		_squareAmplitudes.push_back(0);
		_triangleAmplitudes.push_back(0);
		_sawtoothAmplitudes.push_back(0);
	}
}

void WaveformMenu::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;
}

void WaveformMenu::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	_waveformGenerator = waveformGenerator;
}

void WaveformMenu::inject(const shared_ptr<AudioPlayer> & audioPlayer)
{
	_audioPlayer = audioPlayer;
}

void WaveformMenu::inject(const shared_ptr<AudioManager> & audioManager)
{
	_audioManager = audioManager;
}

void WaveformMenu::update()
{
	if(_guiManager->getGuiButton("waveforms")->isPressed())
	{
		_setGuiVisible(true);

		_isEnabled = true;
	}
	else if(_guiManager->getGuiButton("waveforms_close")->isPressed())
	{
		_setGuiVisible(false);

		if(_audioPlayer->isStarted())
		{
			_audioPlayer->stop();
		}

		_isEnabled = false;
	}

	if(_isEnabled)
	{
		_updatePlaying();
		_updateNotes();
	}
}

void WaveformMenu::_updatePlaying()
{
	if(_guiManager->getGuiButton("waveforms_play")->isPressed())
	{
		vector<shared_ptr<Audio>> soundWaves = {};

		for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
		{
			const double frequency = AudioConstants::NOTE_FREQUENCIES[index] * pow(2.0, static_cast<double>(_octave));
			const int duration = 100;

			if(_guiManager->getGuiButton("waveforms_sin_tgl" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateSineWave(duration, static_cast<double>(_sineAmplitudes[index]) * AMPLITUDE_STEP, frequency));
			}
			if(_guiManager->getGuiButton("waveforms_sqr_tgl" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateSquareWave(duration, static_cast<double>(_squareAmplitudes[index]) * AMPLITUDE_STEP, frequency));
			}
			if(_guiManager->getGuiButton("waveforms_tri_tgl" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateTriangleWave(duration, static_cast<double>(_triangleAmplitudes[index]) * AMPLITUDE_STEP, frequency));
			}
			if(_guiManager->getGuiButton("waveforms_saw_tgl" + to_string(index))->isToggled())
			{
				soundWaves.push_back(_waveformGenerator->generateSawtoothWave(duration, static_cast<double>(_sawtoothAmplitudes[index]) * AMPLITUDE_STEP, frequency));
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

void WaveformMenu::_updateNotes()
{
	for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
	{
		if(_guiManager->getGuiButton("waveforms_sin_decr" + to_string(index))->isPressed())
		{
			_sineAmplitudes[index]--;

			if(_sineAmplitudes[index] == 0)
			{
				_guiManager->getGuiButton("waveforms_sin_decr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("waveforms_sin_decr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("waveforms_sin_incr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("waveforms_sin_incr" + to_string(index))->setHoverable(true);
		}
		else if(_guiManager->getGuiButton("waveforms_sin_incr" + to_string(index))->isPressed())
		{
			_sineAmplitudes[index]++;

			if(_sineAmplitudes[index] == 9)
			{
				_guiManager->getGuiButton("waveforms_sin_incr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("waveforms_sin_incr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("waveforms_sin_decr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("waveforms_sin_decr" + to_string(index))->setHoverable(true);
		}
		else if(_guiManager->getGuiButton("waveforms_sqr_decr" + to_string(index))->isPressed())
		{
			_squareAmplitudes[index]--;

			if(_squareAmplitudes[index] == 0)
			{
				_guiManager->getGuiButton("waveforms_sqr_decr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("waveforms_sqr_decr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("waveforms_sqr_incr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("waveforms_sqr_incr" + to_string(index))->setHoverable(true);
		}
		else if(_guiManager->getGuiButton("waveforms_sqr_incr" + to_string(index))->isPressed())
		{
			_squareAmplitudes[index]++;

			if(_squareAmplitudes[index] == 9)
			{
				_guiManager->getGuiButton("waveforms_sqr_incr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("waveforms_sqr_incr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("waveforms_sqr_decr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("waveforms_sqr_decr" + to_string(index))->setHoverable(true);
		}
		else if(_guiManager->getGuiButton("waveforms_tri_decr" + to_string(index))->isPressed())
		{
			_triangleAmplitudes[index]--;

			if(_triangleAmplitudes[index] == 0)
			{
				_guiManager->getGuiButton("waveforms_tri_decr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("waveforms_tri_decr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("waveforms_tri_incr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("waveforms_tri_incr" + to_string(index))->setHoverable(true);
		}
		else if(_guiManager->getGuiButton("waveforms_tri_incr" + to_string(index))->isPressed())
		{
			_triangleAmplitudes[index]++;

			if(_triangleAmplitudes[index] == 9)
			{
				_guiManager->getGuiButton("waveforms_tri_incr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("waveforms_tri_incr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("waveforms_tri_decr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("waveforms_tri_decr" + to_string(index))->setHoverable(true);
		}
		else if(_guiManager->getGuiButton("waveforms_saw_decr" + to_string(index))->isPressed())
		{
			_sawtoothAmplitudes[index]--;

			if(_sawtoothAmplitudes[index] == 0)
			{
				_guiManager->getGuiButton("waveforms_saw_decr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("waveforms_saw_decr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("waveforms_saw_incr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("waveforms_saw_incr" + to_string(index))->setHoverable(true);
		}
		else if(_guiManager->getGuiButton("waveforms_saw_incr" + to_string(index))->isPressed())
		{
			_sawtoothAmplitudes[index]++;

			if(_sawtoothAmplitudes[index] == 9)
			{
				_guiManager->getGuiButton("waveforms_saw_incr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("waveforms_saw_incr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("waveforms_saw_decr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("waveforms_saw_decr" + to_string(index))->setHoverable(true);
		}

		_guiManager->getGuiLabel("waveforms_sin_val" + to_string(index))->setContent(to_string(_sineAmplitudes[index]));
		_guiManager->getGuiLabel("waveforms_sqr_val" + to_string(index))->setContent(to_string(_squareAmplitudes[index]));
		_guiManager->getGuiLabel("waveforms_tri_val" + to_string(index))->setContent(to_string(_triangleAmplitudes[index]));
		_guiManager->getGuiLabel("waveforms_saw_val" + to_string(index))->setContent(to_string(_sawtoothAmplitudes[index]));

		const bool isSineToggled = _guiManager->getGuiButton("waveforms_sin_tgl" + to_string(index))->isToggled();
		const bool isSquareToggled = _guiManager->getGuiButton("waveforms_sqr_tgl" + to_string(index))->isToggled();
		const bool isTriangleToggled = _guiManager->getGuiButton("waveforms_tri_tgl" + to_string(index))->isToggled();
		const bool isSawoothToggled = _guiManager->getGuiButton("waveforms_saw_tgl" + to_string(index))->isToggled();

		_guiManager->getGuiButton("waveforms_sin_decr" + to_string(index))->setVisible(isSineToggled);
		_guiManager->getGuiButton("waveforms_sqr_decr" + to_string(index))->setVisible(isSquareToggled);
		_guiManager->getGuiButton("waveforms_tri_decr" + to_string(index))->setVisible(isTriangleToggled);
		_guiManager->getGuiButton("waveforms_saw_decr" + to_string(index))->setVisible(isSawoothToggled);
		_guiManager->getGuiLabel("waveforms_sin_val" + to_string(index))->setVisible(isSineToggled);
		_guiManager->getGuiLabel("waveforms_sqr_val" + to_string(index))->setVisible(isSquareToggled);
		_guiManager->getGuiLabel("waveforms_tri_val" + to_string(index))->setVisible(isTriangleToggled);
		_guiManager->getGuiLabel("waveforms_saw_val" + to_string(index))->setVisible(isSawoothToggled);
		_guiManager->getGuiButton("waveforms_sin_incr" + to_string(index))->setVisible(isSineToggled);
		_guiManager->getGuiButton("waveforms_sqr_incr" + to_string(index))->setVisible(isSquareToggled);
		_guiManager->getGuiButton("waveforms_tri_incr" + to_string(index))->setVisible(isTriangleToggled);
		_guiManager->getGuiButton("waveforms_saw_incr" + to_string(index))->setVisible(isSawoothToggled);
	}
}

void WaveformMenu::_setGuiVisible(const bool value)
{
	_guiManager->getGuiRectangle("waveforms_menu")->setVisible(value);
	_guiManager->getGuiButton("waveforms_close")->setVisible(value);
	_guiManager->getGuiButton("waveforms_play")->setVisible(value);

	for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
	{
		_guiManager->getGuiButton("waveforms_sin_decr" + to_string(index))->setVisible(value);
		_guiManager->getGuiLabel("waveforms_sin_val" + to_string(index))->setVisible(value);
		_guiManager->getGuiButton("waveforms_sin_incr" + to_string(index))->setVisible(value);
		_guiManager->getGuiButton("waveforms_sin_tgl" + to_string(index))->setVisible(value);
		_guiManager->getGuiButton("waveforms_sqr_decr" + to_string(index))->setVisible(value);
		_guiManager->getGuiLabel("waveforms_sqr_val" + to_string(index))->setVisible(value);
		_guiManager->getGuiButton("waveforms_sqr_incr" + to_string(index))->setVisible(value);
		_guiManager->getGuiButton("waveforms_sqr_tgl" + to_string(index))->setVisible(value);
		_guiManager->getGuiButton("waveforms_tri_decr" + to_string(index))->setVisible(value);
		_guiManager->getGuiLabel("waveforms_tri_val" + to_string(index))->setVisible(value);
		_guiManager->getGuiButton("waveforms_tri_incr" + to_string(index))->setVisible(value);
		_guiManager->getGuiButton("waveforms_tri_tgl" + to_string(index))->setVisible(value);
		_guiManager->getGuiButton("waveforms_saw_decr" + to_string(index))->setVisible(value);
		_guiManager->getGuiLabel("waveforms_saw_val" + to_string(index))->setVisible(value);
		_guiManager->getGuiButton("waveforms_saw_incr" + to_string(index))->setVisible(value);
		_guiManager->getGuiButton("waveforms_saw_tgl" + to_string(index))->setVisible(value);
		_guiManager->getGuiLabel("waveforms_note" + to_string(index))->setVisible(value);
	}
}