#pragma once

#define GLEW_STATIC

#include "dvec2.hpp"

#include <glew.h>
#include <vector>

using std::vector;

class VertexBuffer final
{
public:
	VertexBuffer(const bool isHorizontallyCentered, const bool isVerticallyCentered);
	VertexBuffer(const vector<dvec2> & vertices, const bool isHorizontallyCentered, const bool isVerticallyCentered);
	~VertexBuffer();

	const unsigned int getVaoId() const;

	const int getVertexCount() const;

	const bool isHorizontallyCentered() const;
	const bool isVerticallyCentered() const;

private:
	const int _vertexCount;

	const bool _isHorizontallyCentered;
	const bool _isVerticallyCentered;

	unsigned int _vaoId = 0;
	unsigned int _vboId = 0;
};