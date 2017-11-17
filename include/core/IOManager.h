#ifndef _IOMANAGER_H_
#define _IOMANAGER_H_
#include <vector>
#include <string>
#include "Log.h"



namespace engine {

	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer, void* manager);
		static bool readFileToBuffer(std::string filePath, std::string& buffer, void* manager);
	};
}
#endif // _IOMANAGER_H_