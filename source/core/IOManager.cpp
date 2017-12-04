#include "core/IOManager.h"
#include <fstream>
#include <cstring>

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
		(void)manager;

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
		(void)manager;

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
	bool IOManager::readFileToBuffer(std::string filePath, unsigned char * buffer, void * manager)
	{
		(void)manager;

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

		unsigned char* temp = new unsigned char[fileSize];
		file.read((char*)temp, fileSize);
		file.close();

		*buffer = *temp;

		return true;
	}
}

#else
    // file reading using AAssetManager example here: https://stackoverflow.com/questions/13317387/how-to-get-file-in-assets-from-android-ndk
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer, void* manager)
	{
        // make sure the manager is not nullptr

        if (manager == nullptr)
        {
            LOGE("manager does not exists!");
        }

		AAssetManager* mgr = static_cast<AAssetManager*>(manager);

		AAsset* asset = AAssetManager_open(mgr, filePath.c_str(), AASSET_MODE_STREAMING);
        if(asset == NULL)
        {
            LOGI("FILE NOT FOUND");
            return false;
        }

        // holds size of searched file
        off64_t length = AAsset_getLength64(asset);
        LOGI("Asset Length: %d\n", (int)length );
        // keep track of remaining bytes to read
        off64_t remaining = AAsset_getRemainingLength64(asset);
        LOGI("Bytes to read: %d\n", (int)remaining);
        size_t Mb = 1024 * 1000; // 1 Mb is maximum chunk size for compressed assets
        size_t currChunk;
        buffer.reserve((unsigned long)length);

        // while we have data to read
        while (remaining != 0)
        {
            // set proper size for our next chunk
            if (remaining >= Mb)
            {
                currChunk = Mb;
            }
            else
            {
                currChunk = (size_t)remaining;
            }
            unsigned char chunk[currChunk];

            // read data chunk
            if(AAsset_read(asset, chunk, currChunk) > 0) //returns less than 0 on error
            {
                // and append it to our string/vector
                buffer.insert(buffer.end(), chunk, chunk + currChunk);
                remaining = AAsset_getRemainingLength64(asset);
                LOGI("Bytes to read: %d\n", (int)remaining);
            }
        }
        AAsset_close(asset);

        return true;
	}

    bool IOManager::readFileToBuffer(std::string filePath, std::string& buffer, void* manager)
    {
        if (manager == nullptr) {
            LOGE("manager does not exists!");
        }

        AAssetManager* mgr = static_cast<AAssetManager*>(manager);
        // open the asset
        AAsset* asset = AAssetManager_open(mgr, filePath.c_str(), AASSET_MODE_STREAMING);
        if(asset == NULL) {
            LOGI("FILE NOT FOUND");
            return false;
        }

        // holds size of searched file
        off64_t length = AAsset_getLength64(asset);
        LOGI("Asset Length: %lu\n", length );
        // keep track of remaining bytes to read
        off64_t remaining = AAsset_getRemainingLength64(asset);
        LOGI("Bytes to read: %lu\n", remaining);
        size_t Mb = 1000 *1024; // 1 Mb is maximum chunk size for compressed assets
        size_t currChunk;
        buffer.reserve(length);

        // while we have data to read
        while (remaining != 0)
        {
            // set proper size for our next chunk
            if (remaining >= Mb)
            {
                currChunk = Mb;
            }
            else
            {
                currChunk = (size_t)remaining;
            }
            unsigned char chunk[currChunk];

            // read data chunk
            if(AAsset_read(asset, chunk, currChunk) > 0) //returns less than 0 on error
            {
                // and append it to our string/vector
                buffer.insert(buffer.end(), chunk, chunk + currChunk);
                remaining = AAsset_getRemainingLength64(asset);
                LOGI("Bytes to read: %lu\n", remaining);
            }
        }


        AAsset_close(asset);

        return true;

    }
	bool IOManager::readFileToBuffer(std::string filePath, unsigned char * buffer, void * manager)
	{
        std::string in;


		if (manager == nullptr) {
			LOGE("manager does not exists!");
		}

		AAssetManager* mgr = static_cast<AAssetManager*>(manager);
		// open the asset
		AAsset* asset = AAssetManager_open(mgr, filePath.c_str(), AASSET_MODE_STREAMING);
		if (asset == NULL) {
			LOGI("FILE NOT FOUND");
			return false;
		}

        std::string tempBuffer;
		// holds size of searched file
		off64_t length = AAsset_getLength64(asset);
		LOGI("Asset Length: %lu\n", length);
		// keep track of remaining bytes to read
		off64_t remaining = AAsset_getRemainingLength64(asset);
		LOGI("Bytes to read: %lu\n", remaining);
		size_t Mb = 1000 * 1024; // 1 Mb is maximum chunk size for compressed assets
		size_t currChunk;

		// while we have data to read
		while (remaining != 0)
		{
			// set proper size for our next chunk
			if (remaining >= Mb)
			{
				currChunk = Mb;
			}
			else
			{
				currChunk = (size_t)remaining;
			}
			unsigned char chunk[currChunk];

			// read data chunk
			if (AAsset_read(asset, chunk, currChunk) > 0) //returns less than 0 on error
			{
				// and append it to our string/vector
                in.insert(tempBuffer.end(), chunk, chunk + currChunk);

				remaining = AAsset_getRemainingLength64(asset);
				LOGI("Bytes to read: %lu\n", remaining);
			}
		}

        unsigned char* out = new unsigned char[in.size()];

        strcpy((char*)out, in.c_str());

        buffer = out;

		AAsset_close(asset);

		return true;
	}
}
#endif


