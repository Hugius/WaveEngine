#pragma once

#include "text.hpp"
#include "base_renderer.hpp"

using std::unique_ptr;

class QuadRenderer final : public BaseRenderer
{
public:
	QuadRenderer();

	void render(const vector<shared_ptr<Quad>> & quads, const vector<shared_ptr<Text>> & texts);

private:
	void _renderQuad(const shared_ptr<Quad> & quad);

	static inline const string VERTEX_SHADER_PATH = "shaders\\quad_vertex.glsl";
	static inline const string FRAGMENT_SHADER_PATH = "shaders\\quad_fragment.glsl";
};