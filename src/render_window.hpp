#pragma once

#include "ivec2.hpp"
#include "dvec2.hpp"
#include "input_handler.hpp"
#include "dvec3.hpp"

#include <string>
#include <windows.h>
#include <memory>

using std::shared_ptr;
using std::string;

class RenderWindow final
{
public:
	void inject(const shared_ptr<InputHandler> inputHandler);
	void initialize();
	void update();
	void swapBuffers();

	const fvec2 getCursorPosition();

	const bool isClosed() const;

private:
	void _initializeHandle();
	void _initializeGlew();
	void _updateEvents();
	void _updateCursorPosition();

	static inline const string ICON_PATH = "icons\\logo.ico";
	static inline const string TITLE = "WaveEngine";

	const fvec2 _convertToNdc(const ivec2 & position);

	const ivec2 _getMonitorResolution();

	shared_ptr<InputHandler> _inputHandler = nullptr;

	HWND _handle = nullptr;

	fvec2 _cursorPosition = fvec2(0.0);
	ivec2 _renderingResolution = ivec2(0);
};