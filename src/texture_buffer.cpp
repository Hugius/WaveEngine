#include "texture_buffer.hpp"

TextureBuffer::TextureBuffer(const shared_ptr<Image> & image)
{
	if(image == nullptr)
	{
		abort();
	}

	glGenTextures(1, &_tboId);
	glBindTexture(GL_TEXTURE_2D, _tboId);

	switch(image->getBitsPerPixel())
	{
		case 24:
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getPixels());

			break;
		}
		case 32:
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());

			break;
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

TextureBuffer::~TextureBuffer()
{
	glDeleteTextures(1, &_tboId);
}

const unsigned int TextureBuffer::getTboId() const
{
	return _tboId;
}