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
		_updatePlaybackGui();
		_updateOctaveGui();
		_updateAmplitudeGui("sin", _sineAmplitudes);
		_updateAmplitudeGui("sqr", _squareAmplitudes);
		_updateAmplitudeGui("tri", _triangleAmplitudes);
		_updateAmplitudeGui("saw", _sawtoothAmplitudes);
	}
}

void WaveformMenu::_updateAmplitudeGui(const string & type, vector<int> & amplitudes)
{
	for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
	{
		if(_guiManager->getGuiButton("waveforms_" + type + "_decr" + to_string(index))->isPressed())
		{
			amplitudes[index]--;

			if(amplitudes[index] == 0)
			{
				_guiManager->getGuiButton("waveforms_" + type + "_decr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("waveforms_" + type + "_decr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("waveforms_" + type + "_incr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("waveforms_" + type + "_incr" + to_string(index))->setHoverable(true);

			_refreshWaveformVisualization();
		}
		else if(_guiManager->getGuiButton("waveforms_" + type + "_txt" + to_string(index))->isPressed())
		{
			_refreshWaveformVisualization();
		}
		else if(_guiManager->getGuiButton("waveforms_" + type + "_incr" + to_string(index))->isPressed())
		{
			amplitudes[index]++;

			if(amplitudes[index] == 9)
			{
				_guiManager->getGuiButton("waveforms_" + type + "_incr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("waveforms_" + type + "_incr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("waveforms_" + type + "_decr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("waveforms_" + type + "_decr" + to_string(index))->setHoverable(true);

			_refreshWaveformVisualization();
		}

		const bool isToggled = _guiManager->getGuiButton("waveforms_" + type + "_txt" + to_string(index))->isToggled();

		_guiManager->getGuiButton("waveforms_" + type + "_decr" + to_string(index))->setVisible(isToggled);
		_guiManager->getGuiLabel("waveforms_" + type + "_val" + to_string(index))->setVisible(isToggled);
		_guiManager->getGuiLabel("waveforms_" + type + "_val" + to_string(index))->setContent(to_string(amplitudes[index]));
		_guiManager->getGuiButton("waveforms_" + type + "_incr" + to_string(index))->setVisible(isToggled);
	}
}

void WaveformMenu::_updatePlaybackGui()
{
	if(_guiManager->getGuiButton("waveforms_play")->isPressed())
	{
		vector<shared_ptr<Audio>> waveforms = _generateWaveforms(100);

		if(_audioPlayer->isStarted())
		{
			_audioPlayer->stop();
		}

		if(!waveforms.empty())
		{
			const shared_ptr<Audio> waveform = _waveformGenerator->combineWaveforms(waveforms);

			_audioPlayer->start(waveform);
		}
	}
}

void WaveformMenu::_updateOctaveGui()
{
	if(_guiManager->getGuiButton("waveforms_oct_decr")->isPressed())
	{
		_octave--;

		if(_octave == AudioConstants::MIN_OCTAVE)
		{
			_guiManager->getGuiButton("waveforms_oct_decr")->setPressable(false);
			_guiManager->getGuiButton("waveforms_oct_decr")->setHoverable(false);
		}

		_guiManager->getGuiButton("waveforms_oct_incr")->setPressable(true);
		_guiManager->getGuiButton("waveforms_oct_incr")->setHoverable(true);

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("waveforms_oct_incr")->isPressed())
	{
		_octave++;

		if(_octave == AudioConstants::MAX_OCTAVE)
		{
			_guiManager->getGuiButton("waveforms_oct_incr")->setPressable(false);
			_guiManager->getGuiButton("waveforms_oct_incr")->setHoverable(false);
		}

		_guiManager->getGuiButton("waveforms_oct_decr")->setPressable(true);
		_guiManager->getGuiButton("waveforms_oct_decr")->setHoverable(true);

		_refreshWaveformVisualization();
	}

	_guiManager->getGuiLabel("waveforms_oct_val")->setContent(to_string(_octave));
}

void WaveformMenu::_setGuiVisible(const bool value)
{
	_guiManager->getGuiRectangle("waveforms_menu")->setVisible(value);
	_guiManager->getGuiButton("waveforms_close")->setVisible(value);
	_guiManager->getGuiWaveform("waveforms_visualization")->setVisible(value);
	_guiManager->getGuiButton("waveforms_play")->setVisible(value);
	_guiManager->getGuiButton("waveforms_oct_decr")->setVisible(value);
	_guiManager->getGuiLabel("waveforms_oct_val")->setVisible(value);
	_guiManager->getGuiButton("waveforms_oct_incr")->setVisible(value);
	_guiManager->getGuiLabel("waveforms_oct_name")->setVisible(value);

	for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
	{
		for(const string & type : {"sin", "sqr", "tri", "saw"})
		{
			_guiManager->getGuiButton("waveforms_" + type + "_decr" + to_string(index))->setVisible(value);
			_guiManager->getGuiLabel("waveforms_" + type + "_val" + to_string(index))->setVisible(value);
			_guiManager->getGuiButton("waveforms_" + type + "_incr" + to_string(index))->setVisible(value);
			_guiManager->getGuiButton("waveforms_" + type + "_txt" + to_string(index))->setVisible(value);
		}

		_guiManager->getGuiLabel("waveforms_note" + to_string(index))->setVisible(value);
	}
}

void WaveformMenu::_refreshWaveformVisualization()
{
	vector<shared_ptr<Audio>> waveforms = _generateWaveforms(10);

	if(waveforms.empty())
	{
		_guiManager->getGuiWaveform("waveforms_visualization")->setSamples({0.0f, 0.0f});
	}
	else
	{
		const shared_ptr<Audio> waveform = _waveformGenerator->combineWaveforms(waveforms);
		const vector<double> samples = _waveformGenerator->extractSamplesFromWaveform(waveform);

		_guiManager->getGuiWaveform("waveforms_visualization")->setSamples(samples);
	}
}

const vector<shared_ptr<Audio>> WaveformMenu::_generateWaveforms(const int duration) const
{
	vector<shared_ptr<Audio>> waveforms = {};

	for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
	{
		const double frequency = AudioConstants::NOTE_FREQUENCIES[index] * pow(2.0, static_cast<double>(_octave));

		if(_guiManager->getGuiButton("waveforms_sin_txt" + to_string(index))->isToggled())
		{
			if(_sineAmplitudes[index] != 0)
			{
				const double amplitude = static_cast<double>(_sineAmplitudes[index]) * OCTAVE_AMPLITUDE_STEP;
				const shared_ptr<Audio> waveform = _waveformGenerator->generateSineWaveform(duration, amplitude, frequency);

				waveforms.push_back(waveform);
			}
		}

		if(_guiManager->getGuiButton("waveforms_sqr_txt" + to_string(index))->isToggled())
		{
			if(_squareAmplitudes[index] != 0)
			{
				const double amplitude = static_cast<double>(_squareAmplitudes[index]) * OCTAVE_AMPLITUDE_STEP;
				const shared_ptr<Audio> waveform = _waveformGenerator->generateSquareWaveform(duration, amplitude, frequency);

				waveforms.push_back(waveform);
			}
		}

		if(_guiManager->getGuiButton("waveforms_tri_txt" + to_string(index))->isToggled())
		{
			if(_triangleAmplitudes[index] != 0)
			{
				const double amplitude = static_cast<double>(_triangleAmplitudes[index]) * OCTAVE_AMPLITUDE_STEP;
				const shared_ptr<Audio> waveform = _waveformGenerator->generateTriangleWaveform(duration, amplitude, frequency);

				waveforms.push_back(waveform);
			}
		}

		if(_guiManager->getGuiButton("waveforms_saw_txt" + to_string(index))->isToggled())
		{
			if(_sawtoothAmplitudes[index] != 0)
			{
				const double amplitude = static_cast<double>(_sawtoothAmplitudes[index]) * OCTAVE_AMPLITUDE_STEP;
				const shared_ptr<Audio> waveform = _waveformGenerator->generateSawtoothWaveform(duration, amplitude, frequency);

				waveforms.push_back(waveform);
			}
		}
	}

	return waveforms;
}