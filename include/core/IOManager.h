#ifndef _IOMANAGER_H_
#define _IOMANAGER_H_
#include <vector>
#include <string>
#include "Log.h"

namespace engine {

	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
		static bool readFileToBuffer(std::string filePath, std::string& buffer);
	};
}
#endif