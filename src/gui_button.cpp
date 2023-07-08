#include "gui_button.hpp"
#include "tools.hpp"

GuiButton::GuiButton(const shared_ptr<Quad> & quad, const shared_ptr<Text> & text)
	:
	_quad(quad),
	_text(text),
	_defaultQuadColor(quad->getColor()),
	_defaultTextColor(text->getColor())
{
	if(quad == nullptr)
	{
		abort();
	}

	if(text == nullptr)
	{
		abort();
	}
}

GuiButton::GuiButton(const shared_ptr<Quad> & quad)
	:
	_quad(quad),
	_text(nullptr),
	_defaultQuadColor(quad->getColor()),
	_defaultTextColor(dvec3(0.0))
{
	if(quad == nullptr)
	{
		abort();
	}
}

void GuiButton::update(const dvec2 & cursorPosition, const bool isLmbPressed)
{
	_isPressed = false;

	_updateHovering(cursorPosition);

	if(_isHovered || _isHighlighted)
	{
		_quad->setColor(_hoveredQuadColor);

		if(_text != nullptr)
		{
			_text->setColor(_hoveredTextColor);
		}
	}
	else
	{
		_quad->setColor(_defaultQuadColor);

		if(_text != nullptr)
		{
			_text->setColor(_defaultTextColor);
		}
	}

	if(_isHovered)
	{
		Tools::setCursorType(CursorType::HAND);

		if(isLmbPressed && _isPressable)
		{
			_isPressed = true;
		}
	}

	_quad->update();

	if(_text != nullptr)
	{
		_text->update();
	}
}

void GuiButton::setVisible(const bool value)
{
	_isVisible = value;

	_quad->setVisible(_isVisible);

	if(_text != nullptr)
	{
		_text->setVisible(_isVisible);
	}
}

void GuiButton::setHoverable(const bool value)
{
	_isHoverable = value;
}

void GuiButton::setPressable(const bool value)
{
	_isPressable = value;

	_quad->setOpacity(_isPressable ? 1.0 : 0.5);

	if(_text != nullptr)
	{
		_text->setOpacity(_isPressable ? 1.0 : 0.5);
	}
}

void GuiButton::setHighlighted(const bool value)
{
	_isHighlighted = value;
}

void GuiButton::setHoveredQuadColor(const dvec3 & value)
{
	_hoveredQuadColor = value;
}

void GuiButton::setHoveredTextColor(const dvec3 & value)
{
	_hoveredTextColor = value;
}

const shared_ptr<Quad> & GuiButton::getQuad() const
{
	return _quad;
}

void GuiButton::_updateHovering(const dvec2 & cursorPosition)
{
	_isHovered = false;

	if(!_isVisible)
	{
		return;
	}

	if(!_isHoverable)
	{
		return;
	}

	const dvec2 position = _quad->getPosition();
	const dvec2 size = _quad->getSize();
	const bool isHorizontallyCentered = _quad->getVertexBuffer()->isHorizontallyCentered();
	const bool isVerticallyCentered = _quad->getVertexBuffer()->isVerticallyCentered();

	bool isHorizontallyHovered;
	if(isHorizontallyCentered)
	{
		isHorizontallyHovered = cursorPosition.x >= position.x - size.x / 2.0 && cursorPosition.x <= position.x + size.x / 2.0;
	}
	else
	{
		isHorizontallyHovered = cursorPosition.x >= position.x && cursorPosition.x <= position.x + size.x;
	}

	bool isVerticallyHovered;
	if(isVerticallyCentered)
	{
		isVerticallyHovered = cursorPosition.y >= position.y - size.y / 2.0 && cursorPosition.y <= position.y + size.y / 2.0;
	}
	else
	{
		isVerticallyHovered = cursorPosition.y >= position.y && cursorPosition.y <= position.y + size.y;
	}

	if(isHorizontallyHovered && isVerticallyHovered)
	{
		_isHovered = true;
	}
}

const bool GuiButton::isPressed() const
{
	return _isPressed;
}