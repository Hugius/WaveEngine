#include "shader_buffer.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::ostringstream;

ShaderBuffer::ShaderBuffer(const string & vertexFilePath, const string & fragmentFilePath)
{
	ifstream vertexFile = ifstream(vertexFilePath);
	ifstream fragmentFile = ifstream(fragmentFilePath);

	if(!vertexFile)
	{
		abort();
	}

	if(!fragmentFile)
	{
		abort();
	}

	ostringstream vertexStream = {};
	ostringstream fragmentStream = {};

	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();

	vertexFile.close();
	fragmentFile.close();

	const string vertexCodeString = vertexStream.str();
	const char * vertexCode = vertexCodeString.c_str();
	const unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
	const string fragmentCodeString = fragmentStream.str();
	const char * fragmentCode = fragmentCodeString.c_str();
	const unsigned int fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexId, 1, &vertexCode, nullptr);
	glCompileShader(vertexId);

	int vertexStatus;

	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &vertexStatus);

	if(!vertexStatus)
	{
		char log[512];

		glGetShaderInfoLog(vertexId, 512, nullptr, log);

		abort();
	}

	glShaderSource(fragmentId, 1, &fragmentCode, nullptr);
	glCompileShader(fragmentId);

	int fragmentStatus;

	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &fragmentStatus);

	if(!fragmentStatus)
	{
		char log[512];

		glGetShaderInfoLog(fragmentId, 512, nullptr, log);

		abort();
	}

	_programId = glCreateProgram();

	glAttachShader(_programId, vertexId);
	glAttachShader(_programId, fragmentId);
	glLinkProgram(_programId);

	int programStatus;

	glGetProgramiv(_programId, GL_LINK_STATUS, &programStatus);

	if(!programStatus)
	{
		char log[512];

		glGetProgramInfoLog(_programId, 512, nullptr, log);

		abort();
	}

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

ShaderBuffer::~ShaderBuffer()
{
	glDeleteProgram(_programId);
}

const unsigned int ShaderBuffer::getUniformId(const string & name)
{
	const auto iterator = _uniformCache.find(name);

	if(iterator != _uniformCache.end())
	{
		return iterator->second;
	}

	const int uniformId = glGetUniformLocation(_programId, name.c_str());

	if(uniformId == -1)
	{
		abort();
	}

	_uniformCache.insert({name, uniformId});

	return static_cast<unsigned int>(uniformId);
}

void ShaderBuffer::bind()
{
	glUseProgram(_programId);
}

void ShaderBuffer::unbind()
{
	glUseProgram(0);
}

const unsigned int ShaderBuffer::getProgramId() const
{
	return _programId;
}

void ShaderBuffer::_uploadUniform(const int uniformId, const bool data)
{
	glUniform1i(uniformId, data);
}

void ShaderBuffer::_uploadUniform(const int uniformId, const int data)
{
	glUniform1i(uniformId, data);
}

void ShaderBuffer::_uploadUniform(const int uniformId, const float data)
{
	glUniform1f(uniformId, data);
}

void ShaderBuffer::_uploadUniform(const int uniformId, const fvec2 & data)
{
	glUniform2f(uniformId, data.x, data.y);
}

void ShaderBuffer::_uploadUniform(const int uniformId, const fvec3 & data)
{
	glUniform3f(uniformId, data.x, data.y, data.z);
}

void ShaderBuffer::_uploadUniform(const int uniformId, const fmat33 & data)
{
	glUniformMatrix3fv(uniformId, 1, GL_FALSE, data.f);
}