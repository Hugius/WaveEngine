#include "input_handler.hpp"

void InputHandler::setLmbPressed()
{
	_isLmbPressed = true;
}

void InputHandler::update()
{
	_isLmbPressed = false;
}

const bool InputHandler::isLmbPressed() const
{
	return _isLmbPressed;
}