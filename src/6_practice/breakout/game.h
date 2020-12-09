//
// Created by JunhaoW on 2020/11/27.
//

#ifndef _GAME_H_
#define _GAME_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_level.h"
#include "power_up.h"

// Represents the current state of the game
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Represents the four possible collision directions
enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// Defines a Collision typedef that represents collision data
// <collision or not?, what direction?, diff vector = center - closest point>
typedef std::tuple<bool, Direction, glm::vec2> Collision;

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float     PLAYER_VELOCITY(500.0f);
// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float     BALL_RADIUS               = 12.5f;
// const float     BALL_RADIUS               = 15.0f;
// Initial particle color
const glm::vec3 INITIAL_PARTICLE_COLOR(1.0f, 1.0f, 1.0f);
// Shake Period
const float     SHAKE_PERIOD              = 0.1f;
// PowerUp
const int       POSITIVE_POWERUP_CHANCE   = 35;
const int       NEGATIVE_POWERUP_CHANCE   = 15;
const int       POSITIVE_POWERUP_DURATION = 10.0f;
const int       NEGATIVE_POWERUP_DURATION = 6.0f;

class Game
{
public:
    // game state
    GameState              State;
    bool                   Keys[1024];
    bool                   KeysProcessed[1024];
    unsigned int           Width, Height;
    std::vector<GameLevel> Levels;
    std::vector<PowerUp>   PowerUps;
    unsigned int           Level;
    unsigned int           Lives;
    // device related
    bool                   RunningInRetina;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void DoCollisions();
    // reset
    void ResetLevel();
    void ResetPlayer();
    void ResetParticleGenerator();
    // powerups
    void SpawnPowerUps(GameObject& block);
    void UpdatePowerUps(float dt);
};

#endif //_GAME_H_
