#include "OGL/Texture2D.h"
#include "core/IOManager.h"

#if defined(ANDROID)

#include <android/asset_manager.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <malloc.h>
#endif

#include <core/Log.h>
#define STB_IMAGE_IMPLEMENTATION
#include <core/stb_image.h>

namespace engine {
	Texture2D::Texture2D(int width, int height, int bytesPerPixel, const GLubyte* pixels) : Object(), m_textureId(0)
	{
		m_textureId = createSimpleTexture2D(width, height, bytesPerPixel, pixels);
	}

	Texture2D::Texture2D(int width, int height, int bytesPerPixel, std::string source, void* manager) : Object(), m_textureId(0)
	{
		m_textureId = createTexture2D(width, height, bytesPerPixel, source,  manager);
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

	#if defined (_WIN32)
	GLuint Texture2D::createTexture2D(int width, int height, int bytesPerPixel, std::string source, void* manager)
	{
		// load texture file
		GLuint texId;

		unsigned char* image = stbi_load(source.c_str(), &width, &height, &bytesPerPixel, STBI_rgb_alpha);
	
		// Generate texture object
		glGenTextures(1, &texId);
		// bind the texture object
		glBindTexture(GL_TEXTURE_2D, texId);
		// load texture
		GLuint fmt = bytesPerPixel == 3 ? GL_RGB : GL_RGBA; // format is either RGB or RGBA depending on bit depth
		glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, image);

		// set filtering mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(image);
		return texId;
	}

	#elif (ANDROID)
	GLuint Texture2D::createTexture2D(int width, int height, int bytesPerPixel, std::string source, void* manager)
	{
		GLuint texId;

		// make sure the manager is not nullptr
		if (manager == nullptr)
		{
			LOGE("manager does not exists!");
		}

		AAssetManager* mgr = static_cast<AAssetManager*>(manager);

		AAsset* asset;
		asset = AAssetManager_open(mgr, source.c_str(), AASSET_MODE_BUFFER);
		if (asset == nullptr)
			LOGE("Asset not found %s", source.c_str());

		off_t assetLength = AAsset_getLength(asset);
		unsigned char* bufferPoint = new unsigned char[assetLength];

		AAsset_read(asset, bufferPoint, (size_t)assetLength);

		int stb_fmt = bytesPerPixel == 3 ? STBI_rgb : STBI_rgb_alpha; // format is either RGB or RGBA depending on bit depth
		stbi_uc* image = stbi_load_from_memory(bufferPoint, (int)assetLength, &width, &height, &bytesPerPixel, stb_fmt);

		AAsset_close(asset);

        // Generate texture object
        glGenTextures(1, &texId);
        // bind the texture object
        glBindTexture(GL_TEXTURE_2D, texId);
        // load texture
        GLuint fmt = bytesPerPixel == 3 ? GL_RGB : GL_RGBA; // format is either RGB or RGBA depending on bit depth
        glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, image);

        // set filtering mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_image_free(image);
        return texId;
	}
	#endif
}
