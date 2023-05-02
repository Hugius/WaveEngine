#include "input_handler.hpp"

void InputHandler::setLmbDown()
{
	_isLmbPressed = true;
	_isLmbHeld = true;
}

void InputHandler::setLmbUp()
{
	_isLmbHeld = false;
}

void InputHandler::update()
{
	_isLmbPressed = false;
}

const bool InputHandler::isLmbPressed() const
{
	return _isLmbPressed;
}

const bool InputHandler::isLmbHeld() const
{
	return _isLmbHeld;
}