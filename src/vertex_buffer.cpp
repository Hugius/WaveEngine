#pragma warning(disable:6386)

#include "vertex_buffer.hpp"

VertexBuffer::VertexBuffer(const bool isHorizontallyCentered, const bool isVerticallyCentered)
	:
	_vertexCount(6),
	_isHorizontallyCentered(isHorizontallyCentered),
	_isVerticallyCentered(isVerticallyCentered)
{
	const int dataCount = 24;

	double * data = new double[dataCount];

	if(_isHorizontallyCentered)
	{
		data[0] = -0.5;
		data[2] = 0.0;
		data[4] = 0.5;
		data[6] = 1.0;
		data[8] = 0.5;
		data[10] = 1.0;
		data[12] = 0.5;
		data[14] = 1.0;
		data[16] = -0.5;
		data[18] = 0.0;
		data[20] = -0.5;
		data[22] = 0.0;
	}
	else
	{
		data[0] = 0.0;
		data[2] = 0.0;
		data[4] = 1.0;
		data[6] = 1.0;
		data[8] = 1.0;
		data[10] = 1.0;
		data[12] = 1.0;
		data[14] = 1.0;
		data[16] = 0.0;
		data[18] = 0.0;
		data[20] = 0.0;
		data[22] = 0.0;
	}

	if(_isVerticallyCentered)
	{
		data[1] = -0.5;
		data[3] = 0.0;
		data[5] = -0.5;
		data[7] = 0.0;
		data[9] = 0.5;
		data[11] = 1.0;
		data[13] = 0.5;
		data[15] = 1.0;
		data[17] = 0.5;
		data[19] = 1.0;
		data[21] = -0.5;
		data[23] = 0.0;
	}
	else
	{
		data[1] = 0.0;
		data[3] = 0.0;
		data[5] = 0.0;
		data[7] = 0.0;
		data[9] = 1.0;
		data[11] = 1.0;
		data[13] = 1.0;
		data[15] = 1.0;
		data[17] = 1.0;
		data[19] = 1.0;
		data[21] = 0.0;
		data[23] = 0.0;
	}

	glGenVertexArrays(1, &_vaoId);
	glGenBuffers(1, &_vboId);
	glBindVertexArray(_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
	glBufferData(GL_ARRAY_BUFFER, dataCount * sizeof(double), data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribLPointer(0, 2, GL_DOUBLE, 4 * sizeof(double), reinterpret_cast<void *>(0 * sizeof(double)));
	glVertexAttribLPointer(1, 2, GL_DOUBLE, 4 * sizeof(double), reinterpret_cast<void *>(2 * sizeof(double)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	delete[] data;
}

VertexBuffer::VertexBuffer(const vector<dvec2> & vertices, const bool isHorizontallyCentered, const bool isVerticallyCentered)
	:
	_vertexCount(static_cast<int>(vertices.size())),
	_isHorizontallyCentered(isHorizontallyCentered),
	_isVerticallyCentered(isVerticallyCentered)
{
	if(_vertexCount < 2)
	{
		abort();
	}

	const int dataCount = _vertexCount * 2;

	double * data = new double[dataCount];

	for(int index = 0; index < _vertexCount; index++)
	{
		const int dataIndex = index * 2;

		if(_isHorizontallyCentered)
		{
			data[dataIndex + 0] = vertices.at(index).x / 2.0;
		}
		else
		{
			data[dataIndex + 0] = vertices.at(index).x / 2.0 + 0.5;
		}

		if(_isVerticallyCentered)
		{

			data[dataIndex + 1] = vertices.at(index).y / 2.0;
		}
		else
		{
			data[dataIndex + 1] = vertices.at(index).y / 2.0 + 0.5;
		}
	}

	glGenVertexArrays(1, &_vaoId);
	glGenBuffers(1, &_vboId);
	glBindVertexArray(_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
	glBufferData(GL_ARRAY_BUFFER, dataCount * sizeof(double), data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribLPointer(0, 2, GL_DOUBLE, 2 * sizeof(double), reinterpret_cast<void *>(0 * sizeof(double)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	delete[] data;
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