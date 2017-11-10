#ifndef _IOMANAGER_H_
#define _IOMANAGER_H_
#include <vector>
#include <string>
#include "Log.h"


#if defined (ANDROID)
	struct AAsset;
#endif // 
namespace engine {

	class IOManager
	{
	public:
#if defined(_WIN32)
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
		static bool readFileToBuffer(std::string filePath, std::string& buffer);
#elif defined (ANDROID)
		static bool readFileToBuffer(AAssetManager* manager, std::string filePath, std::vector<unsigned char>& buffer);
		static bool readFileToBuffer(AAssetManager* manager, std::string filePath, std::string& buffer);
#endif
	};
}
#endif // _IOMANAGER_H_