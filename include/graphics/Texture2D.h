#ifndef _TEXTURE_2D_H_
#define _TEXTURE_2D_H_
#include <GLES2\gl2.h>
#include <string>

namespace engine {
	struct Texture2D
	{
		std::string filepath = "";
		GLuint id;
		int width;
		int height;
	};
}

#endif // !_TEXTURE_2D_H_