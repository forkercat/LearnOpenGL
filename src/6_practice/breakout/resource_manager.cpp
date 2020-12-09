//
// Created by JunhaoW on 2020/11/28.
//

#include "resource_manager.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader>    ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    std::cout << "Initializing Shader with paths: " << std::endl;
    std::cout << "  ---> " << vShaderFile << std::endl;
    std::cout << "  ---> " << fShaderFile << std::endl;
    if (gShaderFile != nullptr)
    {
        std::cout << "  ---> " << gShaderFile << std::endl;
    }

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    vertexCode   = getSourceCodeFromPath(vShaderFile, "VERTEX");
    fragmentCode = getSourceCodeFromPath(fShaderFile, "FRAGMENT");
    if (gShaderFile != nullptr)
    {
        geometryCode = getSourceCodeFromPath(gShaderFile, "GEOMETRY");
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();

    // 2. create shader object
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
    // create texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format    = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (data)
    {
        // now generate texture
        texture.Generate(width, height, data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << file << std::endl;
    }

    // free
    stbi_image_free(data);

    return texture;
}

// read source code from source file
std::string ResourceManager::getSourceCodeFromPath(const char* shaderPath, std::string type)
{
    std::string   shaderCode;
    std::ifstream shaderFile;
    // ensure ifstream objects can throw exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        // read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();
        // convert stream into string
        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::" << type << "::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        std::cout << e.code() << " | " << e.what() << std::endl;
    }
    return shaderCode;
}