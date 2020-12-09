//
// Created by JunhaoW on 2020/12/5.
//

#ifndef _PARTICLE_GENERATOR_H_
#define _PARTICLE_GENERATOR_H_

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"
#include "game_object.h"

const float DEFAULT_PARTICLE_SCALE = 10.0f;

// Represents a single particle and its state
struct Particle
{
    glm::vec2 Position, Velocity;
    glm::vec4 Color;
    float     Scale;
    float     Life;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Scale(DEFAULT_PARTICLE_SCALE), Life(0.0f) { }
};

// Acts like a container for rendering a large number of
// particles by repeatedly spawning and updating particles
// killing them after some time.
class ParticleGenerator
{
public:
    // constructor
    ParticleGenerator(Shader shader, Texture2D texture, glm::vec3 particleColor, unsigned int amount);
    // update all particles
    void Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
    // update color
    void UpdateParticleColor(glm::vec3 color);
    // render all particles
    void Draw();

private:
    // state
    std::vector<Particle> particles;
    unsigned int          amount;
    glm::vec3             particleColor;
    // render state
    Shader                shader;
    Texture2D             texture;
    unsigned int          VAO;
    // initializes buffer and vertex attributes
    void init();
    // returns the first Particle index that's currently unused (Life <= 0.0f or 0 if no inactive particle)
    unsigned int firstUnusedParticle();
    // respawns particle
    void respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif //_PARTICLE_GENERATOR_H_
