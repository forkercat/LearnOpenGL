//
// Created by JunhaoW on 2020/12/3.
//

#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

class GameObject
{
public:
    // object state
    glm::vec2 Position, Size, Velocity;
    glm::vec3 Color;
    float     Rotation;
    bool      IsSolid;
    bool      Destroyed;
    // render state
    Texture2D Sprite;
    // constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size,
        Texture2D sprite, glm::vec3 color = glm::vec3(1.0f),
        glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    // draw sprite
    virtual void Draw(SpriteRenderer& renderer);
};

#endif //_GAME_OBJECT_H_
