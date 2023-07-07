#pragma once

#include "vertex_buffer.hpp"
#include "dvec3.hpp"
#include "dmat33.hpp"
#include "colors.hpp"

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

class Line final
{
public:
	Line(const shared_ptr<VertexBuffer> & vertexBuffer);

	void update();
	void setVertexBuffer(const shared_ptr<VertexBuffer> & vertexBuffer);
	void setColor(const dvec3 & value);
	void setPosition(const dvec2 & value);
	void setSize(const dvec2 & value);
	void setVisible(const bool value);

	const shared_ptr<VertexBuffer> & getVertexBuffer() const;

	const dmat33 & getTransformation() const;

	const dvec3 & getColor() const;

	const bool isVisible() const;

private:
	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;

	dmat33 _transformation = dmat33(1.0);

	dvec3 _color = Colors::WHITE;

	dvec2 _position = dvec2(0.0);
	dvec2 _size = dvec2(1.0);

	bool _isVisible = true;
};