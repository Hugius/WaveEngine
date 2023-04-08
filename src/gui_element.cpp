#include "gui_element.hpp"
#include "tools.hpp"

GuiElement::GuiElement(const string & id, const shared_ptr<Quad> & quad, const shared_ptr<Text> & text, const bool isHoverable, const bool isPressable, const bool isTogglable)
	:
	_id(id),
	_quad(quad),
	_text(text),
	_isHoverable(isHoverable),
	_isPressable(isPressable),
	_isTogglable(isTogglable)
{
	if(id.empty())
	{
		abort();
	}

	if(quad == nullptr)
	{
		abort();
	}
}

void GuiElement::update(const fvec2 & cursorPosition, const bool isLmbPressed)
{
	_quad->update();

	if(_text != nullptr)
	{
		_text->update();
	}

	const bool wasHovered = _isHovered;
	const bool wasToggled = _isToggled;

	_updateHovering(cursorPosition);

	if(_isHovered)
	{
		Tools::setCursorType(CursorType::HAND);

		if(isLmbPressed)
		{
			_isPressed = true;
			_isToggled = !_isToggled;
		}
	}
	else
	{
		_isPressed = false;
	}

	if(!_isToggled && !wasHovered && _isHovered)
	{
		_quad->setLightness(_quad->getLightness() * 1.5f);
	}
	else if(!_isToggled && wasHovered && !_isHovered)
	{
		_quad->setLightness(_quad->getLightness() / 1.5f);
	}
}

void GuiElement::setVisible(const bool value)
{
	_quad->setVisible(value);

	if(_text != nullptr)
	{
		_text->setVisible(value);
	}

	_isVisible = value;
}

void GuiElement::_updateHovering(const fvec2 & cursorPosition)
{
	const fvec2 position = _quad->getPosition();
	const fvec2 size = _quad->getSize();

	_isHovered = false;

	if(cursorPosition.x >= position.x && cursorPosition.x <= position.x + size.x)
	{
		if(cursorPosition.y >= position.y && cursorPosition.y <= position.y + size.y)
		{
			_isHovered = true;
		}
	}
}

const bool GuiElement::isVisible() const
{
	return _isVisible;
}

const bool GuiElement::isHovered() const
{
	return _isHovered;
}

const bool GuiElement::isPressed() const
{
	return _isPressed;
}

const bool GuiElement::isToggled() const
{
	return _isToggled;
}