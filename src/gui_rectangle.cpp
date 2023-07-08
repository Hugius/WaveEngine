#include "gui_rectangle.hpp"

GuiRectangle::GuiRectangle(const shared_ptr<Quad> & quad)
	:
	_quad(quad)
{
	if(quad == nullptr)
	{
		abort();
	}
}

void GuiRectangle::update()
{
	_quad->update();
}

void GuiRectangle::setVisible(const bool value)
{
	_quad->setVisible(value);
}

const shared_ptr<Quad> & GuiRectangle::getQuad() const
{
	return _quad;
}