//
// Created by JunhaoW on 2020/12/4.
//

#ifndef _BALL_OBJECT_H_
#define _BALL_OBJECT_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"

class BallObject : public GameObject
{
public:
    // ball state
    float Radius;
    bool  Stuck;
    bool  Sticky;
    bool  PassThrough;
    bool  SpeedUp;
    // constructor(s)
    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);
    // moves the ball, keeping it constrained within the window bounds (except bottom edge)
    glm::vec2 Move(float dt, unsigned int window_width);
    // resets the ball to original state
    void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif //_BALL_OBJECT_H_
