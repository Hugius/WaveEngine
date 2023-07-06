#pragma once

#include "text.hpp"

class GuiButton final
{
public:
	GuiButton(const shared_ptr<Quad> & quad, const shared_ptr<Text> & text);
	GuiButton(const shared_ptr<Quad> & quad);

	void update(const dvec2 & cursorPosition, const bool isLmbPressed);
	void setVisible(const bool value);
	void setHoverable(const bool value);
	void setPressable(const bool value);
	void setHighlighted(const bool value);
	void setHoveredQuadColor(const dvec3 & value);
	void setHoveredTextColor(const dvec3 & value);

	const bool isPressed() const;

private:
	void _updateHovering(const dvec2 & cursorPosition);

	const shared_ptr<Quad> _quad;
	const shared_ptr<Text> _text;

	const dvec3 _defaultQuadColor;
	const dvec3 _defaultTextColor;

	dvec3 _hoveredQuadColor = Shared::WHITE;
	dvec3 _hoveredTextColor = Shared::WHITE;

	bool _isVisible = false;
	bool _isHoverable = false;
	bool _isPressable = false;
	bool _isHovered = false;
	bool _isPressed = false;
	bool _isHighlighted = false;
};