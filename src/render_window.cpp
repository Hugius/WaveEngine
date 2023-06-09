#define GLEW_STATIC

#include "render_window.hpp"
#include "tools.hpp"

#include <glew.h>
#include <wglew.h>

HDC windowContext = nullptr;
HGLRC openglContext = nullptr;

LRESULT CALLBACK processMessage(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_CREATE:
		{
			PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {};

			pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pixelFormatDescriptor.nVersion = 1;
			pixelFormatDescriptor.dwFlags = (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER);
			pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
			pixelFormatDescriptor.cColorBits = 32;
			pixelFormatDescriptor.cRedBits = 0;
			pixelFormatDescriptor.cRedShift = 0;
			pixelFormatDescriptor.cGreenBits = 0;
			pixelFormatDescriptor.cGreenShift = 0;
			pixelFormatDescriptor.cBlueBits = 0;
			pixelFormatDescriptor.cBlueShift = 0;
			pixelFormatDescriptor.cAlphaBits = 0;
			pixelFormatDescriptor.cAlphaShift = 0;
			pixelFormatDescriptor.cAccumBits = 0;
			pixelFormatDescriptor.cAccumRedBits = 0;
			pixelFormatDescriptor.cAccumGreenBits = 0;
			pixelFormatDescriptor.cAccumBlueBits = 0;
			pixelFormatDescriptor.cAccumAlphaBits = 0;
			pixelFormatDescriptor.cDepthBits = 24;
			pixelFormatDescriptor.cStencilBits = 8;
			pixelFormatDescriptor.cAuxBuffers = 0;
			pixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;
			pixelFormatDescriptor.bReserved = 0;
			pixelFormatDescriptor.dwLayerMask = 0;
			pixelFormatDescriptor.dwVisibleMask = 0;
			pixelFormatDescriptor.dwDamageMask = 0;

			windowContext = GetDC(handle);

			const int pixelFormat = ChoosePixelFormat(windowContext, &pixelFormatDescriptor);

			if(pixelFormat == 0)
			{
				abort();
			}

			SetPixelFormat(windowContext, pixelFormat, &pixelFormatDescriptor);

			openglContext = wglCreateContext(windowContext);

			wglMakeCurrent(windowContext, openglContext);

			break;
		}
		case WM_DESTROY:
		{
			wglDeleteContext(openglContext);
			ReleaseDC(handle, windowContext);
			PostQuitMessage(0);

			openglContext = nullptr;
			windowContext = nullptr;

			break;
		}
		default:
		{
			return DefWindowProc(handle, message, wParam, lParam);
		}
	}

	return 0;
}

RenderWindow::RenderWindow()
{
	if(!SetProcessDPIAware())
	{
		abort();
	}

	_initializeHandle();
	_initializeGlew();
}

void RenderWindow::update()
{
	_updateEvents();
	_updateCursorPosition();
}

void RenderWindow::_initializeHandle()
{
	WNDCLASS windowClass = {};
	windowClass.lpfnWndProc = processMessage;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.lpszClassName = TITLE.c_str();
	windowClass.style = CS_OWNDC;
	windowClass.hIcon = static_cast<HICON>(LoadImage(nullptr, ICON_PATH.c_str(), IMAGE_ICON, ICON_SIZE, ICON_SIZE, LR_LOADFROMFILE));

	if(!RegisterClass(&windowClass))
	{
		abort();
	}

	const ivec2 monitorResolution = _getMonitorResolution();
	const DWORD windowStyle = WS_BORDER | WS_CAPTION | WS_SYSMENU;

	_renderingResolution = static_cast<ivec2>(static_cast<dvec2>(monitorResolution) * 0.9);

	RECT rect = {};
	rect.left = 0;
	rect.top = 0;
	rect.right = _renderingResolution.x;
	rect.bottom = _renderingResolution.y;

	AdjustWindowRectEx(&rect, windowStyle, false, 0);

	const ivec2 windowResolution = ivec2(static_cast<int>(rect.right - rect.left), static_cast<int>(rect.bottom - rect.top));
	const ivec2 windowPosition = (monitorResolution - windowResolution) / 2;

	_handle = CreateWindow(
		windowClass.lpszClassName,
		TITLE.c_str(),
		windowStyle,
		windowPosition.x,
		windowPosition.y,
		windowResolution.x,
		windowResolution.y,
		GetDesktopWindow(),
		nullptr,
		windowClass.hInstance,
		nullptr);

	if(_handle == nullptr)
	{
		abort();
	}
}

void RenderWindow::_initializeGlew()
{
	const unsigned int glewStatus = glewInit();

	if(glewStatus != GLEW_OK)
	{
		abort();
	}

	wglSwapIntervalEXT(true);
}

void RenderWindow::_updateEvents()
{
	if(isClosed())
	{
		return;
	}

	MSG messageEvent = {};

	while(PeekMessage(&messageEvent, _handle, 0, 0, PM_REMOVE))
	{
		switch(messageEvent.message)
		{
			case WM_LBUTTONDOWN:
			{
				_inputHandler->setLmbDown();

				break;
			}
			default:
			{
				DispatchMessage(&messageEvent);

				break;
			}
		}
	}
}

void RenderWindow::_updateCursorPosition()
{
	if(isClosed())
	{
		return;
	}

	POINT point = {};

	if(!GetCursorPos(&point))
	{
		abort();
	}

	if(!ScreenToClient(_handle, &point))
	{
		abort();
	}

	_cursorPosition = _convertToNdc(ivec2(point.x, point.y));
}

void RenderWindow::swapBuffers()
{
	if(windowContext == nullptr)
	{
		return;
	}

	if(!wglSwapLayerBuffers(windowContext, WGL_SWAP_MAIN_PLANE))
	{
		abort();
	}
}

const bool RenderWindow::isClosed() const
{
	return !IsWindow(_handle);
}

const ivec2 RenderWindow::_getMonitorResolution()
{
	RECT rectangle = {};

	if(!GetWindowRect(GetDesktopWindow(), &rectangle))
	{
		abort();
	}

	return ivec2(rectangle.right, rectangle.bottom);
}

const dvec2 RenderWindow::getCursorPosition()
{
	return _cursorPosition;
}

const dvec2 RenderWindow::_convertToNdc(const ivec2 & position)
{
	const double x = static_cast<double>(position.x) / static_cast<double>(_renderingResolution.x);
	const double y = static_cast<double>(position.y) / static_cast<double>(_renderingResolution.y);

	dvec2 ndc = dvec2(x, y);

	ndc.x *= 2.0;
	ndc.y *= 2.0;
	ndc.x -= 1.0;
	ndc.y -= 1.0;
	ndc.y *= -1.0;

	return ndc;
}

void RenderWindow::inject(const shared_ptr<InputHandler> & inputHandler)
{
	if(inputHandler == nullptr)
	{
		abort();
	}

	_inputHandler = inputHandler;
}

void RenderWindow::show()
{
	ShowWindow(_handle, SW_SHOW);
	SetFocus(_handle);
}