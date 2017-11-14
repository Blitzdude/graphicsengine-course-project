#include "OGL/Texture2D.h"
#include <core/Log.h>
#define STB_IMAGE_IMPLEMENTATION
#include <core/stb_image.h>

namespace engine {

	Texture2D::Texture2D(int width, int height, int bytesPerPixel, const GLubyte* pixels) : Object(), m_textureId(0)
	{
		m_textureId = createSimpleTexture2D(width, height, bytesPerPixel, pixels);
	}

	Texture2D::Texture2D(int width, int height, int bytesPerPixel, std::string source) : Object(), m_textureId(0)
	{
		m_textureId = createTexture2D(width, height, bytesPerPixel, source);
	}

	Texture2D::~Texture2D()
	{
		// TODO: delete texture on exit
	}

	GLuint Texture2D::createSimpleTexture2D(int width, int height, int bytesPerPixel, const GLubyte* pixels)
	{
		
		GLuint texId;
		assert(bytesPerPixel == 3 || bytesPerPixel == 4); // make sure bytes per pixel is correct
														  // use tightly packed data
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Generate a texture object
		glGenTextures(1, &texId);
		// bind the texture object
		glBindTexture(GL_TEXTURE_2D, texId);
		// Load texture
		GLuint fmt = bytesPerPixel == 3 ? GL_RGB : GL_RGBA; // format is either RGB or RGBA depeding on bid depth
		glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, pixels);

		// set filtering mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		return texId;
	}

	GLuint Texture2D::createTexture2D(int width, int height, int bytesPerPixel, std::string source)
	{
		// load texture file
		GLuint texId;
		unsigned char* image = stbi_load(source.c_str(), &width, &height, &bytesPerPixel, STBI_rgb_alpha);
	//	assert(bytesPerPixel == 3 || bytesPerPixel == 4); // make sure bytes per pixel is correct
														  // use tightly packed data
		if (image == nullptr)
			LOGE("Couldn't open test.png");
		assert(image != nullptr);

		// Generate texture object
		glGenTextures(1, &texId);
		// bind the texture object
		glBindTexture(GL_TEXTURE_2D, texId);
		// load texture
		GLuint fmt = bytesPerPixel == 3 ? GL_RGB : GL_RGBA; // format is either RGB or RGBA depeding on bid depth
		glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, image);

		// set filtering mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(image);
		return texId;
	}
}
