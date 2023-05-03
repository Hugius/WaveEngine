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

	const shared_ptr<ToneTemplate> currentToneTemplate = _toneTemplateManager->getToneTemplate();

	_updatePlaybackGui();
	_updateAmplitudeGui("sin", currentToneTemplate->sineAmplitudes, currentToneTemplate->sineToggles);
	_updateAmplitudeGui("sqr", currentToneTemplate->squareAmplitudes, currentToneTemplate->squareToggles);
	_updateAmplitudeGui("tri", currentToneTemplate->triangleAmplitudes, currentToneTemplate->triangleToggles);
	_updateAmplitudeGui("saw", currentToneTemplate->sawtoothAmplitudes, currentToneTemplate->sawtoothToggles);
}

void ToneEditorController::_updatePlaybackGui()
{
	bool isHeld = false;

	for(int index = 0; index < ToneConstants::NOTE_COUNT; index++)
	{
		if(_guiManager->getGuiButton("tone_editor_note" + to_string(index))->isHeld())
		{
			isHeld = true;

			if(_waveformPlayer->isStarted())
			{
				break;
			}

			shared_ptr<Tone> tone = make_shared<Tone>(_toneTemplateManager->getToneTemplate());
			tone->setNoteIndex(index);
			tone->setDuration(TONE_DURATION);

			vector<shared_ptr<Waveform>> waveforms = _waveformGenerator->generateWaveforms(tone);

			if(!waveforms.empty())
			{
				const shared_ptr<Waveform> waveform = _waveformGenerator->combineWaveforms(waveforms);

				_waveformPlayer->start(waveform, true);
			}

			break;
		}
	}

	if(!isHeld && _waveformPlayer->isStarted())
	{
		_waveformPlayer->stop();
	}
}

void ToneEditorController::_updateAmplitudeGui(const string & type, array<int, ToneConstants::OCTAVE_COUNT> & amplitudes, array<bool, ToneConstants::OCTAVE_COUNT> & toggles)
{
	for(int index = 0; index < ToneConstants::OCTAVE_COUNT; index++)
	{
		if(_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->isPressed())
		{
			amplitudes.at(index)--;

			_refreshWaveformVisualization();
		}
		else if(_guiManager->getGuiButton("tone_editor_" + type + "_txt" + to_string(index))->isPressed())
		{
			toggles.at(index) = !toggles.at(index);

			_refreshWaveformVisualization();
		}
		else if(_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->isPressed())
		{
			amplitudes.at(index)++;

			_refreshWaveformVisualization();
		}

		_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->setPressable(amplitudes.at(index) > 0);
		_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->setHoverable(amplitudes.at(index) > 0);
		_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->setVisible(toggles.at(index));
		_guiManager->getGuiLabel("tone_editor_" + type + "_val" + to_string(index))->setVisible(toggles.at(index));
		_guiManager->getGuiLabel("tone_editor_" + type + "_val" + to_string(index))->setContent(to_string(amplitudes.at(index)));
		_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->setPressable(amplitudes.at(index) < 9);
		_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->setHoverable(amplitudes.at(index) < 9);
		_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->setVisible(toggles.at(index));
		_guiManager->getGuiButton("tone_editor_" + type + "_txt" + to_string(index))->setHighlighted(toggles.at(index));
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

	for(int index = 0; index < ToneConstants::OCTAVE_COUNT; index++)
	{
		for(const string & type : {"sin", "sqr", "tri", "saw"})
		{
			_guiManager->getGuiButton("tone_editor_" + type + "_decr" + to_string(index))->setVisible(value);
			_guiManager->getGuiLabel("tone_editor_" + type + "_val" + to_string(index))->setVisible(value);
			_guiManager->getGuiButton("tone_editor_" + type + "_incr" + to_string(index))->setVisible(value);
			_guiManager->getGuiButton("tone_editor_" + type + "_txt" + to_string(index))->setVisible(value);
		}

		_guiManager->getGuiLabel("tone_editor_oct" + to_string(index))->setVisible(value);
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
	shared_ptr<Tone> tone = make_shared<Tone>(_toneTemplateManager->getToneTemplate());
	tone->setNoteIndex(ToneConstants::VISUALIZATION_NOTE_INDEX);
	tone->setDuration(ToneConstants::VISUALIZATION_TONE_DURATION);

	vector<shared_ptr<Waveform>> waveforms = _waveformGenerator->generateWaveforms(tone);

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

void ToneEditorController::inject(const shared_ptr<ToneTemplateManager> & toneTemplateManager)
{
	_toneTemplateManager = toneTemplateManager;
}