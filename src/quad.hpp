#pragma once

#include "vertex_buffer.hpp"
#include "texture_buffer.hpp"
#include "fvec3.hpp"
#include "fmat33.hpp"

#include <string>

using std::string;
using std::shared_ptr;

class Quad final
{
public:
	Quad(const shared_ptr<VertexBuffer> vertexBuffer, const shared_ptr<TextureBuffer> textureBuffer, int depth);

	void update();
	void setOpacity(const double value);
	void setColor(const fvec3 & value);
	void setPosition(const fvec2 & value);
	void setRotation(const double value);
	void setSize(const fvec2 & value);
	void setVisible(const bool value);
	void setLightness(const double value);
	void setUvMultiplier(const fvec2 & value);
	void setUvOffset(const fvec2 & value);

	const shared_ptr<VertexBuffer> getVertexBuffer() const;
	const shared_ptr<TextureBuffer> getTexture() const;

	const fmat33 & getTransformation() const;

	const fvec3 & getColor() const;

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;
	const fvec2 & getUvMultiplier() const;
	const fvec2 & getUvOffset() const;

	const double getOpacity() const;
	const double getRotation() const;
	const double getLightness() const;

	const int getDepth() const;

	const bool isVisible() const;

private:
	const shared_ptr<VertexBuffer> _vertexBuffer;
	const shared_ptr<TextureBuffer> _textureBuffer;

	const int _depth;

	fmat33 _transformation = fmat33(1.0);

	fvec3 _color = fvec3(1.0);

	fvec2 _position = fvec2(0.0);
	fvec2 _size = fvec2(1.0);
	fvec2 _uvMultiplier = fvec2(1.0);
	fvec2 _uvOffset = fvec2(0.0);

	double _rotation = 0.0;
	double _opacity = 1.0;
	double _lightness = 1.0;

	bool _isVisible = true;
};