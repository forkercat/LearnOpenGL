//
// Created by JunhaoW on 2020/12/5.
//

#ifndef _POST_PROCESSOR_H_
#define _POST_PROCESSOR_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "shader.h"

// It renders the game on a textured quad after which one can enable
// specific effects by enabling either Confuse, Chaos, or Shake boolean.
// It is required to call BeginRender() before rendering the game and
// EndRender() after rendering the game for the class to work.
class PostProcessor
{
public:
    // state
    Shader       PostProcessingShader;
    Texture2D    Texture;
    unsigned int Width, Height;
    // options
    bool         Confuse, Chaos, Shake;
    // constructor
    PostProcessor(const Shader& shader, unsigned int width, unsigned int height);
    // prepares the postprocessor's framebuffer operations
    void BeginRender();
    // stores all the rendered data into a texture object
    void EndRender();
    // renders the PostProcessor texture quad (as a screen-encompassing large sprite)
    void Render(float time);
private:
    // render state
    unsigned int MSFBO;  // Multisampled FBO
    unsigned int FBO;  // used for blitting MS color-buffer to texture
    unsigned int RBO;  // used for multisampled color buffer
    unsigned int VAO;
    // initialize quad for rendering postprocessing texture
    void initRenderData();
};

#endif //_POST_PROCESSOR_H_
