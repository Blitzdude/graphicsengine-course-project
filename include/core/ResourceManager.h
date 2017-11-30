#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <string>

namespace engine {

	//This is a way for us to access all our resources, such as
	//Models or textures.
	class ResourceManager
	{
	public:
		static Texture2D getTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;
	};

}
#endif // !_RESOURCE_MANAGER_H_