#include "tone_editor.hpp"
#include "tone_constants.hpp"

using std::to_string;

void ToneEditor::update()
{
	if(_guiManager->getGuiButton("tone_editor_close")->isPressed())
	{
		setGuiVisible(false);
		setEnabled(false);

		if(_waveformPlayer->isStarted())
		{
			_waveformPlayer->stop();
		}
	}

	if(_isEnabled)
	{
		_updatePlaybackGui();
		_updateOctaveGui();
		//_updateAmplitudeGui("sin", _sineAmplitudes);
		//_updateAmplitudeGui("sqr", _squareAmplitudes);
		//_updateAmplitudeGui("tri", _triangleAmplitudes);
		//_updateAmplitudeGui("saw", _sawtoothAmplitudes);
	}
}

void ToneEditor::_updatePlaybackGui()
{
	if(_guiManager->getGuiButton("tone_editor_play")->isPressed())
	{
		vector<shared_ptr<Waveform>> waveforms = _generateWaveforms(100);

		if(_waveformPlayer->isStarted())
		{
			_waveformPlayer->stop();
		}

		if(!waveforms.empty())
		{
			const shared_ptr<Waveform> waveform = _waveformGenerator->combineWaveforms(waveforms);

			_waveformPlayer->start(waveform);
		}
	}
}

void ToneEditor::_updateOctaveGui()
{
	if(_guiManager->getGuiButton("tone_editor_oct_decr")->isPressed())
	{
		//_octave--;

		//if(_octave == ToneConstants::MIN_OCTAVE)
		//{
		//	_guiManager->getGuiButton("tone_editor_oct_decr")->setPressable(false);
		//	_guiManager->getGuiButton("tone_editor_oct_decr")->setHoverable(false);
		//}

		_guiManager->getGuiButton("tone_editor_oct_incr")->setPressable(true);
		_guiManager->getGuiButton("tone_editor_oct_incr")->setHoverable(true);

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("tone_editor_oct_incr")->isPressed())
	{
		//_octave++;

		//if(_octave == ToneConstants::MAX_OCTAVE)
		//{
		//	_guiManager->getGuiButton("tone_editor_oct_incr")->setPressable(false);
		//	_guiManager->getGuiButton("tone_editor_oct_incr")->setHoverable(false);
		//}

		_guiManager->getGuiButton("tone_editor_oct_decr")->setPressable(true);
		_guiManager->getGuiButton("tone_editor_oct_decr")->setHoverable(true);

		_refreshWaveformVisualization();
	}

	//_guiManager->getGuiLabel("tone_editor_oct_val")->setContent(to_string(_octave));
}

void ToneEditor::_updateAmplitudeGui(const string & type, vector<int> & amplitudes)
{
	for(int index = 0; index < static_cast<int>(ToneConstants::NOTE_NAMES.size()); index++)
	{
		if(_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->isPressed())
		{
			amplitudes[index]--;

			if(amplitudes[index] == 0)
			{
				_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->setHoverable(true);

			_refreshWaveformVisualization();
		}
		else if(_guiManager->getGuiButton("tone_editor_" + type + "_txt" + to_string(index))->isPressed())
		{
			_refreshWaveformVisualization();
		}
		else if(_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->isPressed())
		{
			amplitudes[index]++;

			if(amplitudes[index] == 9)
			{
				_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->setPressable(false);
				_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->setHoverable(false);
			}

			_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->setPressable(true);
			_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->setHoverable(true);

			_refreshWaveformVisualization();
		}

		const bool isToggled = _guiManager->getGuiButton("tone_editor_" + type + "_txt" + to_string(index))->isToggled();

		_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->setVisible(isToggled);
		_guiManager->getGuiLabel("tone_editor_" + type + "_val" + to_string(index))->setVisible(isToggled);
		_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->setVisible(isToggled);

		const string amplitude = to_string(amplitudes[index]);

		_guiManager->getGuiLabel("tone_editor_" + type + "_val" + to_string(index))->setContent(amplitude);
	}
}

void ToneEditor::setGuiVisible(const bool value)
{
	_guiManager->getGuiRectangle("tone_editor_background")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_close")->setVisible(value);
	_guiManager->getGuiWaveform("tone_editor_visualization")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_play")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_save")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_oct_decr")->setVisible(value);
	_guiManager->getGuiLabel("tone_editor_oct_val")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_oct_incr")->setVisible(value);
	_guiManager->getGuiLabel("tone_editor_oct_name")->setVisible(value);

	for(int index = 0; index < static_cast<int>(ToneConstants::NOTE_NAMES.size()); index++)
	{
		for(const string & type : {"sin", "sqr", "tri", "saw"})
		{
			_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->setVisible(value);
			_guiManager->getGuiLabel("tone_editor_" + type + "_val" + to_string(index))->setVisible(value);
			_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->setVisible(value);
			_guiManager->getGuiButton("tone_editor_" + type + "_txt" + to_string(index))->setVisible(value);
		}

		_guiManager->getGuiLabel("tone_editor_note" + to_string(index))->setVisible(value);
	}
}

void ToneEditor::setEnabled(const bool value)
{
	_isEnabled = value;
}

void ToneEditor::_refreshWaveformVisualization()
{
	vector<shared_ptr<Waveform>> waveforms = _generateWaveforms(10);

	if(waveforms.empty())
	{
		_guiManager->getGuiWaveform("tone_editor_visualization")->setSamples({0.0f, 0.0f});
	}
	else
	{
		const shared_ptr<Waveform> waveform = _waveformGenerator->combineWaveforms(waveforms);
		const vector<double> samples = _waveformGenerator->extractSamplesFromWaveform(waveform);

		_guiManager->getGuiWaveform("tone_editor_visualization")->setSamples(samples);
	}
}

const vector<shared_ptr<Waveform>> ToneEditor::_generateWaveforms(const int duration) const
{
	vector<shared_ptr<Waveform>> waveforms = {};

	for(int index = 0; index < static_cast<int>(ToneConstants::NOTE_NAMES.size()); index++)
	{
		//const double frequency = ToneConstants::NOTE_FREQUENCIES[index] * pow(2.0, static_cast<double>(_octave));

		/*if(_guiManager->getGuiButton("tone_editor_sin_txt" + to_string(index))->isToggled())
		{
			if(_sineAmplitudes[index] != 0)
			{
				const double amplitude = static_cast<double>(_sineAmplitudes[index]) * ToneConstants::OCTAVE_AMPLITUDE_STEP;
				const shared_ptr<Waveform> waveform = _waveformGenerator->generateSineWaveform(duration, amplitude, frequency);

				waveforms.push_back(waveform);
			}
		}

		if(_guiManager->getGuiButton("tone_editor_sqr_txt" + to_string(index))->isToggled())
		{
			if(_squareAmplitudes[index] != 0)
			{
				const double amplitude = static_cast<double>(_squareAmplitudes[index]) * ToneConstants::OCTAVE_AMPLITUDE_STEP;
				const shared_ptr<Waveform> waveform = _waveformGenerator->generateSquareWaveform(duration, amplitude, frequency);

				waveforms.push_back(waveform);
			}
		}

		if(_guiManager->getGuiButton("tone_editor_tri_txt" + to_string(index))->isToggled())
		{
			if(_triangleAmplitudes[index] != 0)
			{
				const double amplitude = static_cast<double>(_triangleAmplitudes[index]) * ToneConstants::OCTAVE_AMPLITUDE_STEP;
				const shared_ptr<Waveform> waveform = _waveformGenerator->generateTriangleWaveform(duration, amplitude, frequency);

				waveforms.push_back(waveform);
			}
		}

		if(_guiManager->getGuiButton("tone_editor_saw_txt" + to_string(index))->isToggled())
		{
			if(_sawtoothAmplitudes[index] != 0)
			{
				const double amplitude = static_cast<double>(_sawtoothAmplitudes[index]) * ToneConstants::OCTAVE_AMPLITUDE_STEP;
				const shared_ptr<Waveform> waveform = _waveformGenerator->generateSawtoothWaveform(duration, amplitude, frequency);

				waveforms.push_back(waveform);
			}
		}*/
	}

	return waveforms;
}

void ToneEditor::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;
}

void ToneEditor::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	_waveformGenerator = waveformGenerator;
}

void ToneEditor::inject(const shared_ptr<WaveformPlayer> & waveformPlayer)
{
	_waveformPlayer = waveformPlayer;
}