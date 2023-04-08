#pragma once

#include "render_window.hpp"
#include "timer.hpp"
#include "image_loader.hpp"
#include "renderer.hpp"
#include "gui_manager.hpp"
#include "gui_controller.hpp"
#include "waveform_generator.hpp"
#include "audio_player.hpp"

class EngineOrchestrator final
{
public:
	void initialize();
	void start();
	void stop();

private:
	void _update();
	void _render();

	static inline const float MAX_RUNTIME_LAG = 100.0f;

	shared_ptr<RenderWindow> _renderWindow = nullptr;
	shared_ptr<InputHandler> _inputHandler = nullptr;
	shared_ptr<Timer> _timer = nullptr;
	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<Renderer> _renderer = nullptr;
	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<GuiController> _guiController = nullptr;
	shared_ptr<WaveformGenerator> _waveformGenerator = nullptr;
	shared_ptr<AudioPlayer> _audioPlayer = nullptr;
	shared_ptr<AudioManager> _audioManager = nullptr;

	float _totalDeltaTime = 0.0f;

	bool _isRunning = false;
};