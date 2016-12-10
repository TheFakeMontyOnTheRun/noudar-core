//
// Created by monty on 08/12/16.
//

#ifndef NOUDAR_CORE_CPLAINFILELOADER_H
#define NOUDAR_CORE_CPLAINFILELOADER_H

namespace Knights {
	class CPlainFileLoader : public IFileLoaderDelegate {
        std::string mPrefix = "res/";
	public:
        explicit CPlainFileLoader();
        explicit CPlainFileLoader( std::string prefix );
		std::string loadFileFromPath( const std::string& path ) override ;
		std::string getFilePathPrefix() override;
	};
}

#endif //NOUDAR_CORE_CPLAINFILELOADER_H
