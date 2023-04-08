#pragma once

#define GLEW_STATIC

#include "dmat33.hpp"
#include "dvec3.hpp"
#include "dvec2.hpp"

#include <unordered_map>
#include <glew.h>
#include <string>

using std::unordered_map;
using std::string;

class ShaderBuffer final
{
public:
	ShaderBuffer(const string & vertexFilePath, const string & fragmentFilePath);
	~ShaderBuffer();

	template<typename T> void uploadUniform(const string & name, const T & data)
	{
		_uploadUniform(getUniformId(name), data);
	}

	void bind();
	void unbind();

	const unsigned int getProgramId() const;
	const unsigned int getUniformId(const string & name);

private:
	void _uploadUniform(const int uniformId, const bool data);
	void _uploadUniform(const int uniformId, const int data);
	void _uploadUniform(const int uniformId, const double data);
	void _uploadUniform(const int uniformId, const dvec2 & data);
	void _uploadUniform(const int uniformId, const dvec3 & data);
	void _uploadUniform(const int uniformId, const dmat33 & data);

	unordered_map<string, unsigned int> _uniformCache = {};

	unsigned int _programId = 0;
};