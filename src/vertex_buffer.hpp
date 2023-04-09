#pragma once

#define GLEW_STATIC

#include <glew.h>

class VertexBuffer final
{
public:
	VertexBuffer(const bool isCentered);
	~VertexBuffer();

	const unsigned int getVaoId() const;
	const unsigned int getVboId() const;

	const int getVertexCount() const;

	const bool isCentered() const;

private:
	static inline const int _vertexCount = 6;

	const bool _isCentered;

	unsigned int _vaoId = 0;
	unsigned int _vboId = 0;
};