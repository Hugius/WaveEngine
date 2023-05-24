#include "timeline_controller.hpp"

using std::to_string;

void TimelineController::update()
{
	const int noteCount = Shared::NOTE_COUNT;

	for(int index = 0; index < noteCount; index++)
	{
		if(_guiManager->getGuiButton("timeline_note" + to_string(index))->isPressed())
		{
			shared_ptr<Tone> tone = make_shared<Tone>(_toneTemplateManager->getToneTemplate());
			shared_ptr<Waveform> waveform = _waveformGenerator->generateWaveform(tone);

			if(waveform == nullptr)
			{
				_guiManager->getGuiWaveform("tone_editor_waveform")->setSamples({0.0f, 0.0f});
			}
			else
			{
				const vector<double> samples = _waveformGenerator->extractSamplesFromWaveform(waveform);

				_guiManager->getGuiWaveform("tone_editor_waveform")->setSamples(samples);
			}
		}
	}
}

void TimelineController::inject(const shared_ptr<GuiManager> & guiManager)
{
	if(guiManager == nullptr)
	{
		abort();
	}

	_guiManager = guiManager;
}

void TimelineController::inject(const shared_ptr<ToneTemplateManager> & toneTemplateManager)
{
	if(toneTemplateManager == nullptr)
	{
		abort();
	}

	_toneTemplateManager = toneTemplateManager;
}

void TimelineController::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	if(waveformGenerator == nullptr)
	{
		abort();
	}

	_waveformGenerator = waveformGenerator;
}

void TimelineController::inject(const shared_ptr<ToneManager> & toneManager)
{
	if(toneManager == nullptr)
	{
		abort();
	}

	_toneManager = toneManager;
}