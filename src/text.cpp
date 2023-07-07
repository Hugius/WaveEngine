#include "text.hpp"
#include "mathematics.hpp"

#include <algorithm>

using std::make_shared;

Text::Text(const shared_ptr<VertexBuffer> & vertexBuffer, const shared_ptr<TextureBuffer> & textureBuffer, const string & content)
	:
	_vertexBuffer(vertexBuffer),
	_textureBuffer(textureBuffer)
{
	if(vertexBuffer == nullptr)
	{
		abort();
	}

	if(textureBuffer == nullptr)
	{
		abort();
	}

	setContent(content);
}

void Text::update()
{
	const dvec2 quadSize = dvec2(_size.x / static_cast<double>(_content.size()), _size.y);

	int index = 0;

	for(const shared_ptr<Quad> & quad : _quads)
	{
		dvec2 offset = dvec2(static_cast<double>(index) * quadSize.x, 0.0);

		if(_vertexBuffer->isHorizontallyCentered())
		{
			offset.x -= (_size.x * 0.5);
			offset.x += (quadSize.x * 0.5);
		}

		quad->setColor(_color);
		quad->setOpacity(_opacity);
		quad->setVisible(_isVisible);
		quad->setPosition(_position + offset);
		quad->setSize(quadSize);
		quad->update();

		index++;
	}
}

void Text::setVisible(const bool value)
{
	_isVisible = value;
}

void Text::setContent(const string & value)
{
	if(value.empty())
	{
		abort();
	}

	if(value == _content)
	{
		return;
	}

	_content = value;

	_quads.clear();

	for(const char & character : _content)
	{
		if(_fontIndices.find(character) == _fontIndices.end())
		{
			abort();
		}

		const int xIndex = _fontIndices.at(character).x;
		const int yIndex = _fontIndices.at(character).y;
		const dvec2 uvMultiplier = dvec2(1.0 / static_cast<double>(FONT_MAP_COLUMN_COUNT), 1.0 / static_cast<double>(FONT_MAP_ROW_COUNT));
		const dvec2 uvOffset = dvec2(static_cast<double>(xIndex) * uvMultiplier.x, static_cast<double>(yIndex) * uvMultiplier.y);
		const shared_ptr<Quad> quad = make_shared<Quad>(_vertexBuffer);

		quad->setVertexBuffer(_vertexBuffer);
		quad->setTextureBuffer(_textureBuffer);
		quad->setUvMultiplier(uvMultiplier);
		quad->setUvOffset(uvOffset);

		_quads.push_back(quad);
	}
}

void Text::setColor(const dvec3 & value)
{
	if(value < Colors::BLACK || value > Colors::WHITE)
	{
		abort();
	}

	_color = value;
}

void Text::setOpacity(const double value)
{
	if(value < 0.0 || value > 1.0)
	{
		abort();
	}

	_opacity = value;
}

void Text::setPosition(const dvec2 & value)
{
	_position = value;
}

void Text::setSize(const dvec2 & value)
{
	if(value < dvec2(0.0))
	{
		abort();
	}

	_size = value;
}

const vector<shared_ptr<Quad>> & Text::getQuads() const
{
	return _quads;
}

const dvec3 & Text::getColor() const
{
	return _color;
}