#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

#include "core\Object.h"
#include "GLES2\gl2.h"
#include <assert.h>

namespace engine {

	class Texture2D : public Object {
	public:
		Texture2D(int width, int height, int bytesPerPixel, const GLubyte* pixels);
		~Texture2D();

		GLuint createSimpleTexture2D(int width, int height, int bytesPerPixel, const GLubyte* pixels);

		// getters
		const GLuint& getTextureId() const { return m_textureId; };

	private:
		// attributes
		GLuint m_textureId;
	};
}
#endif // !_TEXTURE2D_H_