#include "shader_buffer.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::ostringstream;

ShaderBuffer::ShaderBuffer(const string & vertexFilePath, const string & fragmentFilePath)
{
	if(vertexFilePath.empty())
	{
		abort();
	}

	if(fragmentFilePath.empty())
	{
		abort();
	}

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
		const int logSize = 512;

		char log[logSize];

		glGetShaderInfoLog(vertexId, logSize, nullptr, log);

		abort();
	}

	glShaderSource(fragmentId, 1, &fragmentCode, nullptr);
	glCompileShader(fragmentId);

	int fragmentStatus;

	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &fragmentStatus);

	if(!fragmentStatus)
	{
		const int logSize = 512;

		char log[logSize];

		glGetShaderInfoLog(fragmentId, logSize, nullptr, log);

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
		const int logSize = 512;

		char log[logSize];

		glGetProgramInfoLog(_programId, logSize, nullptr, log);

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
	glUniform1i(uniformId, static_cast<int>(data));
}

void ShaderBuffer::_uploadUniform(const int uniformId, const int data)
{
	glUniform1i(uniformId, data);
}

void ShaderBuffer::_uploadUniform(const int uniformId, const double data)
{
	glUniform1d(uniformId, data);
}

void ShaderBuffer::_uploadUniform(const int uniformId, const dvec2 & data)
{
	glUniform2d(uniformId, data.x, data.y);
}

void ShaderBuffer::_uploadUniform(const int uniformId, const dvec3 & data)
{
	glUniform3d(uniformId, data.x, data.y, data.z);
}

void ShaderBuffer::_uploadUniform(const int uniformId, const dmat33 & data)
{
	glUniformMatrix3dv(uniformId, 1, 0, data.f);
}