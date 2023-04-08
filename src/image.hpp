#pragma once

class Image final
{
public:
	Image(const unsigned char * pixels, const int width, const int height, const int bitsPerPixel);
	~Image();

	const unsigned char * getPixels() const;

	const int getWidth() const;
	const int getHeight() const;
	const int getBitsPerPixel() const;

private:
	const unsigned char * _pixels;

	const int _width;
	const int _height;
	const int _bitsPerPixel;
};