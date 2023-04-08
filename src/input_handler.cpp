#include "input_handler.hpp"

#include <shlobj_core.h>

void InputHandler::update()
{
	_scrolledMouseWheels.clear();
	_pressedMouseButtons.clear();
	_pressedKeyboardKeyTypes.clear();
	_toggledMouseButtons.clear();
	_toggledKeyboardKeyTypes.clear();

	for(const MouseWheelType & wheel : _mouseWheelEvents)
	{
		_scrolledMouseWheels.push_back(wheel);
	}

	for(const MouseButtonType & button : _mouseDownEvents)
	{
		if(!isMouseButtonHeld(button))
		{
			_heldMouseButtons.push_back(button);
			_pressedMouseButtons.push_back(button);
		}
	}

	for(const KeyboardKeyType & key : _keyboardDownEvents)
	{
		if(!isKeyboardKeyHeld(key))
		{
			_heldKeyboardKeyTypes.push_back(key);
			_pressedKeyboardKeyTypes.push_back(key);
		}
	}

	for(const MouseButtonType & button : _mouseUpEvents)
	{
		_heldMouseButtons.erase(remove(_heldMouseButtons.begin(), _heldMouseButtons.end(), button), _heldMouseButtons.end());
	}

	for(const KeyboardKeyType & key : _keyboardUpEvents)
	{
		_heldKeyboardKeyTypes.erase(remove(_heldKeyboardKeyTypes.begin(), _heldKeyboardKeyTypes.end(), key), _heldKeyboardKeyTypes.end());
	}

	for(const MouseButtonType & button : _mouseButtons)
	{
		if(GetKeyState(static_cast<int>(button)) & 1)
		{
			_toggledMouseButtons.push_back(button);
		}
	}

	for(const KeyboardKeyType & key : _keyboardKeys)
	{
		if(GetKeyState(static_cast<int>(key)) & 1)
		{
			_toggledKeyboardKeyTypes.push_back(key);
		}
	}

	_mouseWheelEvents.clear();
	_mouseDownEvents.clear();
	_mouseUpEvents.clear();
	_keyboardDownEvents.clear();
	_keyboardUpEvents.clear();
}

void InputHandler::sendMouseWheelEvent(const MouseWheelType wheel)
{
	_mouseWheelEvents.push_back(wheel);
}

void InputHandler::sendMouseDownEvent(const MouseButtonType button)
{
	_mouseDownEvents.push_back(button);
}

void InputHandler::sendMouseUpEvent(const MouseButtonType button)
{
	_mouseUpEvents.push_back(button);
}

void InputHandler::sendKeyboardDownEvent(const KeyboardKeyType key)
{
	_keyboardDownEvents.push_back(key);
}

void InputHandler::sendKeyboardUpEvent(const KeyboardKeyType key)
{
	_keyboardUpEvents.push_back(key);
}

const bool InputHandler::isKeyboardKeyHeld(const KeyboardKeyType key) const
{
	return find(_heldKeyboardKeyTypes.begin(), _heldKeyboardKeyTypes.end(), key) != _heldKeyboardKeyTypes.end();
}

const bool InputHandler::isKeyboardKeyPressed(const KeyboardKeyType key) const
{
	return find(_pressedKeyboardKeyTypes.begin(), _pressedKeyboardKeyTypes.end(), key) != _pressedKeyboardKeyTypes.end();
}

const bool InputHandler::isKeyboardKeyToggled(const KeyboardKeyType key) const
{
	return find(_toggledKeyboardKeyTypes.begin(), _toggledKeyboardKeyTypes.end(), key) != _toggledKeyboardKeyTypes.end();
}

const bool InputHandler::isMouseWheelScrolled(const MouseWheelType wheel) const
{
	return find(_scrolledMouseWheels.begin(), _scrolledMouseWheels.end(), wheel) != _scrolledMouseWheels.end();
}

const bool InputHandler::isMouseButtonHeld(const MouseButtonType button) const
{
	return find(_heldMouseButtons.begin(), _heldMouseButtons.end(), button) != _heldMouseButtons.end();
}

const bool InputHandler::isMouseButtonPressed(const MouseButtonType button) const
{
	return find(_pressedMouseButtons.begin(), _pressedMouseButtons.end(), button) != _pressedMouseButtons.end();
}

const bool InputHandler::isMouseButtonToggled(const MouseButtonType button) const
{
	return find(_toggledMouseButtons.begin(), _toggledMouseButtons.end(), button) != _toggledMouseButtons.end();
}