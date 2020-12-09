//
// Created by JunhaoW on 2020/10/23.
//

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

// #include <learnopengl/shader_s.h>
#include <learnopengl/shader.h>
#include <learnopengl/filesystem.h>

// stb_image
#include <stb_image.h>

// irrklang
#include <irrKlang/irrKlang.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/random.hpp>


#include <vector>

using namespace irrklang;



int main()
{
    ISoundEngine *SoundEngine = createIrrKlangDevice();

    // std::string pluginPath = FileSystem::getPath("dlls").c_str();
    //
    // std::cout <<pluginPath << std::endl;
    //
    // SoundEngine->loadPlugins(pluginPath.c_str());

    SoundEngine->play2D(FileSystem::getPath("resources/audio/breakout.mp3").c_str(), true);

    getchar();

    return 0;
}