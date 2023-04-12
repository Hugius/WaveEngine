#include "gui_label.hpp"

GuiLabel::GuiLabel(const shared_ptr<Text> & text)
	:
	_text(text)
{
	if(text == nullptr)
	{
		abort();
	}
}

void GuiLabel::update()
{
	_text->update();
}

void GuiLabel::setVisible(const bool value)
{
	_text->setVisible(value);
}

void GuiLabel::setContent(const string & value)
{
	_text->setContent(value);
}