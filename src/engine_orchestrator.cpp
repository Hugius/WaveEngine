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
	_topMenuController(make_shared<TopMenuController>()),
	_bottomMenuController(make_shared<BottomMenuController>()),
	_waveformGenerator(make_shared<WaveformGenerator>()),
	_waveformPlayer(make_shared<WaveformPlayer>()),
	_toneManager(make_shared<ToneManager>()),
	_lineRenderer(make_shared<LineRenderer>()),
	_toneEditorController(make_shared<ToneEditorController>())
{
	_renderWindow->inject(_inputHandler);
	_guiManager->inject(_imageLoader);
	_toneEditorController->inject(_guiManager);
	_toneEditorController->inject(_waveformGenerator);
	_toneEditorController->inject(_waveformPlayer);
	_topMenuController->inject(_guiManager);
	_topMenuController->inject(_toneManager);
	_topMenuController->inject(_toneEditorController);
	_bottomMenuController->inject(_guiManager);
	_bottomMenuController->inject(_toneManager);
	_bottomMenuController->inject(_waveformGenerator);

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
	_topMenuController->update();
	_bottomMenuController->update();
	_toneEditorController->update();
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