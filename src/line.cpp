#include "line.hpp"
#include "mathematics.hpp"

Line::Line(const shared_ptr<VertexBuffer> & vertexBuffer)
{
	setVertexBuffer(vertexBuffer);
}

void Line::update()
{
	const dmat33 translationMatrix = Mathematics::createTranslationMatrix(_position.x, _position.y);
	const dmat33 scalingMatrix = Mathematics::createScalingMatrix(_size.x, _size.y);

	_transformation = (translationMatrix * scalingMatrix);
}

void Line::setVertexBuffer(const shared_ptr<VertexBuffer> & vertexBuffer)
{
	if(vertexBuffer == nullptr)
	{
		abort();
	}

	_vertexBuffer = vertexBuffer;
}

void Line::setColor(const dvec3 & value)
{
	if(value < Colors::BLACK || value > Colors::WHITE)
	{
		abort();
	}

	_color = value;
}

void Line::setPosition(const dvec2 & value)
{
	_position = value;
}

void Line::setSize(const dvec2 & value)
{
	if(value < dvec2(0.0))
	{
		abort();
	}

	_size = value;
}

const shared_ptr<VertexBuffer> & Line::getVertexBuffer() const
{
	return _vertexBuffer;
}

const dvec3 & Line::getColor() const
{
	return _color;
}

const bool Line::isVisible() const
{
	return _isVisible;
}

const dmat33 & Line::getTransformation() const
{
	return _transformation;
}

void Line::setVisible(const bool value)
{
	_isVisible = value;
}