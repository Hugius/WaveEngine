#pragma once

#include "tone_editor.hpp"

using std::unique_ptr;

class GuiController final
{
public:
	GuiController();

	void inject(const shared_ptr<GuiManager> & guiManager);
	void inject(const shared_ptr<WaveformGenerator> & waveformGenerator);
	void inject(const shared_ptr<WaveformPlayer> & waveformPlayer);
	void inject(const shared_ptr<ToneManager> & toneManager);
	void update();

private:
	const unique_ptr<ToneEditor> _toneEditor;

	shared_ptr<GuiManager> _guiManager = nullptr;
};