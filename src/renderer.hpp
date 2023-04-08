#pragma once

#include "text.hpp"
#include "shader_buffer.hpp"

using std::unique_ptr;

class Renderer final
{
public:
	void initialize();
	void render(const vector<shared_ptr<Quad>> & quads, const vector<shared_ptr<Text>> & texts);

private:
	void _bindShader();
	void _renderQuad(const shared_ptr<Quad> quad);
	void _unbindShader();

	static inline const string VERTEX_SHADER_PATH = "shaders\\vertex.glsl";
	static inline const string FRAGMENT_SHADER_PATH = "shaders\\fragment.glsl";
	static inline const fvec3 BACKGROUND_COLOR = fvec3(0.25, 0.25, 0.5);

	unique_ptr<ShaderBuffer> _shaderBuffer = nullptr;
};