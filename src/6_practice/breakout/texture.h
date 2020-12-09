//
// Created by JunhaoW on 2020/11/28.
//

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glad/glad.h>

class Texture2D
{
public:
    unsigned int ID;
    // size
    unsigned int Width, Height;
    // format
    unsigned int Internal_Format;
    unsigned int Image_Format;
    // texture configuration
    unsigned int Wrap_S;
    unsigned int Wrap_T;
    unsigned int Filter_Min;
    unsigned int Filter_Max;
    // constructor
    Texture2D();
    // generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
};

#endif //_TEXTURE_H_
