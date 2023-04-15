#include "gui_waveform.hpp"

using std::make_shared;

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
	const shared_ptr<VertexBuffer> vertexBuffer = _line->getVertexBuffer();

	vector<dvec2> vertices = {};

	for(int index = 0; index < static_cast<int>(samples.size()); index++)
	{
		const double x = -1.0 + static_cast<double>(index) / static_cast<double>(samples.size()) * 2.0;
		const double y = samples[index];

		vertices.push_back(dvec2(x, y));
	}

	_line->setVertexBuffer(make_shared<VertexBuffer>(vertices, vertexBuffer->isHorizontallyCentered(), vertexBuffer->isVerticallyCentered()));
}