#include "line_renderer.hpp"

LineRenderer::LineRenderer()
	:
	BaseRenderer(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH)
{

}

void LineRenderer::render(const vector<shared_ptr<Line>> & lines)
{
	_shaderBuffer->bind();

	for(const shared_ptr<Line> & line : lines)
	{
		_renderLine(line);
	}

	_shaderBuffer->unbind();
}

void LineRenderer::_renderLine(const shared_ptr<Line> & line)
{
	if(!line->isVisible())
	{
		return;
	}

	_shaderBuffer->uploadUniform("u_transformation", line->getTransformation());
	_shaderBuffer->uploadUniform("u_color", line->getColor());

	if(line->getVertexBuffer() != nullptr)
	{
		glBindVertexArray(line->getVertexBuffer()->getVaoId());
		glDrawArrays(GL_LINE_STRIP, 0, line->getVertexBuffer()->getVertexCount());
		glBindVertexArray(0);
	}
}