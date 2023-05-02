#pragma once

#include "render_window.hpp"
#include "timer.hpp"
#include "image_loader.hpp"
#include "quad_renderer.hpp"
#include "gui_manager.hpp"
#include "top_menu_controller.hpp"
#include "waveform_generator.hpp"
#include "waveform_player.hpp"
#include "line_renderer.hpp"
#include "bottom_menu_controller.hpp"

class EngineOrchestrator final
{
public:
	EngineOrchestrator();

	void start();
	void stop();

private:
	void _update();
	void _render();

	static inline const double MAX_RUNTIME_LAG = 100.0;

	const shared_ptr<RenderWindow> _renderWindow;
	const shared_ptr<InputHandler> _inputHandler;
	const shared_ptr<Timer> _timer;
	const shared_ptr<ImageLoader> _imageLoader;
	const shared_ptr<QuadRenderer> _quadRenderer;
	const shared_ptr<GuiManager> _guiManager;
	const shared_ptr<TopMenuController> _topMenuController;
	const shared_ptr<BottomMenuController> _bottomMenuController;
	const shared_ptr<WaveformGenerator> _waveformGenerator;
	const shared_ptr<WaveformPlayer> _waveformPlayer;
	const shared_ptr<ToneEditorController> _toneEditorController;
	const shared_ptr<ToneTemplateManager> _toneTemplateManager;
	const shared_ptr<LineRenderer> _lineRenderer;

	double _totalDeltaTime = 0.0;

	bool _isRunning = false;
};