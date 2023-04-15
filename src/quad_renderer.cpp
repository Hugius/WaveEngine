#include "quad_renderer.hpp"

QuadRenderer::QuadRenderer()
	:
	BaseRenderer(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void QuadRenderer::render(const vector<shared_ptr<Quad>> & quads)
{
	_shaderBuffer->bind();

	for(const shared_ptr<Quad> & quad : quads)
	{
		_renderQuad(quad);
	}

	_shaderBuffer->unbind();
}

void QuadRenderer::render(const vector<shared_ptr<Text>> & texts)
{
	glEnable(GL_BLEND);

	_shaderBuffer->bind();

	for(const shared_ptr<Text> & text : texts)
	{
		for(const shared_ptr<Quad> & quad : text->getQuads())
		{
			_renderQuad(quad);
		}
	}

	_shaderBuffer->unbind();

	glDisable(GL_BLEND);
}

void QuadRenderer::_renderQuad(const shared_ptr<Quad> & quad)
{
	if(!quad->isVisible())
	{
		return;
	}

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

	if(quad->getVertexBuffer() != nullptr)
	{
		glBindVertexArray(quad->getVertexBuffer()->getVaoId());
		glDrawArrays(GL_TRIANGLES, 0, quad->getVertexBuffer()->getVertexCount());
		glBindVertexArray(0);
	}

	if(quad->getTexture() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}