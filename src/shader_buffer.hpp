#pragma once

#define GLEW_STATIC

#include "fmat33.hpp"
#include "fvec3.hpp"
#include "fvec2.hpp"

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
	void _uploadUniform(const int uniformId, const fvec2 & data);
	void _uploadUniform(const int uniformId, const fvec3 & data);
	void _uploadUniform(const int uniformId, const fmat33 & data);

	unordered_map<string, unsigned int> _uniformCache = {};

	unsigned int _programId = 0;
};