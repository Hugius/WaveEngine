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

void GuiElement::update(const dvec2 & cursorPosition, const bool isLmbPressed)
{
	_isPressed = false;

	const bool wasHovered = _isHovered;

	_updateHovering(cursorPosition);

	if(_isHovered)
	{
		Tools::setCursorType(CursorType::HAND);

		if(isLmbPressed)
		{
			if(_isPressable)
			{
				_isPressed = true;
			}

			if(_isTogglable)
			{
				_isToggled = !_isToggled;
			}
		}
	}

	if(!_isToggled && !wasHovered && _isHovered)
	{
		_quad->setLightness(1.5);
	}
	else if(!_isToggled && wasHovered && !_isHovered)
	{
		_quad->setLightness(1.0);
	}

	_quad->update();

	if(_text != nullptr)
	{
		_text->update();
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

void GuiElement::_updateHovering(const dvec2 & cursorPosition)
{
	_isHovered = false;

	if(!_isHoverable)
	{
		return;
	}

	const dvec2 position = _quad->getPosition();
	const dvec2 size = _quad->getSize();
	const bool isCentered = _quad->getVertexBuffer()->isCentered();

	if(isCentered)
	{
		if(cursorPosition.x >= position.x - size.x / 2.0 && cursorPosition.x <= position.x + size.x / 2.0)
		{
			if(cursorPosition.y >= position.y - size.y / 2.0 && cursorPosition.y <= position.y + size.y / 2.0)
			{
				_isHovered = true;
			}
		}
	}
	else
	{
		if(cursorPosition.x >= position.x && cursorPosition.x <= position.x + size.x)
		{
			if(cursorPosition.y >= position.y && cursorPosition.y <= position.y + size.y)
			{
				_isHovered = true;
			}
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