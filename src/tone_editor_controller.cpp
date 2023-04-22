#include "tone_editor_controller.hpp"
#include "tone_constants.hpp"

using std::to_string;

void ToneEditorController::update()
{
	if(_guiManager->getGuiButton("tone_editor_close")->isPressed())
	{
		setGuiVisible(false);
		setEnabled(false);
		setTone(nullptr);

		if(_waveformPlayer->isStarted())
		{
			_waveformPlayer->stop();
		}
	}

	if(_isEnabled)
	{
		_updatePlaybackGui();
		_updateOctaveGui();
		_updateAmplitudeGui("sin", _tone->sineAmplitudes, _tone->sineToggles);
		_updateAmplitudeGui("sqr", _tone->squareAmplitudes, _tone->squareToggles);
		_updateAmplitudeGui("tri", _tone->triangleAmplitudes, _tone->triangleToggles);
		_updateAmplitudeGui("saw", _tone->sawtoothAmplitudes, _tone->sawtoothToggles);
	}
}

void ToneEditorController::_updatePlaybackGui()
{
	if(_guiManager->getGuiButton("tone_editor_play")->isPressed())
	{
		if(_waveformPlayer->isStarted())
		{
			_waveformPlayer->stop();
		}

		vector<shared_ptr<Waveform>> waveforms = _waveformGenerator->generateWaveforms(_tone, 100);

		if(!waveforms.empty())
		{
			const shared_ptr<Waveform> waveform = _waveformGenerator->combineWaveforms(waveforms);

			_waveformPlayer->start(waveform);
		}
	}
}

void ToneEditorController::_updateOctaveGui()
{
	if(_guiManager->getGuiButton("tone_editor_oct_decr")->isPressed())
	{
		_tone->octave--;

		if(_tone->octave == ToneConstants::MIN_OCTAVE)
		{
			_guiManager->getGuiButton("tone_editor_oct_decr")->setPressable(false);
			_guiManager->getGuiButton("tone_editor_oct_decr")->setHoverable(false);
		}

		_guiManager->getGuiButton("tone_editor_oct_incr")->setPressable(true);
		_guiManager->getGuiButton("tone_editor_oct_incr")->setHoverable(true);

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("tone_editor_oct_incr")->isPressed())
	{
		_tone->octave++;

		if(_tone->octave == ToneConstants::MAX_OCTAVE)
		{
			_guiManager->getGuiButton("tone_editor_oct_incr")->setPressable(false);
			_guiManager->getGuiButton("tone_editor_oct_incr")->setHoverable(false);
		}

		_guiManager->getGuiButton("tone_editor_oct_decr")->setPressable(true);
		_guiManager->getGuiButton("tone_editor_oct_decr")->setHoverable(true);

		_refreshWaveformVisualization();
	}

	_guiManager->getGuiLabel("tone_editor_oct_val")->setContent(to_string(_tone->octave));
}

void ToneEditorController::_updateAmplitudeGui(const string & type, vector<int> & amplitudes, vector<bool> & toggles)
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
			toggles[index] = !toggles[index];

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

		_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->setVisible(toggles[index]);
		_guiManager->getGuiLabel("tone_editor_" + type + "_val" + to_string(index))->setVisible(toggles[index]);
		_guiManager->getGuiLabel("tone_editor_" + type + "_val" + to_string(index))->setContent(to_string(amplitudes[index]));
		_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->setVisible(toggles[index]);
		_guiManager->getGuiButton("tone_editor_" + type + "_txt" + to_string(index))->setHighlighted(toggles[index]);
	}
}

void ToneEditorController::setGuiVisible(const bool value)
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

void ToneEditorController::setEnabled(const bool value)
{
	_isEnabled = value;
}

void ToneEditorController::setTone(const shared_ptr<Tone> & value)
{
	_tone = value;
}

void ToneEditorController::_refreshWaveformVisualization()
{
	vector<shared_ptr<Waveform>> waveforms = _waveformGenerator->generateWaveforms(_tone, 10);

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

void ToneEditorController::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;
}

void ToneEditorController::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	_waveformGenerator = waveformGenerator;
}

void ToneEditorController::inject(const shared_ptr<WaveformPlayer> & waveformPlayer)
{
	_waveformPlayer = waveformPlayer;
}