#include "text.hpp"
#include "mathematics.hpp"

#include <algorithm>

using std::max;
using std::clamp;
using std::make_shared;

Text::Text(const shared_ptr<VertexBuffer> & vertexBuffer, const shared_ptr<TextureBuffer> & textureBuffer, const int depth, const string & content)
	:
	_depth(depth),
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

	if(depth < 1)
	{
		abort();
	}

	if(content.empty())
	{
		abort();
	}

	setContent(content);
}

void Text::update()
{
	const dmat33 rotationMatrix = Mathematics::createRotationMatrix(Mathematics::convertToRadians(_rotation));
	const dvec2 quadSize = dvec2((this->getSize().x / static_cast<double>(this->_content.size())), this->getSize().y);

	int index = 0;

	for(const shared_ptr<Quad> & quad : _quads)
	{
		dvec2 offset = dvec2((static_cast<double>(index) * quadSize.x), 0.0);

		if(_vertexBuffer->isHorizontallyCentered())
		{
			offset.x -= (this->getSize().x * 0.5);
			offset.x += (quadSize.x * 0.5);
		}

		quad->setPosition(_position + (rotationMatrix * offset));
		quad->setRotation(_rotation);
		quad->setSize(quadSize);
		quad->update();

		index++;
	}
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
		if(_fontMapIndices.find(character) == _fontMapIndices.end())
		{
			abort();
		}

		const int xIndex = _fontMapIndices.at(character).x;
		const int yIndex = _fontMapIndices.at(character).y;
		const dvec2 uvMultiplier = dvec2((1.0 / static_cast<double>(FONT_MAP_COLUMN_COUNT)), (1.0 / static_cast<double>(FONT_MAP_ROW_COUNT)));
		const dvec2 uvOffset = dvec2((static_cast<double>(xIndex) * uvMultiplier.x), (static_cast<double>(yIndex) * uvMultiplier.y));
		const shared_ptr<Quad> quad = make_shared<Quad>(_vertexBuffer, _textureBuffer, _depth);

		quad->setOpacity(_opacity);
		quad->setColor(_color);
		quad->setVisible(_isVisible);
		quad->setLightness(_lightness);
		quad->setUvMultiplier(uvMultiplier);
		quad->setUvOffset(uvOffset);

		_quads.push_back(quad);
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

void Text::setRotation(const double value)
{
	_rotation = Mathematics::limitAngle(value);
}

void Text::setSize(const dvec2 & value)
{
	_size = dvec2(max(0.0, value.x), max(0.0, value.y));
}

const string & Text::getContent() const
{
	return _content;
}

const vector<shared_ptr<Quad>> & Text::getQuads() const
{
	return _quads;
}

const dvec3 & Text::getColor() const
{
	return _color;
}

const double Text::getOpacity() const
{
	return _opacity;
}

const bool Text::isVisible() const
{
	return _isVisible;
}

const dvec2 & Text::getPosition() const
{
	return _position;
}

const double Text::getRotation() const
{
	return _rotation;
}

const double Text::getLightness() const
{
	return _lightness;
}

const dvec2 & Text::getSize() const
{
	return _size;
}

const int Text::getDepth() const
{
	return _depth;
}