#include "tone_editor_controller.hpp"
#include "tone_constants.hpp"

using std::to_string;

void ToneEditorController::update()
{
	if(!_isEnabled)
	{
		return;
	}

	if(_guiManager->getGuiButton("tone_editor_close")->isPressed())
	{
		if(_waveformPlayer->isStarted())
		{
			_waveformPlayer->stop();
		}

		_setGuiVisible(false);

		_isEnabled = false;

		return;
	}

	const shared_ptr<Tone> currentTone = _toneManager->getCurrentTone();

	_updatePlaybackGui();
	_updateAmplitudeGui("sin", currentTone->sineAmplitudes, currentTone->sineToggles);
	_updateAmplitudeGui("sqr", currentTone->squareAmplitudes, currentTone->squareToggles);
	_updateAmplitudeGui("tri", currentTone->triangleAmplitudes, currentTone->triangleToggles);
	_updateAmplitudeGui("saw", currentTone->sawtoothAmplitudes, currentTone->sawtoothToggles);
}

void ToneEditorController::_updatePlaybackGui()
{
	for(int index = 0; index < ToneConstants::NOTE_COUNT; index++)
	{
		if(_guiManager->getGuiButton("tone_editor_note" + to_string(index))->isPressed())
		{
			if(_waveformPlayer->isStarted())
			{
				_waveformPlayer->stop();
			}

			const shared_ptr<Tone> currentTone = _toneManager->getCurrentTone();

			currentTone->note = static_cast<NoteType>(index);

			vector<shared_ptr<Waveform>> waveforms = _waveformGenerator->generateWaveforms(currentTone);

			currentTone->note = ToneConstants::DEFAULT_NOTE_TYPE;

			if(!waveforms.empty())
			{
				const shared_ptr<Waveform> waveform = _waveformGenerator->combineWaveforms(waveforms);

				_waveformPlayer->start(waveform);
			}

			break;
		}
	}
}

void ToneEditorController::_updateAmplitudeGui(const string & type, vector<int> & amplitudes, vector<bool> & toggles)
{
	for(int octave = 0; octave < ToneConstants::OCTAVE_COUNT; octave++)
	{
		if(_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(octave))->isPressed())
		{
			amplitudes.at(octave)--;

			_refreshWaveformVisualization();
		}
		else if(_guiManager->getGuiButton("tone_editor_" + type + "_txt" + to_string(octave))->isPressed())
		{
			toggles.at(octave) = !toggles.at(octave);

			_refreshWaveformVisualization();
		}
		else if(_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(octave))->isPressed())
		{
			amplitudes.at(octave)++;

			_refreshWaveformVisualization();
		}

		_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(octave))->setPressable(amplitudes.at(octave) > 0);
		_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(octave))->setHoverable(amplitudes.at(octave) > 0);
		_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(octave))->setVisible(toggles.at(octave));
		_guiManager->getGuiLabel("tone_editor_" + type + "_val" + to_string(octave))->setVisible(toggles.at(octave));
		_guiManager->getGuiLabel("tone_editor_" + type + "_val" + to_string(octave))->setContent(to_string(amplitudes.at(octave)));
		_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(octave))->setPressable(amplitudes.at(octave) < 9);
		_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(octave))->setHoverable(amplitudes.at(octave) < 9);
		_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(octave))->setVisible(toggles.at(octave));
		_guiManager->getGuiButton("tone_editor_" + type + "_txt" + to_string(octave))->setHighlighted(toggles.at(octave));
	}
}

void ToneEditorController::_setGuiVisible(const bool value)
{
	_guiManager->getGuiRectangle("tone_editor_frame")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_close")->setVisible(value);
	_guiManager->getGuiWaveform("tone_editor_wave")->setVisible(value);

	for(int index = 0; index < ToneConstants::NOTE_COUNT; index++)
	{
		_guiManager->getGuiButton("tone_editor_note" + to_string(index))->setVisible(value);
	}

	for(int octave = 0; octave < ToneConstants::OCTAVE_COUNT; octave++)
	{
		for(const string & type : {"sin", "sqr", "tri", "saw"})
		{
			_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(octave))->setVisible(value);
			_guiManager->getGuiLabel("tone_editor_" + type + "_val" + to_string(octave))->setVisible(value);
			_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(octave))->setVisible(value);
			_guiManager->getGuiButton("tone_editor_" + type + "_txt" + to_string(octave))->setVisible(value);
		}

		_guiManager->getGuiLabel("tone_editor_oct" + to_string(octave))->setVisible(value);
	}
}

void ToneEditorController::enable()
{
	_setGuiVisible(true);
	_refreshWaveformVisualization();

	_isEnabled = true;
}

void ToneEditorController::_refreshWaveformVisualization()
{
	vector<shared_ptr<Waveform>> waveforms = _waveformGenerator->generateWaveforms(_toneManager->getCurrentTone());

	if(waveforms.empty())
	{
		_guiManager->getGuiWaveform("tone_editor_wave")->setSamples({0.0f, 0.0f});
	}
	else
	{
		const shared_ptr<Waveform> waveform = _waveformGenerator->combineWaveforms(waveforms);
		const vector<double> samples = _waveformGenerator->extractSamplesFromWaveform(waveform);

		_guiManager->getGuiWaveform("tone_editor_wave")->setSamples(samples);
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

void ToneEditorController::inject(const shared_ptr<ToneManager> & toneManager)
{
	_toneManager = toneManager;
}