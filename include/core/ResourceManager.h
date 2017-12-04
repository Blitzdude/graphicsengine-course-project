#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
#include <core/Object.h>
#include <graphics/Texture2D.h>
#include <core/TextureCache.h>
#include <string>

namespace engine {

	//This is a way for us to access all our resources, such as
	//Models or textures.
	class ResourceManager : public Object
	{
	public:
		static Texture2D getTexture(std::string texturePath);
		static void createTexture(std::string texturePath, int width, int height, int bytesPerPixel, void* manager);
	private:
		static TextureCache m_textureCache;
	};

}
#endif // !_RESOURCE_MANAGER_H_