//
// Created by monty on 08/12/16.
//
#include <string>
#include <iostream>
#include <fstream>

#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

namespace Knights {
	std::string CPlainFileLoader::loadFileFromPath( const std::string& path ) {
		std::string entry;
		std::ifstream fileToLoad(path);

		char buffer;

		whi le (!fileToLoad.eof()) {
			fileToLoad >> buffer;
			entry += buffer;
		}

		return entry;
	}

	std::string CPlainFileLoader::getFilePathPrefix() {
		return "res/";
	}
}