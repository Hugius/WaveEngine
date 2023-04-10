#include "text.hpp"
#include "mathematics.hpp"

#include <algorithm>

using std::max;
using std::clamp;
using std::make_shared;

Text::Text(const shared_ptr<VertexBuffer> & vertexBuffer, const shared_ptr<TextureBuffer> & textureBuffer, const string & content, const int depth)
	:
	_depth(depth),
	_vertexBuffer(vertexBuffer),
	_textureBuffer(textureBuffer),
	_content(content)
{
	if(vertexBuffer == nullptr)
	{
		abort();
	}

	if(textureBuffer == nullptr)
	{
		abort();
	}

	if(depth < 1)
	{
		abort();
	}

	if(content.empty())
	{
		abort();
	}

	for(const char & character : _content)
	{
		if(_fontIndices.find(character) == _fontIndices.end())
		{
			abort();
		}

		const int xIndex = _fontIndices.at(character).x;
		const int yIndex = _fontIndices.at(character).y;
		const dvec2 uvMultiplier = dvec2((1.0 / static_cast<double>(FONT_MAP_COLUMN_COUNT)), (1.0 / static_cast<double>(FONT_MAP_ROW_COUNT)));
		const dvec2 uvOffset = dvec2((static_cast<double>(xIndex) * uvMultiplier.x), (static_cast<double>(yIndex) * uvMultiplier.y));
		const shared_ptr<Quad> quad = make_shared<Quad>(_vertexBuffer, _depth);

		quad->setTextureBuffer(_textureBuffer);
		quad->setOpacity(_opacity);
		quad->setColor(_color);
		quad->setVisible(_isVisible);
		quad->setLightness(_lightness);
		quad->setUvMultiplier(uvMultiplier);
		quad->setUvOffset(uvOffset);

		_quads.push_back(quad);
	}
}

void Text::update()
{
	const dvec2 quadSize = dvec2((_size.x / static_cast<double>(_content.size())), _size.y);

	int index = 0;

	for(const shared_ptr<Quad> & quad : _quads)
	{
		dvec2 offset = dvec2((static_cast<double>(index) * quadSize.x), 0.0);

		if(_vertexBuffer->isHorizontallyCentered())
		{
			offset.x -= (_size.x * 0.5);
			offset.x += (quadSize.x * 0.5);
		}

		quad->setPosition(_position + offset);
		quad->setSize(quadSize);
		quad->update();

		index++;
	}
}

void Text::setVisible(const bool value)
{
	_isVisible = value;

	for(const shared_ptr<Quad> & quad : _quads)
	{
		quad->setVisible(_isVisible);
	}
}

void Text::setLightness(const double value)
{
	_lightness = max(0.0, value);

	for(const shared_ptr<Quad> & quad : _quads)
	{
		quad->setLightness(_lightness);
	}
}

void Text::setColor(const dvec3 & value)
{
	_color = dvec3(clamp(value.r, 0.0, 1.0), clamp(value.g, 0.0, 1.0), clamp(value.b, 0.0, 1.0));

	for(const shared_ptr<Quad> & quad : _quads)
	{
		quad->setColor(_color);
	}
}

void Text::setOpacity(const double value)
{
	_opacity = clamp(value, 0.0, 1.0);

	for(const shared_ptr<Quad> & quad : _quads)
	{
		quad->setOpacity(_opacity);
	}
}

void Text::setPosition(const dvec2 & value)
{
	_position = value;
}

void Text::setSize(const dvec2 & value)
{
	_size = dvec2(max(0.0, value.x), max(0.0, value.y));
}

const vector<shared_ptr<Quad>> & Text::getQuads() const
{
	return _quads;
}

const int Text::getDepth() const
{
	return _depth;
}