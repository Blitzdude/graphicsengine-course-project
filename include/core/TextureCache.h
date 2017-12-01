#ifndef _TEXTURE_CACHE_H_
#define _TEXTURE_CACHE_H_

#include <map>
#include <string>
#include "graphics/Texture2D.h"
#include "core/Object.h"

namespace engine {

	//This cache the textures so that multiple sprites can use the same textures
	class TextureCache : public Object 
	{
	public: 
		TextureCache();
		~TextureCache();

		Texture2D getTexture(std::string texturePath);
		void createTexture(std::string texturePath, int width, int height, int bytesPerPixel, void* manager);

	private:
		std::map<std::string, Texture2D> m_textureMap;
	};

}
#endif // !_TEXTURE_CACHE_H_