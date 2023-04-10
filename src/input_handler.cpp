#include "input_handler.hpp"

void InputHandler::sendMouseDownEvent()
{
	_isMouseButtonPressed = true;
}

void InputHandler::sendMouseUpEvent()
{
	_isMouseButtonPressed = false;
}

const bool InputHandler::isMouseButtonPressed() const
{
	return _isMouseButtonPressed;
}