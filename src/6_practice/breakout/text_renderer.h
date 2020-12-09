//
// Created by JunhaoW on 2020/12/7.
//

#ifndef _TEXT_RENDERER_H_
#define _TEXT_RENDERER_H_

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "shader.h"

// Holds state information relevant to a character as loaded using FreeType
struct Character
{
    unsigned int TextureID;  // glyph texture
    glm::ivec2   Size;       // size of glyph
    glm::ivec2   Bearing;    // offset from baseline to left/top of glyph
    unsigned int Advance;    // horizontal offset to advance to next glyph
};

// A renderer class for rendering text displayed by a font loaded using
// FreeType library. A single font is loaded, processed into a list of
// Character items for later rendering.
class TextRenderer
{
public:
    // holds a list of pre-complied Characters
    std::map<char, Character> Characters;
    // shader used for text rendering
    Shader TextShader;
    // constructor
    TextRenderer(unsigned int width, unsigned int height);
    // pre-complies a list of characters from the given font
    void Load(std::string font, unsigned int fontSize);
    // renders a string of text using the precompiled list of characters
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));

private:
    // render state
    unsigned int VAO, VBO;
};

#endif //_TEXT_RENDERER_H_
