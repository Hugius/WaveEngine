#pragma once

#include "text.hpp"

class GuiButton final
{
public:
	GuiButton(const shared_ptr<Quad> & quad, const shared_ptr<Text> & text);

	void update(const dvec2 & cursorPosition, const bool isLmbPressed);
	void setVisible(const bool value);
	void setHoverable(const bool value);
	void setPressable(const bool value);
	void setTogglable(const bool value);

	const bool isPressed() const;
	const bool isToggled() const;

private:
	void _updateHovering(const dvec2 & cursorPosition);

	const shared_ptr<Quad> _quad;
	const shared_ptr<Text> _text;

	const dvec3 _originalQuadColor;
	const dvec3 _originalTextColor;

	bool _isVisible = false;
	bool _isHoverable = false;
	bool _isPressable = false;
	bool _isTogglable = false;
	bool _isHovered = false;
	bool _isPressed = false;
	bool _isToggled = false;
};