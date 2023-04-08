#pragma once

#define GLEW_STATIC

#include <glew.h>

class VertexBuffer final
{
public:
	VertexBuffer();
	~VertexBuffer();

	const unsigned int getVaoId() const;
	const unsigned int getVboId() const;

	const int getVertexCount() const;

private:
	static inline const int _vertexCount = 6;

	unsigned int _vaoId = 0;
	unsigned int _vboId = 0;
};