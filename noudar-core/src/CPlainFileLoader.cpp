//
// Created by monty on 08/12/16.
//
#include <string>
#include <iostream>
#include <fstream>

#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

namespace Knights {
    
    CPlainFileLoader::CPlainFileLoader() {
    }
    
    CPlainFileLoader::CPlainFileLoader( std::string prefix ) : mPrefix( prefix ) {
    }

    
	std::string CPlainFileLoader::loadFileFromPath( const std::string& path ) {
		std::string entry;
		std::ifstream fileToLoad(path);

		char buffer;

		while (!fileToLoad.eof()) {
			fileToLoad >> buffer;
			entry.push_back(buffer);
		}

		return entry;
	}

	std::string CPlainFileLoader::getFilePathPrefix() {
        return mPrefix;
	}
}
