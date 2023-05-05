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

	_updateNoteGui();
	_updateDurationGui();
	_updateAmplitudeGui("sine", currentToneTemplate->sineAmplitudes, currentToneTemplate->sineToggles);
	_updateAmplitudeGui("square", currentToneTemplate->squareAmplitudes, currentToneTemplate->squareToggles);
	_updateAmplitudeGui("triangle", currentToneTemplate->triangleAmplitudes, currentToneTemplate->triangleToggles);
	_updateAmplitudeGui("sawtooth", currentToneTemplate->sawtoothAmplitudes, currentToneTemplate->sawtoothToggles);
}

void ToneEditorController::_updateNoteGui()
{
	for(int index = 0; index < ToneConstants::NOTE_COUNT; index++)
	{
		if(_guiManager->getGuiButton("tone_editor_note" + to_string(index))->isPressed())
		{
			if(_waveformPlayer->isStarted())
			{
				_waveformPlayer->stop();
			}

			shared_ptr<Tone> tone = make_shared<Tone>(_toneTemplateManager->getToneTemplate());

			tone->setNoteIndex(index);

			vector<shared_ptr<Waveform>> waveforms = _waveformGenerator->generateWaveforms(tone);

			if(!waveforms.empty())
			{
				const shared_ptr<Waveform> waveform = _waveformGenerator->combineWaveforms(waveforms);

				_waveformPlayer->start(waveform, false);
			}

			break;
		}
	}
}

void ToneEditorController::_updateDurationGui()
{
	const shared_ptr<ToneTemplate> currentToneTemplate = _toneTemplateManager->getToneTemplate();

	if(_guiManager->getGuiButton("tone_editor_duration_decrease")->isPressed())
	{
		currentToneTemplate->duration -= ToneConstants::DURATION_STEP;

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("tone_editor_duration_increase")->isPressed())
	{
		currentToneTemplate->duration += ToneConstants::DURATION_STEP;

		_refreshWaveformVisualization();
	}

	const string prefix = currentToneTemplate->duration < 99 ? "0" : "";

	_guiManager->getGuiButton("tone_editor_duration_decrease")->setPressable(currentToneTemplate->duration > ToneConstants::MIN_DURATION);
	_guiManager->getGuiLabel("tone_editor_duration_value")->setContent(prefix + to_string(currentToneTemplate->duration));
	_guiManager->getGuiButton("tone_editor_duration_increase")->setPressable(currentToneTemplate->duration < ToneConstants::MAX_DURATION);
}

void ToneEditorController::_updateAmplitudeGui(const string & type, array<int, ToneConstants::OCTAVE_COUNT> & amplitudes, array<bool, ToneConstants::OCTAVE_COUNT> & toggles)
{
	for(int index = 0; index < ToneConstants::OCTAVE_COUNT; index++)
	{
		if(_guiManager->getGuiButton("tone_editor_" + type + "_decrease" + to_string(index))->isPressed())
		{
			amplitudes.at(index)--;

			_refreshWaveformVisualization();
		}
		else if(_guiManager->getGuiButton("tone_editor_" + type + "_text" + to_string(index))->isPressed())
		{
			toggles.at(index) = !toggles.at(index);

			_refreshWaveformVisualization();
		}
		else if(_guiManager->getGuiButton("tone_editor_" + type + "_increase" + to_string(index))->isPressed())
		{
			amplitudes.at(index)++;

			_refreshWaveformVisualization();
		}

		_guiManager->getGuiButton("tone_editor_" + type + "_decrease" + to_string(index))->setPressable(amplitudes.at(index) > 0);
		_guiManager->getGuiButton("tone_editor_" + type + "_decrease" + to_string(index))->setHoverable(amplitudes.at(index) > 0);
		_guiManager->getGuiButton("tone_editor_" + type + "_decrease" + to_string(index))->setVisible(toggles.at(index));
		_guiManager->getGuiLabel("tone_editor_" + type + "_value" + to_string(index))->setVisible(toggles.at(index));
		_guiManager->getGuiLabel("tone_editor_" + type + "_value" + to_string(index))->setContent(to_string(amplitudes.at(index)));
		_guiManager->getGuiButton("tone_editor_" + type + "_increase" + to_string(index))->setPressable(amplitudes.at(index) < 9);
		_guiManager->getGuiButton("tone_editor_" + type + "_increase" + to_string(index))->setHoverable(amplitudes.at(index) < 9);
		_guiManager->getGuiButton("tone_editor_" + type + "_increase" + to_string(index))->setVisible(toggles.at(index));
		_guiManager->getGuiButton("tone_editor_" + type + "_text" + to_string(index))->setHighlighted(toggles.at(index));
	}
}

void ToneEditorController::_setGuiVisible(const bool value)
{
	_guiManager->getGuiRectangle("tone_editor_background")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_close")->setVisible(value);
	_guiManager->getGuiWaveform("tone_editor_waveform")->setVisible(value);

	for(int index = 0; index < ToneConstants::NOTE_COUNT; index++)
	{
		_guiManager->getGuiButton("tone_editor_note" + to_string(index))->setVisible(value);
	}

	_guiManager->getGuiButton("tone_editor_duration_decrease")->setVisible(value);
	_guiManager->getGuiLabel("tone_editor_duration_value")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_duration_increase")->setVisible(value);
	_guiManager->getGuiLabel("tone_editor_duration_text")->setVisible(value);

	for(int index = 0; index < ToneConstants::OCTAVE_COUNT; index++)
	{
		for(const string & type : {"sine", "square", "triangle", "sawtooth"})
		{
			_guiManager->getGuiButton("tone_editor_" + type + "_decrease" + to_string(index))->setVisible(value);
			_guiManager->getGuiLabel("tone_editor_" + type + "_value" + to_string(index))->setVisible(value);
			_guiManager->getGuiButton("tone_editor_" + type + "_increase" + to_string(index))->setVisible(value);
			_guiManager->getGuiButton("tone_editor_" + type + "_text" + to_string(index))->setVisible(value);
		}

		_guiManager->getGuiLabel("tone_editor_octave" + to_string(index))->setVisible(value);
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
	vector<shared_ptr<Waveform>> waveforms = _waveformGenerator->generateWaveforms(make_shared<Tone>(_toneTemplateManager->getToneTemplate()));

	if(waveforms.empty())
	{
		_guiManager->getGuiWaveform("tone_editor_waveform")->setSamples({0.0f, 0.0f});
	}
	else
	{
		const shared_ptr<Waveform> waveform = _waveformGenerator->combineWaveforms(waveforms);
		const vector<double> samples = _waveformGenerator->extractSamplesFromWaveform(waveform);

		_guiManager->getGuiWaveform("tone_editor_waveform")->setSamples(samples);
	}
}

void ToneEditorController::inject(const shared_ptr<GuiManager> & guiManager)
{
	if(guiManager == nullptr)
	{
		abort();
	}

	_guiManager = guiManager;
}

void ToneEditorController::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	if(waveformGenerator == nullptr)
	{
		abort();
	}

	_waveformGenerator = waveformGenerator;
}

void ToneEditorController::inject(const shared_ptr<WaveformPlayer> & waveformPlayer)
{
	if(waveformPlayer == nullptr)
	{
		abort();
	}

	_waveformPlayer = waveformPlayer;
}

void ToneEditorController::inject(const shared_ptr<ToneTemplateManager> & toneTemplateManager)
{
	if(toneTemplateManager == nullptr)
	{
		abort();
	}

	_toneTemplateManager = toneTemplateManager;
}