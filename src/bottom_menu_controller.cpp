#include "bottom_menu_controller.hpp"
#include "shared_constants.hpp"

using std::make_shared;
using std::to_string;

void BottomMenuController::update()
{
	int toneCount = _toneTemplateManager->getToneTemplateCount();
	int toneIndex = _toneTemplateManager->getToneTemplateIndex();

	if(_guiManager->getGuiButton("bottom_menu_create")->isPressed())
	{
		_toneTemplateManager->addToneTemplate(make_shared<ToneTemplate>());

		toneCount++;

		_toneTemplateManager->setToneTemplateIndex(toneCount - 1);

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("bottom_menu_previous")->isPressed())
	{
		toneIndex--;

		_toneTemplateManager->setToneTemplateIndex(toneIndex);

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("bottom_menu_next")->isPressed())
	{
		toneIndex++;

		_toneTemplateManager->setToneTemplateIndex(toneIndex);

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("bottom_menu_delete")->isPressed())
	{
		_toneTemplateManager->removeToneTemplate();

		_refreshWaveformVisualization();
	}
	else if(_guiManager->getGuiButton("tone_editor_close")->isPressed())
	{
		_refreshWaveformVisualization();
	}

	_guiManager->getGuiButton("bottom_menu_create")->setHoverable(toneCount < MAX_TONES);
	_guiManager->getGuiButton("bottom_menu_create")->setPressable(toneCount < MAX_TONES);
	_guiManager->getGuiButton("bottom_menu_previous")->setHoverable(toneCount != 0 && toneIndex > 0);
	_guiManager->getGuiButton("bottom_menu_previous")->setPressable(toneCount != 0 && toneIndex > 0);
	_guiManager->getGuiButton("bottom_menu_next")->setHoverable(toneCount != 0 && toneIndex < toneCount - 1);
	_guiManager->getGuiButton("bottom_menu_next")->setPressable(toneCount != 0 && toneIndex < toneCount - 1);
	_guiManager->getGuiButton("bottom_menu_delete")->setHoverable(toneCount != 0);
	_guiManager->getGuiButton("bottom_menu_delete")->setPressable(toneCount != 0);
	_guiManager->getGuiLabel("bottom_menu_number")->setContent(toneCount == 0 ? "  " : ((toneIndex < 9 ? "0" : "") + to_string(toneIndex + 1)));
}

void BottomMenuController::_refreshWaveformVisualization()
{
	if(_toneTemplateManager->getToneTemplateCount() == 0)
	{
		_guiManager->getGuiWaveform("bottom_menu_waveform")->setVisible(false);

		return;
	}

	_guiManager->getGuiWaveform("bottom_menu_waveform")->setVisible(true);

	vector<shared_ptr<Waveform>> waveforms = _waveformGenerator->generateWaveforms(make_shared<Tone>(_toneTemplateManager->getToneTemplate()));

	if(waveforms.empty())
	{
		_guiManager->getGuiWaveform("bottom_menu_waveform")->setSamples({0.0f, 0.0f});
	}
	else
	{
		const shared_ptr<Waveform> waveform = _waveformGenerator->combineWaveforms(waveforms);
		const vector<double> samples = _waveformGenerator->extractSamplesFromWaveform(waveform);

		_guiManager->getGuiWaveform("bottom_menu_waveform")->setSamples(samples);
	}
}

void BottomMenuController::inject(const shared_ptr<GuiManager> & guiManager)
{
	if(guiManager == nullptr)
	{
		abort();
	}

	_guiManager = guiManager;
}

void BottomMenuController::inject(const shared_ptr<ToneTemplateManager> & toneTemplateManager)
{
	if(toneTemplateManager == nullptr)
	{
		abort();
	}

	_toneTemplateManager = toneTemplateManager;
}

void BottomMenuController::inject(const shared_ptr<WaveformGenerator> & waveformGenerator)
{
	if(waveformGenerator == nullptr)
	{
		abort();
	}

	_waveformGenerator = waveformGenerator;
}