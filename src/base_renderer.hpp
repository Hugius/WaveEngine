#pragma once

#include "shader_buffer.hpp"

#include <memory>

using std::unique_ptr;

class BaseRenderer
{
public:
	BaseRenderer(const string & vertexShaderPath, const string & fragmentShaderPath);

protected:
	const unique_ptr<ShaderBuffer> _shaderBuffer;
};