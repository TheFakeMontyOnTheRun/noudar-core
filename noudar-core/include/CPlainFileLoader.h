//
// Created by monty on 08/12/16.
//

#ifndef NOUDAR_CORE_CPLAINFILELOADER_H
#define NOUDAR_CORE_CPLAINFILELOADER_H

namespace Knights {
    class CPlainFileLoader : public IFileLoaderDelegate {
        std::string mPrefix = "res/";
        std::function<std::string(std::string)> mFilenameTransformation = [](
                const std::string &filename) { return filename; };
    public:
        explicit CPlainFileLoader();

        ~CPlainFileLoader() override;

        explicit CPlainFileLoader(const std::string &prefix);

        uint8_t *loadBinaryFileFromPath(const std::string &path) override;

        size_t sizeOfFile(const std::string &path) override;

        std::string loadFileFromPath(const std::string &path) override;

        std::string getFilePathPrefix() override;

        void setFilenameTransformation(std::function<std::string(std::string)> transform);
    };
}

#endif //NOUDAR_CORE_CPLAINFILELOADER_H
