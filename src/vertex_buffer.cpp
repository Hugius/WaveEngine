#include "vertex_buffer.hpp"

VertexBuffer::VertexBuffer(const bool isHorizontallyCentered, const bool isVerticallyCentered)
	:
	_isHorizontallyCentered(isHorizontallyCentered),
	_isVerticallyCentered(isVerticallyCentered)
{
	double * vertices = new double[24];

	if(_isHorizontallyCentered)
	{
		vertices[0] = -0.5;
		vertices[2] = 0.0;
		vertices[4] = 0.5;
		vertices[6] = 1.0;
		vertices[8] = 0.5;
		vertices[10] = 1.0;
		vertices[12] = 0.5;
		vertices[14] = 1.0;
		vertices[16] = -0.5;
		vertices[18] = 0.0;
		vertices[20] = -0.5;
		vertices[22] = 0.0;
	}
	else
	{
		vertices[0] = 0.0;
		vertices[2] = 0.0;
		vertices[4] = 1.0;
		vertices[6] = 1.0;
		vertices[8] = 1.0;
		vertices[10] = 1.0;
		vertices[12] = 1.0;
		vertices[14] = 1.0;
		vertices[16] = 0.0;
		vertices[18] = 0.0;
		vertices[20] = 0.0;
		vertices[22] = 0.0;
	}

	if(_isVerticallyCentered)
	{
		vertices[1] = -0.5;
		vertices[3] = 0.0;
		vertices[5] = -0.5;
		vertices[7] = 0.0;
		vertices[9] = 0.5;
		vertices[11] = 1.0;
		vertices[13] = 0.5;
		vertices[15] = 1.0;
		vertices[17] = 0.5;
		vertices[19] = 1.0;
		vertices[21] = -0.5;
		vertices[23] = 0.0;
	}
	else
	{
		vertices[1] = 0.0;
		vertices[3] = 0.0;
		vertices[5] = 0.0;
		vertices[7] = 0.0;
		vertices[9] = 1.0;
		vertices[11] = 1.0;
		vertices[13] = 1.0;
		vertices[15] = 1.0;
		vertices[17] = 1.0;
		vertices[19] = 1.0;
		vertices[21] = 0.0;
		vertices[23] = 0.0;
	}

	glGenVertexArrays(1, &_vaoId);
	glGenBuffers(1, &_vboId);
	glBindVertexArray(_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(double), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribLPointer(0, 3, GL_DOUBLE, 4 * sizeof(double), (void *)(0 * sizeof(double)));
	glVertexAttribLPointer(1, 2, GL_DOUBLE, 4 * sizeof(double), (void *)(2 * sizeof(double)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	delete[] vertices;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteVertexArrays(1, &_vaoId);
	glDeleteBuffers(1, &_vboId);
}

const unsigned int VertexBuffer::getVaoId() const
{
	return _vaoId;
}

const unsigned int VertexBuffer::getVboId() const
{
	return _vboId;
}

const int VertexBuffer::getVertexCount() const
{
	return _vertexCount;
}

const bool VertexBuffer::isVerticallyCentered() const
{
	return _isVerticallyCentered;
}

const bool VertexBuffer::isHorizontallyCentered() const
{
	return _isHorizontallyCentered;
}