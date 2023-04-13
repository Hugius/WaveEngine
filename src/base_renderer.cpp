#include "base_renderer.hpp"
#include "tools.hpp"

using std::make_unique;

BaseRenderer::BaseRenderer(const string & vertexShaderPath, const string & fragmentShaderPath)
	:
	_shaderBuffer(make_unique<ShaderBuffer>(Tools::getRootDirectoryPath() + vertexShaderPath, Tools::getRootDirectoryPath() + fragmentShaderPath))
{

}