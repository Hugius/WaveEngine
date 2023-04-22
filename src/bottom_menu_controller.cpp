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
		_toneManager->addTone(make_shared<Tone>());

		_refreshGui();
	}
	else if(_guiManager->getGuiButton("bottom_menu_decr")->isPressed())
	{
		_toneManager->decreaseCurrentIndex();

		_refreshGui();
	}
	else if(_guiManager->getGuiButton("bottom_menu_incr")->isPressed())
	{
		_toneManager->increaseCurrentIndex();

		_refreshGui();
	}
	else if(_guiManager->getGuiButton("bottom_menu_delete")->isPressed())
	{

	}

	_refreshGui();

	const int toneCount = static_cast<int>(_toneManager->getTones().size());
	const int currentIndex = _toneManager->getCurrentIndex();

	_guiManager->getGuiButton("bottom_menu_create")->setHoverable(toneCount < 99);
	_guiManager->getGuiButton("bottom_menu_create")->setPressable(toneCount < 99);
	_guiManager->getGuiButton("bottom_menu_decr")->setHoverable(toneCount != 0 && currentIndex > 0);
	_guiManager->getGuiButton("bottom_menu_decr")->setPressable(toneCount != 0 && currentIndex > 0);
	_guiManager->getGuiButton("bottom_menu_incr")->setHoverable(toneCount != 0 && currentIndex < toneCount - 1);
	_guiManager->getGuiButton("bottom_menu_incr")->setPressable(toneCount != 0 && currentIndex < toneCount - 1);
	_guiManager->getGuiButton("bottom_menu_delete")->setHoverable(toneCount != 0);
	_guiManager->getGuiButton("bottom_menu_delete")->setPressable(toneCount != 0);
}

void BottomMenuController::_refreshGui()
{
	const string numberContent = to_string(_toneManager->getCurrentIndex() + 1);

	_guiManager->getGuiLabel("bottom_menu_number")->setContent(numberContent.size() == 1 ? "0" + numberContent : numberContent);

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