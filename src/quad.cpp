#include "quad.hpp"
#include "mathematics.hpp"

#include <algorithm>

Quad::Quad(const shared_ptr<VertexBuffer> & vertexBuffer)
{
	setVertexBuffer(vertexBuffer);
}

void Quad::update()
{
	const dmat33 translationMatrix = Mathematics::createTranslationMatrix(_position.x, _position.y);
	const dmat33 scalingMatrix = Mathematics::createScalingMatrix(_size.x, _size.y);

	_transformation = (translationMatrix * scalingMatrix);
}

void Quad::setVertexBuffer(const shared_ptr<VertexBuffer> & vertexBuffer)
{
	if(vertexBuffer == nullptr)
	{
		abort();
	}

	_vertexBuffer = vertexBuffer;
}

void Quad::setTextureBuffer(const shared_ptr<TextureBuffer> & textureBuffer)
{
	if(textureBuffer == nullptr)
	{
		abort();
	}

	_textureBuffer = textureBuffer;
}

void Quad::setColor(const dvec3 & value)
{
	if(value < Colors::BLACK || value > Colors::WHITE)
	{
		abort();
	}

	_color = value;
}

void Quad::setUvMultiplier(const dvec2 & value)
{
	if(value < dvec2(0.0) || value > dvec2(1.0))
	{
		abort();
	}

	_uvMultiplier = value;
}

void Quad::setUvOffset(const dvec2 & value)
{
	if(value < dvec2(0.0) || value > dvec2(1.0))
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
	if(value < 0.0 || value > 1.0)
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
	if(value < dvec2(0.0))
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

const dvec2 & Quad::getSize() const
{
	return _size;
}

void Quad::setVisible(const bool value)
{
	_isVisible = value;
}