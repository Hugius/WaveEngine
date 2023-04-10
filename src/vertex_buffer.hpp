#pragma once

#define GLEW_STATIC

#include <glew.h>

class VertexBuffer final
{
public:
	VertexBuffer(const bool isHorizontallyCentered, const bool isVerticallyCentered);
	~VertexBuffer();

	const unsigned int getVaoId() const;
	const unsigned int getVboId() const;

	const int getVertexCount() const;

	const bool isHorizontallyCentered() const;
	const bool isVerticallyCentered() const;

private:
	static inline const int _vertexCount = 6;

	const bool _isHorizontallyCentered;
	const bool _isVerticallyCentered;

	unsigned int _vaoId = 0;
	unsigned int _vboId = 0;
};