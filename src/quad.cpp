#include "quad.hpp"
#include "mathematics.hpp"

#include <algorithm>

using std::max;
using std::clamp;
using std::make_shared;

Quad::Quad(const shared_ptr<VertexBuffer> vertexBuffer, const shared_ptr<TextureBuffer> textureBuffer, int depth)
	:
	_vertexBuffer(vertexBuffer),
	_textureBuffer(textureBuffer),
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
	const dmat33 rotationMatrix = Mathematics::createRotationMatrix(Mathematics::convertToRadians(_rotation));
	const dmat33 scalingMatrix = Mathematics::createScalingMatrix(_size.x, _size.y);

	_transformation = (translationMatrix * rotationMatrix * scalingMatrix);
}

void Quad::setColor(const dvec3 & value)
{
	_color = dvec3(clamp(value.r, 0.0, 1.0), clamp(value.g, 0.0, 1.0), clamp(value.b, 0.0, 1.0));
}

void Quad::setUvMultiplier(const dvec2 & value)
{
	_uvMultiplier = dvec2(clamp(value.x, 0.0, 1.0), clamp(value.y, 0.0, 1.0));
}

void Quad::setUvOffset(const dvec2 & value)
{
	_uvOffset = dvec2(clamp(value.x, 0.0, 1.0), clamp(value.y, 0.0, 1.0));
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
	_opacity = clamp(value, 0.0, 1.0);
}

void Quad::setPosition(const dvec2 & value)
{
	_position = value;
}

void Quad::setRotation(const double value)
{
	_rotation = Mathematics::limitAngle(value);
}

void Quad::setSize(const dvec2 & value)
{
	_size = dvec2(max(0.0, value.x), max(0.0, value.y));
}

const shared_ptr<VertexBuffer> Quad::getVertexBuffer() const
{
	return _vertexBuffer;
}

const shared_ptr<TextureBuffer> Quad::getTexture() const
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

const double Quad::getRotation() const
{
	return _rotation;
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
	_lightness = max(0.0, value);
}