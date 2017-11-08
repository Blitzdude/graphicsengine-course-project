#include "OGL\Texture2D.h"

namespace engine {

	Texture2D::Texture2D(int width, int height, int bytesPerPixel, const GLubyte* pixels) : Object(), m_textureId(0)
	{
		m_textureId = createSimpleTexture2D(width, height, bytesPerPixel, pixels);
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
}
