#include "gui_waveform.hpp"

using std::make_shared;
using std::max_element;
using std::begin;
using std::end;

GuiWaveform::GuiWaveform(const shared_ptr<Line> & line)
	:
	_line(line)
{
	if(line == nullptr)
	{
		abort();
	}
}

void GuiWaveform::update()
{
	_line->update();
}

void GuiWaveform::setVisible(const bool value)
{
	_line->setVisible(value);
}

void GuiWaveform::setSamples(const vector<double> & samples)
{
	const shared_ptr<VertexBuffer> oldVertexBuffer = _line->getVertexBuffer();
	const double amplitude = *max_element(begin(samples), end(samples));

	vector<dvec2> vertices = {};

	for(int index = 0; index < static_cast<int>(samples.size()); index++)
	{
		const double x = -1.0 + static_cast<double>(index) / static_cast<double>(samples.size()) * 2.0;
		const double y = samples[index] / amplitude;

		vertices.push_back(dvec2(x, y));
	}

	const shared_ptr<VertexBuffer> newVertexBuffer = make_shared<VertexBuffer>(vertices, oldVertexBuffer->isHorizontallyCentered(), oldVertexBuffer->isVerticallyCentered());

	_line->setVertexBuffer(newVertexBuffer);
}