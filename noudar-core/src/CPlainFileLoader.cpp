//
// Created by monty on 08/12/16.
//
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

namespace Knights {

    CPlainFileLoader::CPlainFileLoader() {
    }

    CPlainFileLoader::CPlainFileLoader(std::string prefix) : mPrefix(prefix) {
    }

    std::vector<char> CPlainFileLoader::loadBinaryFileFromPath(const std::string &path) {
        std::ifstream fontFile(path, std::ios::binary);

        std::vector<char> buffer((
                                         std::istreambuf_iterator<char>(fontFile)),
                                 (std::istreambuf_iterator<char>()));

        return buffer;
    }

    std::string CPlainFileLoader::loadFileFromPath(const std::string &path) {
        std::string entry;
        std::ifstream fileToLoad(path);

        char buffer;

        while (!fileToLoad.eof()) {
            fileToLoad >>  std::noskipws >> buffer;
            entry.push_back(buffer);
        }

        return entry;
    }

    std::string CPlainFileLoader::getFilePathPrefix() {
        return mPrefix;
    }
}
