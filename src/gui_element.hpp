#pragma once

#include "text.hpp"

class GuiElement final
{
public:
	GuiElement(const string & id, const shared_ptr<Quad> & quad, const shared_ptr<Text> & text, const bool isHoverable, const bool isPressable, const bool isTogglable);

	void update(const dvec2 & cursorPosition, const bool isLmbPressed);
	void setVisible(const bool value);

	const bool isPressed() const;
	const bool isToggled() const;

private:
	void _updateHovering(const dvec2 & cursorPosition);

	const shared_ptr<Quad> _quad;
	const shared_ptr<Text> _text;

	const string _id;

	const bool _isHoverable = false;
	const bool _isPressable = false;
	const bool _isTogglable = false;

	bool _isVisible = false;
	bool _isHovered = false;
	bool _isPressed = false;
	bool _isToggled = false;
};