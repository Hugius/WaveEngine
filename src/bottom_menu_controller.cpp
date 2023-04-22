#include "bottom_menu_controller.hpp"

using std::make_shared;
using std::to_string;

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
		_toneManager->addNewTone(make_shared<Tone>());
	}
	else if(_guiManager->getGuiButton("bottom_menu_prev")->isPressed())
	{
		_toneManager->selectPreviousTone();
	}
	else if(_guiManager->getGuiButton("bottom_menu_next")->isPressed())
	{
		_toneManager->selectNextTone();
	}
	else if(_guiManager->getGuiButton("bottom_menu_delete")->isPressed())
	{
		_toneManager->removeCurrentTone();
	}

	const int toneCount = _toneManager->getToneCount();
	const int toneIndex = _toneManager->getCurrentToneIndex();
	const string numberContent = (toneIndex < 9 ? "0" : "") + to_string(toneIndex + 1);

	_guiManager->getGuiButton("bottom_menu_create")->setHoverable(toneCount < MAX_TONES);
	_guiManager->getGuiButton("bottom_menu_create")->setPressable(toneCount < MAX_TONES);
	_guiManager->getGuiButton("bottom_menu_prev")->setHoverable(toneCount != 0 && toneIndex > 0);
	_guiManager->getGuiButton("bottom_menu_prev")->setPressable(toneCount != 0 && toneIndex > 0);
	_guiManager->getGuiButton("bottom_menu_next")->setHoverable(toneCount != 0 && toneIndex < toneCount - 1);
	_guiManager->getGuiButton("bottom_menu_next")->setPressable(toneCount != 0 && toneIndex < toneCount - 1);
	_guiManager->getGuiButton("bottom_menu_delete")->setHoverable(toneCount != 0);
	_guiManager->getGuiButton("bottom_menu_delete")->setPressable(toneCount != 0);
	_guiManager->getGuiLabel("bottom_menu_number")->setContent(toneCount == 0 ? "" : numberContent);

	if(toneCount > 0)
	{
		_refreshWaveformVisualization();
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