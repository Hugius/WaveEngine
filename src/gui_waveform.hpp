#pragma once

#include "line.hpp"

class GuiWaveform final
{
public:
	GuiWaveform(const shared_ptr<Line> & line);

	void update();
	void setVisible(const bool value);
	void setSamples(const vector<double> & samples);

private:
	const shared_ptr<Line> _line;
};