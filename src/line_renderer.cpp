#include "line_renderer.hpp"

LineRenderer::LineRenderer()
	:
	BaseRenderer(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH)
{

}

void LineRenderer::render(const shared_ptr<Line> & line)
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_transformation", line->getTransformation());
	_shaderBuffer->uploadUniform("u_color", line->getColor());

	glBindVertexArray(line->getVertexBuffer()->getVaoId());
	glDrawArrays(GL_LINE_STRIP, 0, line->getVertexBuffer()->getVertexCount());
	glBindVertexArray(0);

	_shaderBuffer->unbind();
}