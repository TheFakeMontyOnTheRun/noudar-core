//
// Created by monty on 08/12/16.
//
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <Common.h>

#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

namespace Knights {

    CPlainFileLoader::CPlainFileLoader() {
    }

    CPlainFileLoader::CPlainFileLoader(std::string prefix) : mPrefix(prefix) {
    }

    std::vector<char> CPlainFileLoader::loadBinaryFileFromPath(const std::string &path) {
        FILE *fd;

        fd = fopen(( getFilePathPrefix() + path).c_str(), "rb");
        std::vector<char> toReturn = readToBuffer(fd);
        fclose(fd);

        return toReturn;
    }

    std::string CPlainFileLoader::loadFileFromPath(const std::string &path) {
        FILE *fd;

        fd = fopen(( getFilePathPrefix() + path).c_str(), "r");
        auto toReturn = readToString(fd);
        fclose(fd);

        return toReturn;
    }

    std::string CPlainFileLoader::getFilePathPrefix() {
        return mPrefix;
    }
}
