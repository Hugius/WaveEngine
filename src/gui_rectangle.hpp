#pragma once

#include "quad.hpp"

class GuiRectangle final
{
public:
	GuiRectangle(const shared_ptr<Quad> & quad);

	void update();
	void setVisible(const bool value);

private:
	const shared_ptr<Quad> _quad;
};