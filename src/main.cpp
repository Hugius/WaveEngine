#include "engine_orchestrator.hpp"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	EngineOrchestrator engineOrchestrator;

	engineOrchestrator.start();

	return 0;
}