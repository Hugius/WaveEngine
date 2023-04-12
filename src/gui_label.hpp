#pragma once

#include "text.hpp"

class GuiLabel final
{
public:
	GuiLabel(const shared_ptr<Text> & text);

	void update();
	void setVisible(const bool value);
	void setContent(const string & value);

private:
	const shared_ptr<Text> _text;
};