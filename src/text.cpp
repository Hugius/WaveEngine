#include "text.hpp"
#include "mathematics.hpp"

#include <algorithm>

using std::make_shared;

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

void Text::setVertexBuffer(const shared_ptr<VertexBuffer> & vertexBuffer)
{
	_vertexBuffer = vertexBuffer;
}

void Text::setTextureBuffer(const shared_ptr<TextureBuffer> & textureBuffer)
{
	_textureBuffer = textureBuffer;
}

void Text::setVisible(const bool value)
{
	_isVisible = value;
}

void Text::setContent(const string & value)
{
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
		const shared_ptr<Quad> quad = make_shared<Quad>();

		quad->setVertexBuffer(_vertexBuffer);
		quad->setTextureBuffer(_textureBuffer);
		quad->setUvMultiplier(uvMultiplier);
		quad->setUvOffset(uvOffset);

		_quads.push_back(quad);
	}
}

void Text::setColor(const dvec3 & value)
{
	if(value.r < 0.0 || value.r > 1.0)
	{
		abort();
	}

	if(value.g < 0.0 || value.g > 1.0)
	{
		abort();
	}

	if(value.b < 0.0 || value.b > 1.0)
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
	if(value.x < 0.0)
	{
		abort();
	}

	if(value.y < 0.0)
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