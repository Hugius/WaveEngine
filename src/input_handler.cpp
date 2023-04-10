#include "input_handler.hpp"

void InputHandler::sendMouseButtonDownEvent()
{
	_isMouseButtonPressed = true;
}

void InputHandler::update()
{
	_isMouseButtonPressed = false;
}

const bool InputHandler::isMouseButtonPressed() const
{
	return _isMouseButtonPressed;
}