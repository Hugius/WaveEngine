#include "quad.hpp"
#include "mathematics.hpp"

#include <algorithm>

using std::make_shared;

Quad::Quad(const shared_ptr<VertexBuffer> & vertexBuffer, int depth)
	:
	_vertexBuffer(vertexBuffer),
	_depth(depth)
{
	if(vertexBuffer == nullptr)
	{
		abort();
	}

	if(depth < 1)
	{
		abort();
	}
}

void Quad::update()
{
	const dmat33 translationMatrix = Mathematics::createTranslationMatrix(_position.x, _position.y);
	const dmat33 scalingMatrix = Mathematics::createScalingMatrix(_size.x, _size.y);

	_transformation = (translationMatrix * scalingMatrix);
}

void Quad::setTextureBuffer(const shared_ptr<TextureBuffer> & textureBuffer)
{
	_textureBuffer = textureBuffer;
}

void Quad::setColor(const dvec3 & value)
{
	if(value.r < 0.0f || value.r > 1.0f)
	{
		abort();
	}

	if(value.g < 0.0f || value.g > 1.0f)
	{
		abort();
	}

	if(value.b < 0.0f || value.b > 1.0f)
	{
		abort();
	}

	_color = value;
}

void Quad::setUvMultiplier(const dvec2 & value)
{
	if(value.x < 0.0f || value.x > 1.0f)
	{
		abort();
	}

	if(value.y < 0.0f || value.y > 1.0f)
	{
		abort();
	}

	_uvMultiplier = value;
}

void Quad::setUvOffset(const dvec2 & value)
{
	if(value.x < 0.0f || value.x > 1.0f)
	{
		abort();
	}

	if(value.y < 0.0f || value.y > 1.0f)
	{
		abort();
	}

	_uvOffset = value;
}

const dvec2 & Quad::getUvMultiplier() const
{
	return _uvMultiplier;
}

const dvec2 & Quad::getUvOffset() const
{
	return _uvOffset;
}

void Quad::setOpacity(const double value)
{
	if(value < 0.0f || value > 1.0f)
	{
		abort();
	}

	_opacity = value;
}

void Quad::setPosition(const dvec2 & value)
{
	_position = value;
}

void Quad::setSize(const dvec2 & value)
{
	if(value.x < 0.0f)
	{
		abort();
	}

	if(value.y < 0.0f)
	{
		abort();
	}

	_size = value;
}

const shared_ptr<VertexBuffer> & Quad::getVertexBuffer() const
{
	return _vertexBuffer;
}

const shared_ptr<TextureBuffer> & Quad::getTexture() const
{
	return _textureBuffer;
}

const dvec3 & Quad::getColor() const
{
	return _color;
}

const double Quad::getOpacity() const
{
	return _opacity;
}

const bool Quad::isVisible() const
{
	return _isVisible;
}

const dmat33 & Quad::getTransformation() const
{
	return _transformation;
}

const dvec2 & Quad::getPosition() const
{
	return _position;
}

const double Quad::getLightness() const
{
	return _lightness;
}

const dvec2 & Quad::getSize() const
{
	return _size;
}

const int Quad::getDepth() const
{
	return _depth;
}

void Quad::setVisible(const bool value)
{
	_isVisible = value;
}

void Quad::setLightness(const double value)
{
	if(value < 0.0f)
	{
		abort();
	}

	_lightness = value;
}