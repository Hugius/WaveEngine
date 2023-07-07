#include "timeline_controller.hpp"
#include "mathematics.hpp"

using std::to_string;

void TimelineController::update()
{
	const double CHAR_X = 0.0125;
	const double CHAR_Y = 0.05;
	const double x = -1.0;
	const double y = -0.75;
	const double height = 2.0 - 0.25 - CHAR_Y;
	const double separatorOffset = CHAR_X * 6.0;
	const int noteCount = Shared::NOTE_COUNT;
	const vector<double> notePositions = Mathematics::calculateDistributedPositions(y, height, noteCount, true);

	for(int index = 0; index < noteCount; index++)
	{
		if(_guiManager->getGuiButton("timeline_note" + to_string(index))->isPressed())
		{
			const shared_ptr<ToneTemplate> toneTemplate = _toneTemplateManager->getToneTemplate();
			const shared_ptr<Tone> tone = make_shared<Tone>(toneTemplate);
			const shared_ptr<Waveform> waveform = _waveformGenerator->generateWaveform(tone);
			const vector<double> samples = _waveformGenerator->extractSamplesFromWaveform(waveform);
			const dvec2 position = dvec2(x + separatorOffset + CHAR_X * 0.75, notePositions.at(index) + separatorOffset);
			const dvec2 size = dvec2(CHAR_X * (static_cast<double>(tone->getToneTemplate()->getDuration()) / 1.0), separatorOffset);

			_guiManager->addGuiButton("rterttr", position, size, Colors::NORMAL_GRAY, Colors::LIGHT_GRAY, false, true, true, true, true);
			_guiManager->addGuiWaveform("rterttr", position, size, Colors::WHITE, false, true, true);
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