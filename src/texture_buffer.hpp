#pragma once

#define GLEW_STATIC

#include "image.hpp"

#include <memory>
#include <glew.h>

using std::shared_ptr;

class TextureBuffer final
{
public:
	TextureBuffer(const shared_ptr<Image> & image);
	~TextureBuffer();

	const unsigned int getTboId() const;

private:
	unsigned int _tboId;
};