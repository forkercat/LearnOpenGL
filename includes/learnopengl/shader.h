//
// Created by JunhaoW on 2020/10/28.
//

#ifndef SHADER_H_
#define SHADER_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // -------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
    {
        std::cout << "Initializing Shader with paths: " << std::endl;
        std::cout << "  ---> " << vertexPath << std::endl;
        std::cout << "  ---> " << fragmentPath << std::endl;
        if (geometryPath != nullptr)
        {
            std::cout << "  ---> " << geometryPath << std::endl;
        }

        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;

        vertexCode = getSourceCodeFromPath(vertexPath, "VERTEX");
        fragmentCode = getSourceCodeFromPath(fragmentPath, "FRAGMENT");
        if (geometryPath != nullptr)
        {
            geometryCode = getSourceCodeFromPath(geometryPath, "GEOMETRY");
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // if geometry shader is given
        unsigned int geometry;
        if (geometryPath != nullptr)
        {
            const char* gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, nullptr);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }

        // shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if (geometryPath != nullptr)
        {
            glAttachShader(ID, geometry);
        }

        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        // deletion
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryPath != nullptr)
        {
            glDeleteShader(geometry);
        }
    }

    // activate the shader
    // -------------------
    void use()
    {
        glUseProgram(ID);
    }

    // utility uniform functions
    // -------------------------
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string& name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    // read source code from source file
    std::string getSourceCodeFromPath(const char* shaderPath, std::string type)
    {
        std::string shaderCode;
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

    // utility function for checking errors
    // ------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")  // shader
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog
                          << "\n -- --------------------------------------------------- -- "
                          << std::endl;
            }
        }
        else  // program
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog
                          << "\n -- --------------------------------------------------- -- "
                          << std::endl;
            }
        }
    }
};

#endif //SHADER_M_H_
