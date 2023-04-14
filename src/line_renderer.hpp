#pragma once

#include "base_renderer.hpp"
#include "line.hpp"

using std::shared_ptr;

class LineRenderer final : public BaseRenderer
{
public:
	LineRenderer();

	void render(const vector<shared_ptr<Line>> & lines);

private:
	void _renderLine(const shared_ptr<Line> & line);

	static inline const string VERTEX_SHADER_PATH = "shaders\\line_vertex.glsl";
	static inline const string FRAGMENT_SHADER_PATH = "shaders\\line_fragment.glsl";
};