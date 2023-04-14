#pragma once

#include "vertex_buffer.hpp"
#include "texture_buffer.hpp"
#include "dvec3.hpp"
#include "dmat33.hpp"

#include <string>

using std::string;
using std::shared_ptr;

class Quad final
{
public:
	Quad(const shared_ptr<VertexBuffer> & vertexBuffer);

	void update();
	void setTextureBuffer(const shared_ptr<TextureBuffer> & textureBuffer);
	void setOpacity(const double value);
	void setColor(const dvec3 & value);
	void setPosition(const dvec2 & value);
	void setSize(const dvec2 & value);
	void setVisible(const bool value);
	void setLightness(const double value);
	void setUvMultiplier(const dvec2 & value);
	void setUvOffset(const dvec2 & value);

	const shared_ptr<VertexBuffer> & getVertexBuffer() const;
	const shared_ptr<TextureBuffer> & getTexture() const;

	const dmat33 & getTransformation() const;

	const dvec3 & getColor() const;

	const dvec2 & getPosition() const;
	const dvec2 & getSize() const;
	const dvec2 & getUvMultiplier() const;
	const dvec2 & getUvOffset() const;

	const double getOpacity() const;
	const double getLightness() const;

	const bool isVisible() const;

private:
	const shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<TextureBuffer> _textureBuffer;

	dmat33 _transformation = dmat33(1.0);

	dvec3 _color = dvec3(1.0);

	dvec2 _position = dvec2(0.0);
	dvec2 _size = dvec2(1.0);
	dvec2 _uvMultiplier = dvec2(1.0);
	dvec2 _uvOffset = dvec2(0.0);

	double _opacity = 1.0;
	double _lightness = 1.0;

	bool _isVisible = true;
};