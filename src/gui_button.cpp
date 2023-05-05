#include "gui_button.hpp"
#include "tools.hpp"

GuiButton::GuiButton(const shared_ptr<Quad> & quad, const shared_ptr<Text> & text)
	:
	_quad(quad),
	_text(text),
	_originalQuadColor(quad->getColor()),
	_originalTextColor(text->getColor())
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

void GuiButton::update(const dvec2 & cursorPosition, const bool isLmbPressed)
{
	_isPressed = false;

	_updateHovering(cursorPosition);

	if(_isHovered || _isHighlighted)
	{
		_quad->setColor(dvec3(1.0f) - _originalQuadColor);
		_text->setColor(dvec3(1.0f) - _originalTextColor);
	}
	else
	{
		_quad->setColor(_originalQuadColor);
		_text->setColor(_originalTextColor);
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
	_text->update();
}

void GuiButton::setVisible(const bool value)
{
	_isVisible = value;

	_quad->setVisible(_isVisible);
	_text->setVisible(_isVisible);
}

void GuiButton::setHoverable(const bool value)
{
	_isHoverable = value;
}

void GuiButton::setPressable(const bool value)
{
	_isPressable = value;

	_quad->setOpacity(_isPressable ? 1.0 : 0.5);
	_text->setOpacity(_isPressable ? 1.0 : 0.5);
}

void GuiButton::setHighlighted(const bool value)
{
	_isHighlighted = value;
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
		isHorizontallyHovered = cursorPosition.x >= position.x - size.x * 0.5f && cursorPosition.x <= position.x + size.x * 0.5f;
	}
	else
	{
		isHorizontallyHovered = cursorPosition.x >= position.x && cursorPosition.x <= position.x + size.x;
	}

	bool isVerticallyHovered;
	if(isVerticallyCentered)
	{
		isVerticallyHovered = cursorPosition.y >= position.y - size.y * 0.5f && cursorPosition.y <= position.y + size.y * 0.5f;
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