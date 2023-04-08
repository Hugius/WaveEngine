#pragma once

#include "text.hpp"

class GuiElement final
{
public:
	GuiElement(const string & id, const shared_ptr<Quad> & quad, const shared_ptr<Text> & text, const bool isHoverable, const bool isPressable, const bool isTogglable);

	void update(const fvec2 & cursorPosition, const bool isLmbPressed);
	void setVisible(const bool value);

	const bool isVisible() const;
	const bool isHovered() const;
	const bool isPressed() const;
	const bool isToggled() const;

private:
	void _updateHovering(const fvec2 & cursorPosition);

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