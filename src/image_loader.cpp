#pragma warning(disable:6385)
#pragma warning(disable:6386)

#include "image_loader.hpp"
#include "tools.hpp"

#include <future>
#include <set>

using std::make_shared;
using std::set;
using std::future;
using std::launch;
using std::future_status;
using std::chrono::seconds;

const shared_ptr<Image> & ImageLoader::getImage(const string & filePath)
{
	const auto iterator = _cache.find(filePath);

	if(iterator != _cache.end())
	{
		return iterator->second;
	}

	_cache.insert({filePath, _getImage(filePath)});

	return getImage(filePath);
}

const shared_ptr<Image> ImageLoader::_getImage(const string & filePath) const
{
	FILE * file = nullptr;

	if(fopen_s(&file, filePath.c_str(), "rb") != 0)
	{
		abort();
	}

	unsigned char * header = new unsigned char[18];

	for(int index = 0; index < 18; index++)
	{
		header[index] = getc(file);
	}

	const unsigned char rawIdLength = (header[0]);
	const unsigned char rawColorMap = (header[1]);
	const unsigned char rawImageType = (header[2]);
	const unsigned short rawOriginX = ((header[9] << 8) | header[8]);
	const unsigned short rawOriginY = ((header[11] << 8) | header[10]);
	const unsigned short rawWidth = ((header[13] << 8) | header[12]);
	const unsigned short rawHeight = ((header[15] << 8) | header[14]);
	const unsigned char rawFormat = (header[16]);

	if(rawIdLength != 0)
	{
		abort();
	}

	if(rawColorMap != 0)
	{
		abort();
	}

	if((rawImageType != 2) && (rawImageType != 3))
	{
		abort();
	}

	if((rawOriginX != 0) || (rawOriginY != 0))
	{
		abort();
	}

	if((rawWidth == 0) || (rawHeight == 0))
	{
		abort();
	}

	if((rawFormat != 24) && (rawFormat != 32))
	{
		abort();
	}

	const int width = static_cast<int>(rawWidth);
	const int height = static_cast<int>(rawHeight);
	const int bitsPerPixel = static_cast<int>(rawFormat);
	const int bytesPerPixel = (bitsPerPixel / 8);
	const int size = (width * height * bytesPerPixel);

	unsigned char * pixels = new unsigned char[size];

	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			const int index = ((y * width * bytesPerPixel) + (x * bytesPerPixel));

			switch(bitsPerPixel)
			{
				case 24:
				{
					const unsigned char blue = static_cast<unsigned char>(getc(file));
					const unsigned char green = static_cast<unsigned char>(getc(file));
					const unsigned char red = static_cast<unsigned char>(getc(file));

					pixels[index + 0] = red;
					pixels[index + 1] = green;
					pixels[index + 2] = blue;

					break;
				}
				case 32:
				{
					const unsigned char blue = static_cast<unsigned char>(getc(file));
					const unsigned char green = static_cast<unsigned char>(getc(file));
					const unsigned char red = static_cast<unsigned char>(getc(file));
					const unsigned char alpha = static_cast<unsigned char>(getc(file));

					pixels[index + 0] = red;
					pixels[index + 1] = green;
					pixels[index + 2] = blue;
					pixels[index + 3] = alpha;

					break;
				}
			}
		}
	}

	delete[] header;

	fclose(file);

	return make_shared<Image>(pixels, width, height, bitsPerPixel);
}