#include "quad_renderer.hpp"
#include "tools.hpp"

#include <map>

using std::make_shared;
using std::make_unique;
using std::map;
using std::vector;

void QuadRenderer::initialize()
{
	_shaderBuffer = make_unique<ShaderBuffer>(Tools::getRootDirectoryPath() + VERTEX_SHADER_PATH, Tools::getRootDirectoryPath() + FRAGMENT_SHADER_PATH);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void QuadRenderer::render(const vector<shared_ptr<Quad>> & quads, const vector<shared_ptr<Text>> & texts)
{
	glClear(GL_COLOR_BUFFER_BIT);

	_bindShader();

	map<int, vector<shared_ptr<Quad>>> orderedQuads = {};

	for(const shared_ptr<Quad> & quad : quads)
	{
		orderedQuads.insert({quad->getDepth(), {quad}});
	}

	for(const shared_ptr<Text> & text : texts)
	{
		orderedQuads.insert({text->getDepth(), text->getQuads()});
	}

	for(const auto & [depth, quads] : orderedQuads)
	{
		for(const shared_ptr<Quad> & quad : quads)
		{
			if(!quad->isVisible())
			{
				continue;
			}

			_renderQuad(quad);
		}
	}

	_unbindShader();
}

void QuadRenderer::render(const shared_ptr<VertexBuffer> & vertexBuffer)
{
	_bindShader();

	_shaderBuffer->uploadUniform("u_transformation", dmat33(1.0));
	_shaderBuffer->uploadUniform("u_color", dvec3(1.0));
	_shaderBuffer->uploadUniform("u_opacity", 1.0);
	_shaderBuffer->uploadUniform("u_lightness", 1.0);
	_shaderBuffer->uploadUniform("u_uvMultiplier", 0.0);
	_shaderBuffer->uploadUniform("u_uvOffset", 0.0);
	_shaderBuffer->uploadUniform("u_hasTexture", false);

	glBindVertexArray(vertexBuffer->getVaoId());
	glDrawArrays(GL_LINE_STRIP, 0, vertexBuffer->getVertexCount());
	glBindVertexArray(0);

	_unbindShader();
}

void QuadRenderer::_bindShader()
{
	_shaderBuffer->bind();

	glEnable(GL_BLEND);
}

void QuadRenderer::_renderQuad(const shared_ptr<Quad> & quad)
{
	_shaderBuffer->uploadUniform("u_transformation", quad->getTransformation());
	_shaderBuffer->uploadUniform("u_color", quad->getColor());
	_shaderBuffer->uploadUniform("u_opacity", quad->getOpacity());
	_shaderBuffer->uploadUniform("u_lightness", quad->getLightness());
	_shaderBuffer->uploadUniform("u_uvMultiplier", quad->getUvMultiplier());
	_shaderBuffer->uploadUniform("u_uvOffset", quad->getUvOffset());
	_shaderBuffer->uploadUniform("u_hasTexture", quad->getTexture() != nullptr);

	if(quad->getTexture() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, quad->getTexture()->getTboId());
	}

	glBindVertexArray(quad->getVertexBuffer()->getVaoId());
	glDrawArrays(GL_TRIANGLES, 0, quad->getVertexBuffer()->getVertexCount());
	glBindVertexArray(0);

	if(quad->getTexture() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void QuadRenderer::_unbindShader()
{
	glDisable(GL_BLEND);

	_shaderBuffer->unbind();
}