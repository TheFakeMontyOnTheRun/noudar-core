//
// Created by monty on 08/12/16.
//
#include <string>
#include <vector>
#include <functional>

using std::vector;

#include "Common.h"
#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

namespace Knights {

    CPlainFileLoader::CPlainFileLoader() {
    }

    CPlainFileLoader::CPlainFileLoader(const std::string &prefix) : mPrefix(prefix) {
    }

    size_t CPlainFileLoader::sizeOfFile(const std::string &path) {
        auto fd = fopen((getFilePathPrefix() + mFilenameTransformation(path)).c_str(), "rb");

        fseek(fd, 0, SEEK_END);
        auto endPos = ftell(fd);
        fclose(fd);

        return endPos;
    }

    uint8_t *CPlainFileLoader::loadBinaryFileFromPath(const std::string &path) {

        FILE *fd;

        fd = fopen((getFilePathPrefix() + mFilenameTransformation(path)).c_str(), "rb");

        if (fd == nullptr) {
            exit(0);
        }

        auto toReturn = readToBuffer(fd);
        fclose(fd);

        return toReturn;
    }

    std::string CPlainFileLoader::loadFileFromPath(const std::string &path) {
        FILE *fd;

        fd = fopen((getFilePathPrefix() + mFilenameTransformation(path)).c_str(), "r");

        if (fd == nullptr) {
            exit(0);
        }

        auto toReturn = readToString(fd);
        fclose(fd);

        return toReturn;
    }

    std::string CPlainFileLoader::getFilePathPrefix() {
        return mPrefix;
    }

    void CPlainFileLoader::setFilenameTransformation(std::function<std::string(std::string)> transform) {
        this->mFilenameTransformation = transform;
    }

    CPlainFileLoader::~CPlainFileLoader() {
    }
}
