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
	const fmat33 translationMatrix = Mathematics::createTranslationMatrix(_position.x, _position.y);
	const fmat33 rotationMatrix = Mathematics::createRotationMatrix(Mathematics::convertToRadians(_rotation));
	const fmat33 scalingMatrix = Mathematics::createScalingMatrix(_size.x, _size.y);

	_transformation = (translationMatrix * rotationMatrix * scalingMatrix);
}

void Quad::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Quad::setUvMultiplier(const fvec2 & value)
{
	_uvMultiplier = fvec2(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f));
}

void Quad::setUvOffset(const fvec2 & value)
{
	_uvOffset = fvec2(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f));
}

const fvec2 & Quad::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2 & Quad::getUvOffset() const
{
	return _uvOffset;
}

void Quad::setOpacity(const float value)
{
	_opacity = clamp(value, 0.0f, 1.0f);
}

void Quad::setPosition(const fvec2 & value)
{
	_position = value;
}

void Quad::setRotation(const float value)
{
	_rotation = Mathematics::limitAngle(value);
}

void Quad::setSize(const fvec2 & value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

const shared_ptr<VertexBuffer> Quad::getVertexBuffer() const
{
	return _vertexBuffer;
}

const shared_ptr<TextureBuffer> Quad::getTexture() const
{
	return _textureBuffer;
}

const fvec3 & Quad::getColor() const
{
	return _color;
}

const float Quad::getOpacity() const
{
	return _opacity;
}

const bool Quad::isVisible() const
{
	return _isVisible;
}

const fmat33 & Quad::getTransformation() const
{
	return _transformation;
}

const fvec2 & Quad::getPosition() const
{
	return _position;
}

const float Quad::getRotation() const
{
	return _rotation;
}

const float Quad::getLightness() const
{
	return _lightness;
}

const fvec2 & Quad::getSize() const
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

void Quad::setLightness(const float value)
{
	_lightness = max(0.0f, value);
}