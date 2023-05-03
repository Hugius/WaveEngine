#pragma once

#include "text.hpp"

class GuiButton final
{
public:
	GuiButton(const shared_ptr<Quad> & quad, const shared_ptr<Text> & text);

	void update(const dvec2 & cursorPosition, const bool isLmbPressed, const bool isLmbHeld);
	void setVisible(const bool value);
	void setHoverable(const bool value);
	void setPressable(const bool value);
	void setHoldable(const bool value);
	void setHighlighted(const bool value);

	const bool isPressed() const;
	const bool isHeld() const;

private:
	void _updateHovering(const dvec2 & cursorPosition);

	const shared_ptr<Quad> _quad;
	const shared_ptr<Text> _text;

	const dvec3 _originalQuadColor;
	const dvec3 _originalTextColor;

	bool _isVisible = false;
	bool _isHoverable = false;
	bool _isPressable = false;
	bool _isHoldable = false;
	bool _isHovered = false;
	bool _isPressed = false;
	bool _isHeld = false;
	bool _isHighlighted = false;
	bool _canBeHeld = false;
};