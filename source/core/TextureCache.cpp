#include "core/TextureCache.h"
#include "OGL/ImageLoader.h"
#include "core/Log.h"

namespace engine {

engine::TextureCache::TextureCache()
{
}

engine::TextureCache::~TextureCache()
{
}

Texture2D TextureCache::getTexture(std::string texturePath)
{
	// lookup the texture and see if its in the map
	auto mit = m_textureMap.find(texturePath);

	// check if its not in the map
	if (mit == m_textureMap.end()) {
		LOGE("Texture not found in cache!: %s", texturePath.c_str());
	}
	// if it is:

	return mit->second;
}

void TextureCache::createTexture(std::string texturePath, int width, int height, int bytesPerPixel, void* manager)
{
	//lookup the texture and see if its in the map
	auto mit = m_textureMap.find(texturePath);

	//check if its not in the map
	if (mit == m_textureMap.end()) {
		//Load the texture
		Texture2D newTexture = ImageLoader::loadPNG(texturePath, width, height, bytesPerPixel, manager);

		//Insert it into the map
		m_textureMap.insert(make_pair(texturePath, newTexture));

		LOGI("Texture inserted into cache! %s", texturePath.c_str());
	}
	else 
	{
		LOGI("Texture with path: %s already exists", texturePath.c_str());
	}
}

}


