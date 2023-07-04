#include "timeline_controller.hpp"
#include "mathematics.hpp"

using std::to_string;

static inline const double CHAR_X = 0.0125;
static inline const double CHAR_Y = 0.05;

void TimelineController::update()
{
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
			const dvec2 waveformX = dvec2(x + separatorOffset + CHAR_X * 0.75, notePositions.at(index) + separatorOffset / 2.0);
			const dvec2 waveformY = dvec2(CHAR_X * (static_cast<double>(tone->getToneTemplate()->getDuration()) / 10.0), CHAR_Y * 3.0);

			_guiManager->addGuiWaveform("rterttr", waveformX, waveformY, Shared::WHITE, false, false, true);
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