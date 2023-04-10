#pragma warning(disable:6386)

#include "image.hpp"

#include <stdlib.h>

Image::Image(const unsigned char * pixels, const int width, const int height, const int bitsPerPixel)
	:
	_pixels(pixels),
	_width(width),
	_height(height),
	_bitsPerPixel(bitsPerPixel)
{
	if(_pixels == nullptr)
	{
		abort();
	}

	if(_width == 0)
	{
		abort();
	}

	if(_height == 0)
	{
		abort();
	}
}

Image::~Image()
{
	delete[] _pixels;
}

const unsigned char * Image::getPixels() const
{
	return _pixels;
}

const int Image::getWidth() const
{
	return _width;
}

const int Image::getHeight() const
{
	return _height;
}

const int Image::getBitsPerPixel() const
{
	return _bitsPerPixel;
}