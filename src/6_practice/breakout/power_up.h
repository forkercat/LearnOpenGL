//
// Created by JunhaoW on 2020/12/6.
//

#ifndef _POWER_UP_H_
#define _POWER_UP_H_

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"

// The size of a PowerUp block
const glm::vec2 POWERUP_SIZE(60.0f, 20.0f);
// Velocity that a PowerUp block has when spawned
const glm::vec2 VELOCITY(0.0f, 150.0f);

class PowerUp : public GameObject
{
public:
    // PowerUp state
    std::string Type;
    float       Duration;
    bool        Activated;
    // constructor
    PowerUp(std::string type, glm::vec3 color, float duration, glm::vec2 position, Texture2D texture)
        : GameObject(position, POWERUP_SIZE, texture, color, VELOCITY),
          Type(type), Duration(duration), Activated()
    {

    }
};

#endif //_POWER_UP_H_
