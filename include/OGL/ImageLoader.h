#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_

#include <string>
#include <graphics/Texture2D.h>

namespace engine {

	class ImageLoader  {
	public:

		static Texture2D loadPNG(std::string filepath, int width, int height, int bytesPerPixel, void* manager);

	};
}
#endif // !_IMAGE_LOADER_H_