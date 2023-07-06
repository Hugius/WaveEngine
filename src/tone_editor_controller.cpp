#include "tone_editor_controller.hpp"
#include "shared.hpp"

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

	_updateNoteGui();
	_updateAttackGui();
	_updateDurationGui();
	_updateReleaseGui();
	_updateAmplitudeGui();
}

void ToneEditorController::_updateNoteGui()
{
	for(int index = 0; index < Shared::NOTE_COUNT; index++)
	{
		if(_guiManager->getGuiButton("tone_editor_note" + to_string(index))->isPressed())
		{
			if(_waveformPlayer->isStarted())
			{
				_waveformPlayer->stop();
			}

			shared_ptr<Tone> tone = make_shared<Tone>(_toneTemplateManager->getToneTemplate());

			tone->setNoteIndex(index);

			shared_ptr<Waveform> waveform = _waveformGenerator->generateWaveform(tone);

			if(waveform != nullptr)
			{
				_waveformPlayer->start(waveform, false);
			}

			break;
		}
	}
}

void ToneEditorController::_updateAttackGui()
{
	const shared_ptr<ToneTemplate> currentToneTemplate = _toneTemplateManager->getToneTemplate();

	if(_guiManager->getGuiButton("tone_editor_attack_decrease")->isPressed())
	{
		currentToneTemplate->setAttack(currentToneTemplate->getAttack() - ATTACK_STEP);

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("tone_editor_attack_increase")->isPressed())
	{
		currentToneTemplate->setAttack(currentToneTemplate->getAttack() + ATTACK_STEP);

		_refreshWaveformVisualization();
	}

	const string valueContent = (currentToneTemplate->getAttack() == 0 ? "00" : currentToneTemplate->getAttack() < 100 ? "0" : "") + to_string(currentToneTemplate->getAttack());
	const bool isDecreasable = currentToneTemplate->getAttack() > MIN_TONE_ATTACK;
	const bool isIncreasable = currentToneTemplate->getAttack() < min(MAX_TONE_ATTACK, min(currentToneTemplate->getDuration(), currentToneTemplate->getRelease()));

	_guiManager->getGuiButton("tone_editor_attack_decrease")->setPressable(isDecreasable);
	_guiManager->getGuiButton("tone_editor_attack_decrease")->setHoverable(isDecreasable);
	_guiManager->getGuiLabel("tone_editor_attack_value")->setContent(valueContent);
	_guiManager->getGuiButton("tone_editor_attack_increase")->setPressable(isIncreasable);
	_guiManager->getGuiButton("tone_editor_attack_increase")->setHoverable(isIncreasable);
}

void ToneEditorController::_updateDurationGui()
{
	const shared_ptr<ToneTemplate> currentToneTemplate = _toneTemplateManager->getToneTemplate();

	if(_guiManager->getGuiButton("tone_editor_duration_decrease")->isPressed())
	{
		currentToneTemplate->setDuration(currentToneTemplate->getDuration() - DURATION_STEP);

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("tone_editor_duration_increase")->isPressed())
	{
		currentToneTemplate->setDuration(currentToneTemplate->getDuration() + DURATION_STEP);

		_refreshWaveformVisualization();
	}

	const string valueContent = (currentToneTemplate->getDuration() < 100 ? "0" : "") + to_string(currentToneTemplate->getDuration());
	const bool isDecreasable = currentToneTemplate->getDuration() > max(Shared::MIN_TONE_DURATION, currentToneTemplate->getRelease());
	const bool isIncreasable = currentToneTemplate->getDuration() < Shared::MAX_TONE_DURATION;

	_guiManager->getGuiButton("tone_editor_duration_decrease")->setPressable(isDecreasable);
	_guiManager->getGuiButton("tone_editor_duration_decrease")->setHoverable(isDecreasable);
	_guiManager->getGuiLabel("tone_editor_duration_value")->setContent(valueContent);
	_guiManager->getGuiButton("tone_editor_duration_increase")->setPressable(isIncreasable);
	_guiManager->getGuiButton("tone_editor_duration_increase")->setHoverable(isIncreasable);
}

void ToneEditorController::_updateReleaseGui()
{
	const shared_ptr<ToneTemplate> currentToneTemplate = _toneTemplateManager->getToneTemplate();

	if(_guiManager->getGuiButton("tone_editor_release_decrease")->isPressed())
	{
		currentToneTemplate->setRelease(currentToneTemplate->getRelease() - RELEASE_STEP);

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("tone_editor_release_increase")->isPressed())
	{
		currentToneTemplate->setRelease(currentToneTemplate->getRelease() + RELEASE_STEP);

		_refreshWaveformVisualization();
	}

	const string valueContent = (currentToneTemplate->getRelease() == 0 ? "00" : currentToneTemplate->getRelease() < 100 ? "0" : "") + to_string(currentToneTemplate->getRelease());
	const bool isDecreasable = currentToneTemplate->getRelease() > max(MIN_TONE_RELEASE, currentToneTemplate->getAttack());
	const bool isIncreasable = currentToneTemplate->getRelease() < min(MAX_TONE_RELEASE, currentToneTemplate->getDuration());

	_guiManager->getGuiButton("tone_editor_release_decrease")->setPressable(isDecreasable);
	_guiManager->getGuiButton("tone_editor_release_decrease")->setHoverable(isDecreasable);
	_guiManager->getGuiLabel("tone_editor_release_value")->setContent(valueContent);
	_guiManager->getGuiButton("tone_editor_release_increase")->setPressable(isIncreasable);
	_guiManager->getGuiButton("tone_editor_release_increase")->setHoverable(isIncreasable);
}

void ToneEditorController::_updateAmplitudeGui()
{
	const shared_ptr<ToneTemplate> currentToneTemplate = _toneTemplateManager->getToneTemplate();

	for(const string & type : {"sine", "square", "triangle", "sawtooth"})
	{
		array<int, Shared::OCTAVE_COUNT> amplitudes;
		array<bool, Shared::OCTAVE_COUNT> toggles;

		if(type == "sine")
		{
			amplitudes = currentToneTemplate->getSineAmplitudes();
			toggles = currentToneTemplate->getSineToggles();
		}
		else if(type == "square")
		{
			amplitudes = currentToneTemplate->getSquareAmplitudes();
			toggles = currentToneTemplate->getSquareToggles();
		}
		else if(type == "triangle")
		{
			amplitudes = currentToneTemplate->getTriangleAmplitudes();
			toggles = currentToneTemplate->getTriangleToggles();
		}
		else
		{
			amplitudes = currentToneTemplate->getSawtoothAmplitudes();
			toggles = currentToneTemplate->getSawtoothToggles();
		}

		bool isGuiButtonPressed = false;

		for(int index = 0; index < Shared::OCTAVE_COUNT; index++)
		{
			if(_guiManager->getGuiButton("tone_editor_" + type + "_decrease" + to_string(index))->isPressed())
			{
				amplitudes.at(index)--;

				isGuiButtonPressed = true;
			}
			else if(_guiManager->getGuiButton("tone_editor_" + type + "_text" + to_string(index))->isPressed())
			{
				toggles.at(index) = !toggles.at(index);

				isGuiButtonPressed = true;
			}
			else if(_guiManager->getGuiButton("tone_editor_" + type + "_increase" + to_string(index))->isPressed())
			{
				amplitudes.at(index)++;

				isGuiButtonPressed = true;
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

		if(isGuiButtonPressed)
		{
			if(type == "sine")
			{
				currentToneTemplate->setSineAmplitudes(amplitudes);
				currentToneTemplate->setSineToggles(toggles);
			}
			else if(type == "square")
			{
				currentToneTemplate->setSquareAmplitudes(amplitudes);
				currentToneTemplate->setSquareToggles(toggles);
			}
			else if(type == "triangle")
			{
				currentToneTemplate->setTriangleAmplitudes(amplitudes);
				currentToneTemplate->setTriangleToggles(toggles);
			}
			else
			{
				currentToneTemplate->setSawtoothAmplitudes(amplitudes);
				currentToneTemplate->setSawtoothToggles(toggles);
			}

			_refreshWaveformVisualization();
		}
	}
}

void ToneEditorController::_setGuiVisible(const bool value)
{
	_guiManager->getGuiRectangle("tone_editor_background")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_close")->setVisible(value);
	_guiManager->getGuiWaveform("tone_editor_waveform")->setVisible(value);

	for(int index = 0; index < Shared::NOTE_COUNT; index++)
	{
		_guiManager->getGuiButton("tone_editor_note" + to_string(index))->setVisible(value);
	}

	_guiManager->getGuiButton("tone_editor_attack_decrease")->setVisible(value);
	_guiManager->getGuiLabel("tone_editor_attack_value")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_attack_increase")->setVisible(value);
	_guiManager->getGuiLabel("tone_editor_attack_text")->setVisible(value);

	_guiManager->getGuiButton("tone_editor_duration_decrease")->setVisible(value);
	_guiManager->getGuiLabel("tone_editor_duration_value")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_duration_increase")->setVisible(value);
	_guiManager->getGuiLabel("tone_editor_duration_text")->setVisible(value);

	_guiManager->getGuiButton("tone_editor_release_decrease")->setVisible(value);
	_guiManager->getGuiLabel("tone_editor_release_value")->setVisible(value);
	_guiManager->getGuiButton("tone_editor_release_increase")->setVisible(value);
	_guiManager->getGuiLabel("tone_editor_release_text")->setVisible(value);

	for(int index = 0; index < Shared::OCTAVE_COUNT; index++)
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
	shared_ptr<Tone> tone = make_shared<Tone>(_toneTemplateManager->getToneTemplate());
	shared_ptr<Waveform> waveform = _waveformGenerator->generateWaveform(tone);

	if(waveform == nullptr)
	{
		_guiManager->getGuiWaveform("tone_editor_waveform")->setSamples({0.0, 0.0});
	}
	else
	{
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