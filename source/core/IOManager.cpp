#include "core/IOManager.h"
#include <fstream>

#if defined(ANDROID)

#include <android/asset_manager.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <malloc.h>

#endif
namespace engine {

#if defined(_WIN32)
    bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer, void* manager)
    {
        std::ifstream file(filePath, std::ios::binary); // open file
        if (file.fail()) { // error check
			LOGI("failed to open %s : ", filePath.c_str());
          //  perror(filePath.c_str());
            return false;
        }

        //seek to the end
        file.seekg(0, std::ios::end);

        //Get the file size
        unsigned int fileSize = (unsigned int)file.tellg();
        file.seekg(0, std::ios::beg);

        //Reduce the file size by any header bytes that might be present
        fileSize -= (unsigned int)file.tellg();

        buffer.resize(fileSize); // resize the buffer to the size of the file. 
        file.read((char *)&(buffer[0]), fileSize);
        file.close();

        return true;
    }

    bool IOManager::readFileToBuffer(std::string filePath, std::string & buffer, void* manager)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (file.fail()) {
            perror(filePath.c_str());
            return false;
        }

        //seek to the end
        file.seekg(0, std::ios::end);

        //Get the file size
        unsigned int fileSize = (unsigned int)file.tellg();
        file.seekg(0, std::ios::beg);

        //Reduce the file size by any header bytes that might be present
        fileSize -= (unsigned int)file.tellg();

        buffer.resize(fileSize);
        file.read((char *)&(buffer[0]), fileSize);
        file.close();

        return true;
    }
}

#else

	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer, void* manager)
	{
        // make sure the manager is not nullptr

        if (manager == nullptr) {
            LOGE("manager does not exists!");
        }

		AAssetManager* mgr = static_cast<AAssetManager*>(manager);

		AAsset* asset = AAssetManager_open(mgr, filePath.c_str(), AASSET_MODE_BUFFER);
        if(asset == NULL) {
            LOGI("FILE NOT FOUND");
            return false;
        }
        long size = AAsset_getLength(asset);
        AAsset_read(asset, &buffer[0], size);

        AAsset_close(asset);

        return true;
	}

    bool IOManager::readFileToBuffer(std::string filePath, std::string& buffer, void* manager)
    {
        if (manager == nullptr) {
            LOGE("manager does not exists!");
        }

        AAssetManager* mgr = static_cast<AAssetManager*>(manager);

        AAsset* asset = AAssetManager_open(mgr, filePath.c_str(), AASSET_MODE_BUFFER);
        if(asset == NULL) {
            LOGI("FILE NOT FOUND");
            return false;
        }
        long size = AAsset_getLength(asset);
        AAsset_read(asset, &buffer[0], size);

        AAsset_close(asset);

        return true;

    }
}
#endif


