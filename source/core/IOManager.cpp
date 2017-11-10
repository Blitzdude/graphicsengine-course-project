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
    bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
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

    bool IOManager::readFileToBuffer(std::string filePath, std::string & buffer)
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

	bool IOManager::readFileToBuffer(AAssetManager* manager, std::string filePath, std::vector<unsigned char>& buffer)
	{
    
        android_app* app;
        AAssetManager* assetManager = app->activity->assetManager;

		AAsset* asset = AAssetManager_open(assetManager, filePath.c_str(), AASSET_MODE_BUFFER);
        if(asset == NULL) {
            LOGI("FILE NOT FOUND");
            return false;
        }
        long size = AAsset_getLength(asset);
        AAsset_read(asset, &buffer[0], size);

        AAsset_close(asset);


        return true;
	}

    bool IOManager::readFileToBuffer(AAssetManager* manager, std::string filePath, std::string& buffer)
    {
		android_app* app;
        AAssetManager* assetManager = app->activity->assetManager;

        AAsset* asset = AAssetManager_open(assetManager, filePath.c_str(), AASSET_MODE_BUFFER);
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


