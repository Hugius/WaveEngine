#include "engine_orchestrator.hpp"
#include "tools.hpp"

using std::make_shared;

EngineOrchestrator::EngineOrchestrator()
	:
	_renderWindow(make_shared<RenderWindow>()),
	_inputHandler(make_shared<InputHandler>()),
	_timer(make_shared<Timer>()),
	_imageLoader(make_shared<ImageLoader>()),
	_quadRenderer(make_shared<QuadRenderer>()),
	_guiManager(make_shared<GuiManager>()),
	_guiController(make_shared<GuiController>()),
	_waveformGenerator(make_shared<WaveformGenerator>()),
	_audioPlayer(make_shared<AudioPlayer>()),
	_audioManager(make_shared<AudioManager>()),
	_lineRenderer(make_shared<LineRenderer>())
{
	_renderWindow->inject(_inputHandler);
	_guiManager->inject(_imageLoader);
	_guiController->inject(_guiManager);
	_guiController->inject(_waveformGenerator);
	_guiController->inject(_audioPlayer);
	_guiController->inject(_audioManager);

	_guiManager->initialize();

	_update();
}

void EngineOrchestrator::start()
{
	if(_isRunning)
	{
		abort();
	}

	_isRunning = true;

	double runtimeLag = 0.0;

	while(true)
	{
		_timer->start();

		const double millisecondsPerUpdate = 1000.0 / _timer->getUpdateCountPerSecond();

		runtimeLag += _totalDeltaTime;
		runtimeLag = min(MAX_RUNTIME_LAG, runtimeLag);

		while(runtimeLag >= millisecondsPerUpdate)
		{
			_update();

			runtimeLag = max(0.0, runtimeLag - millisecondsPerUpdate);

			if(!_isRunning)
			{
				break;
			}
		}

		if(!_isRunning)
		{
			break;
		}

		_render();

		_timer->stop();

		_totalDeltaTime = _timer->getDeltaTime();
	}
}

void EngineOrchestrator::stop()
{
	if(!_isRunning)
	{
		abort();
	}

	_isRunning = false;
}

void EngineOrchestrator::_update()
{
	if(_renderWindow->isClosed())
	{
		return stop();
	}

	_inputHandler->update();
	_renderWindow->update();
	_guiController->update();
	_guiManager->update(_renderWindow->getCursorPosition(), _inputHandler->isLmbPressed());
}

void EngineOrchestrator::_render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	_quadRenderer->render(_guiManager->getQuads());
	_quadRenderer->render(_guiManager->getTexts());
	_lineRenderer->render(_guiManager->getLines());
	_renderWindow->swapBuffers();
}