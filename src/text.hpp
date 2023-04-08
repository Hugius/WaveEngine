#pragma once

#include "quad.hpp"
#include "ivec2.hpp"

#include <unordered_map>

using std::unordered_map;
using std::vector;

class Text final
{
public:
	Text(const shared_ptr<VertexBuffer> & vertexBuffer, const shared_ptr<TextureBuffer> & textureBuffer, const int depth, const string & content);

	void update();
	void setContent(const string & value);
	void setOpacity(const double value);
	void setColor(const fvec3 & value);
	void setPosition(const fvec2 & value);
	void setRotation(const double value);
	void setSize(const fvec2 & value);
	void setVisible(const bool value);
	void setLightness(const double value);

	const vector<shared_ptr<Quad>> & getQuads() const;

	const string & getContent() const;

	const fvec3 & getColor() const;

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;

	const double getOpacity() const;
	const double getRotation() const;
	const double getLightness() const;

	const int getDepth() const;

	const bool isVisible() const;

private:
	static inline const unordered_map<char, ivec2> _fontMapIndices =
	{
		{' ', ivec2(0, 5)},
		{'!', ivec2(1, 5)},
		{'"', ivec2(2, 5)},
		{'#', ivec2(3, 5)},
		{'$', ivec2(4, 5)},
		{'%', ivec2(5, 5)},
		{'&', ivec2(6, 5)},
		{'\'', ivec2(7, 5)},
		{'(', ivec2(8, 5)},
		{')', ivec2(9, 5)},
		{'*', ivec2(10, 5)},
		{'+', ivec2(11, 5)},
		{',', ivec2(12, 5)},
		{'-', ivec2(13, 5)},
		{'.', ivec2(14, 5)},
		{'/', ivec2(15, 5)},
		{'0', ivec2(0, 4)},
		{'1', ivec2(1, 4)},
		{'2', ivec2(2, 4)},
		{'3', ivec2(3, 4)},
		{'4', ivec2(4, 4)},
		{'5', ivec2(5, 4)},
		{'6', ivec2(6, 4)},
		{'7', ivec2(7, 4)},
		{'8', ivec2(8, 4)},
		{'9', ivec2(9, 4)},
		{':', ivec2(10, 4)},
		{';', ivec2(11, 4)},
		{'<', ivec2(12, 4)},
		{'=', ivec2(13, 4)},
		{'>', ivec2(14, 4)},
		{'?', ivec2(15, 4)},
		{'@', ivec2(0, 3)},
		{'A', ivec2(1, 3)},
		{'B', ivec2(2, 3)},
		{'C', ivec2(3, 3)},
		{'D', ivec2(4, 3)},
		{'E', ivec2(5, 3)},
		{'F', ivec2(6, 3)},
		{'G', ivec2(7, 3)},
		{'H', ivec2(8, 3)},
		{'I', ivec2(9, 3)},
		{'J', ivec2(10, 3)},
		{'K', ivec2(11, 3)},
		{'L', ivec2(12, 3)},
		{'M', ivec2(13, 3)},
		{'N', ivec2(14, 3)},
		{'O', ivec2(15, 3)},
		{'P', ivec2(0, 2)},
		{'Q', ivec2(1, 2)},
		{'R', ivec2(2, 2)},
		{'S', ivec2(3, 2)},
		{'T', ivec2(4, 2)},
		{'U', ivec2(5, 2)},
		{'V', ivec2(6, 2)},
		{'W', ivec2(7, 2)},
		{'X', ivec2(8, 2)},
		{'Y', ivec2(9, 2)},
		{'Z', ivec2(10, 2)},
		{'[', ivec2(11, 2)},
		{'\\', ivec2(12, 2)},
		{']', ivec2(13, 2)},
		{'^', ivec2(14, 2)},
		{'_', ivec2(15, 2)},
		{'`', ivec2(0, 1)},
		{'a', ivec2(1, 1)},
		{'b', ivec2(2, 1)},
		{'c', ivec2(3, 1)},
		{'d', ivec2(4, 1)},
		{'e', ivec2(5, 1)},
		{'f', ivec2(6, 1)},
		{'g', ivec2(7, 1)},
		{'h', ivec2(8, 1)},
		{'i', ivec2(9, 1)},
		{'j', ivec2(10, 1)},
		{'k', ivec2(11, 1)},
		{'l', ivec2(12, 1)},
		{'m', ivec2(13, 1)},
		{'n', ivec2(14, 1)},
		{'o', ivec2(15, 1)},
		{'p', ivec2(0, 0)},
		{'q', ivec2(1, 0)},
		{'r', ivec2(2, 0)},
		{'s', ivec2(3, 0)},
		{'t', ivec2(4, 0)},
		{'u', ivec2(5, 0)},
		{'v', ivec2(6, 0)},
		{'w', ivec2(7, 0)},
		{'x', ivec2(8, 0)},
		{'y', ivec2(9, 0)},
		{'z', ivec2(10, 0)},
		{'{', ivec2(11, 0)},
		{'|', ivec2(12, 0)},
		{'}', ivec2(13, 0)},
		{'~', ivec2(14, 0)}
	};

	static inline const int FONT_MAP_ROW_COUNT = 6;
	static inline const int FONT_MAP_COLUMN_COUNT = 16;

	const shared_ptr<VertexBuffer> _vertexBuffer;
	const shared_ptr<TextureBuffer> _textureBuffer;

	const int _depth;

	vector<shared_ptr<Quad>> _quads = {};

	string _content = "";

	fvec3 _color = fvec3(1.0);

	fvec2 _position = fvec2(0.0);
	fvec2 _size = fvec2(1.0);

	double _rotation = 0.0;
	double _opacity = 1.0;
	double _lightness = 1.0;

	bool _isVisible = true;
};