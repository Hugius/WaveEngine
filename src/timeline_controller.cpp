#include "timeline_controller.hpp"
#include "mathematics.hpp"

using std::to_string;

void TimelineController::update()
{
	const int noteCount = Shared::NOTE_COUNT;
	const double separatorDistance = fabs(_guiManager->getGuiRectangle("timeline_separator0")->getQuad()->getPosition().y - _guiManager->getGuiRectangle("timeline_separator1")->getQuad()->getPosition().y);

	for(int index = 0; index < noteCount; index++)
	{
		if(_guiManager->getGuiButton("timeline_note" + to_string(index))->isPressed())
		{
			const shared_ptr<ToneTemplate> toneTemplate = _toneTemplateManager->getToneTemplate();
			const shared_ptr<Tone> tone = make_shared<Tone>(toneTemplate);
			const shared_ptr<Waveform> waveform = _waveformGenerator->generateWaveform(tone);
			const vector<double> samples = _waveformGenerator->extractSamplesFromWaveform(waveform);
			const dvec2 separatorPosition = _guiManager->getGuiRectangle("timeline_separator" + to_string(index))->getQuad()->getPosition();
			const dvec2 separatorSize = _guiManager->getGuiRectangle("timeline_separator" + to_string(index))->getQuad()->getSize();
			const dvec2 tonePosition = dvec2(separatorPosition.x, separatorPosition.y + separatorSize.y / 2.0);
			const dvec2 toneSize = dvec2(DURATION_MULTIPLIER * static_cast<double>(tone->getToneTemplate()->getDuration()), separatorDistance - separatorSize.y);

			_guiManager->addGuiButton("rterttr", tonePosition, toneSize, Colors::GRAY, Colors::LIGHT_GRAY, false, false, true, true, true);
			_guiManager->addGuiWaveform("rterttr", tonePosition + toneSize * 0.05, toneSize * 0.9, Colors::WHITE, false, false, true);
			_guiManager->getGuiWaveform("rterttr")->setSamples(samples);
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