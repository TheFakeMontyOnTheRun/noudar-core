//
// Created by monty on 08/12/16.
//

#ifndef NOUDAR_CORE_IFILELOADERDELEGATE_H
#define NOUDAR_CORE_IFILELOADERDELEGATE_H
namespace Knights {
	class IFileLoaderDelegate {
	public:
		virtual std::string loadFileFromPath( const std::string& path ) = 0;
		virtual uint8_t* loadBinaryFileFromPath( const std::string& path ) = 0;
        virtual size_t sizeOfFile(const std::string& path) = 0;
	private:
		virtual std::string getFilePathPrefix() = 0;
	};

	std::string filterLineBreaks( std::string input );
}
#endif //NOUDAR_CORE_IFILELOADERDELEGATE_H
