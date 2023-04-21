#include "bottom_menu_controller.hpp"

using std::make_shared;

void BottomMenuController::inject(const shared_ptr<GuiManager> & guiManager)
{
	_guiManager = guiManager;
}

void BottomMenuController::inject(const shared_ptr<ToneManager> & toneManager)
{
	_toneManager = toneManager;
}

void BottomMenuController::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	_waveformGenerator = waveformGenerator;
}

void BottomMenuController::update()
{
	if(_guiManager->getGuiButton("bottom_menu_create")->isPressed())
	{
		_toneManager->addTone(make_shared<Tone>());

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("bottom_menu_delete")->isPressed())
	{

	}
}

void BottomMenuController::_refreshWaveformVisualization()
{
	vector<shared_ptr<Waveform>> waveforms = _waveformGenerator->generateWaveforms(_toneManager->getCurrentTone(), 10);

	if(waveforms.empty())
	{
		_guiManager->getGuiWaveform("bottom_menu_visualization")->setSamples({0.0f, 0.0f});
	}
	else
	{
		const shared_ptr<Waveform> waveform = _waveformGenerator->combineWaveforms(waveforms);
		const vector<double> samples = _waveformGenerator->extractSamplesFromWaveform(waveform);

		_guiManager->getGuiWaveform("bottom_menu_visualization")->setSamples(samples);
	}
}