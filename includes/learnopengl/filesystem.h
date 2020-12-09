//
// Created by JunhaoW on 2020/10/29.
//

#ifndef LEARNOPENGL_INCLUDES_LEARNOPENGL_FILESYSTEM_H_
#define LEARNOPENGL_INCLUDES_LEARNOPENGL_FILESYSTEM_H_

#include <string>

typedef std::string (* Builder)(const std::string& path);

class FileSystem
{
public:
    static std::string getPath(const std::string& path);

private:
    static std::string const& getRoot();

    static std::string getPathRelativeRoot(const std::string& path);

    static std::string getPathRelativeBinary(const std::string& path);

    static Builder getPathBuilder();
};

#endif //LEARNOPENGL_INCLUDES_LEARNOPENGL_FILESYSTEM_H_
