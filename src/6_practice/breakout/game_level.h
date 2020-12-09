//
// Created by JunhaoW on 2020/12/3.
//

#ifndef _GAME_LEVEL_H_
#define _GAME_LEVEL_H_

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

class GameLevel
{
public:
    // level state
    std::vector<GameObject> Bricks;
    // constructor
    GameLevel() { }
    // loads level from file
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    // render level
    void Draw(SpriteRenderer& renderer);
    // check if the level is completed
    bool IsCompleted();

private:
    // initialize level from tile data
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif //_GAME_LEVEL_H_
