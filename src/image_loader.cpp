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

const shared_ptr<Image> ImageLoader::getImage(const string & filePath)
{
	const auto iterator = _cache.find(filePath);

	if(iterator != _cache.end())
	{
		return iterator->second;
	}

	shared_ptr<Image> loadedImage = _getImage(filePath);

	if(loadedImage == nullptr)
	{
		return nullptr;
	}

	_cache.insert({filePath, loadedImage});

	return loadedImage;
}

shared_ptr<Image> ImageLoader::_getImage(const string & filePath) const
{
	FILE * file = nullptr;

	if(fopen_s(&file, filePath.c_str(), "rb") != 0)
	{
		return nullptr;
	}

	unsigned char * header = new unsigned char[18];

	for(int index = 0; index < 18; index++)
	{
		header[index] = getc(file);
	}

	unsigned char rawIdLength = (header[0]);
	unsigned char rawColorMap = (header[1]);
	unsigned char rawImageType = (header[2]);
	unsigned short rawOriginX = ((header[9] << 8) | header[8]);
	unsigned short rawOriginY = ((header[11] << 8) | header[10]);
	unsigned short rawWidth = ((header[13] << 8) | header[12]);
	unsigned short rawHeight = ((header[15] << 8) | header[14]);
	unsigned char rawFormat = (header[16]);

	if(rawIdLength != 0)
	{
		return nullptr;
	}

	if(rawColorMap != 0)
	{
		return nullptr;
	}

	if((rawImageType != 2) && (rawImageType != 3))
	{
		return nullptr;
	}

	if((rawOriginX != 0) || (rawOriginY != 0))
	{
		return nullptr;
	}

	if((rawWidth == 0) || (rawHeight == 0))
	{
		return nullptr;
	}

	if((rawFormat != 24) && (rawFormat != 32))
	{
		return nullptr;
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