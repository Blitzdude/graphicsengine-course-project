#include "OGL/ImageLoader.h"
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
	Texture2D ImageLoader::loadPNG(std::string filepath, int width, int height, int bytesPerPixel, void* manager)
	{
		// create Texture2D and initialize its fields to zero
		Texture2D texture = {};

		// This is the buffer input we load the file into
		/*
		std::string in;
		// Read the image file with IOManager
		if (IOManager::readFileToBuffer(filepath, in, manager) == false)
		{
			LOGE("Failed to load PNG file to Buffer! %s", filepath.c_str());
		}
		LOGI("%s\n", in.c_str());
		*/
		
		// Decode the png using stbi_load_from_memmory
		int stb_fmt = bytesPerPixel == 3 ? STBI_rgb : STBI_rgb_alpha; // format depending on bit Depth
		stbi_uc* out = stbi_load(filepath.c_str(), &width, &height, &bytesPerPixel, stb_fmt);
		//unsigned char* out = stbi_load_from_memory((unsigned char*)in.c_str(), sizeof(in), &width, &height, &bytesPerPixel, stb_fmt);

		// Generate the openGL texture object
		glGenTextures(1, &(texture.id));
		
		// bind the texture object
		glBindTexture(GL_TEXTURE_2D, texture.id);

		// upload the pixels to the texture
		GLuint fmt = bytesPerPixel == 3 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, out);

		// set some texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Generate the mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

		// unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0);
		// return the texture data
		
		texture.width = width;
		texture.height = height;
		texture.filepath = filepath;

		return texture;
	}
}
