#ifndef _IOMANAGER_H_
#define _IOMANAGER_H_
#include <vector>
#include <string>
#include "Log.h"


#if defined (ANDROID)
#include <android/asset_manager.h>
	struct AAsset;
#endif // 
namespace engine {

	class IOManager
	{
	public:
#if !defined(ANDROID)
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
		static bool readFileToBuffer(std::string filePath, std::string& buffer);
#else
		static bool readFileToBuffer( std::string filePath, std::vector<unsigned char>& buffer, AAssetManager* manager );
		static bool readFileToBuffer( std::string filePath, std::string& buffer, AAssetManager* manager);
#endif
	};
}
#endif // _IOMANAGER_H_