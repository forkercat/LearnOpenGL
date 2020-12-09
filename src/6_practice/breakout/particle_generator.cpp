//te
// Created by JunhaoW on 2020/12/5.
//

#include "particle_generator.h"

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, glm::vec3 particleColor, unsigned int amount)
    : shader(shader), texture(texture), particleColor(particleColor), amount(amount)
{
    this->init();
}

void ParticleGenerator::Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset)
{
    // add new particles
    for (unsigned int i = 0; i < newParticles; ++i)
    {
        int unusedParticle = this->firstUnusedParticle();
        this->respawnParticle(this->particles[unusedParticle], object, offset);
    }
    // update all particles
    for (unsigned int i = 0; i < this->amount; ++i)
    {
        Particle& p = this->particles[i];
        p.Life -= dt;
        if (p.Life > 0.0f)
        {
            p.Position -= p.Velocity * dt;  // slower
            p.Color.a -= dt * 2.5f;
        }
    }
}

void ParticleGenerator::UpdateParticleColor(glm::vec3 color)
{
    this->particleColor = color;
}

void ParticleGenerator::Draw()
{
    // use additive blending to give it a 'glow' effect
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    this->shader.Use();
    for (Particle particle : this->particles)
    {
        if (particle.Life > 0.0f)
        {
            this->shader.SetVector2f("offset", particle.Position);
            this->shader.SetVector4f("color", particle.Color);
            this->shader.SetFloat("scale", particle.Scale);
            this->texture.Bind();
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    // restore
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init()
{
    unsigned int VBO;
    float        particle_quad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);
    // fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
    glBindVertexArray(0);

    // create default amount of particle instances
    for (unsigned int i = 0; i < this->amount; ++i)
    {
        this->particles.push_back(Particle());
    }
}

// stores the index of the last particle used (for quick access to next dead particle)
unsigned int lastUsedParticle = 0;
unsigned int ParticleGenerator::firstUnusedParticle()
{
    // First: search from last used particle, this will usually return almost instantly
    for (unsigned int i = lastUsedParticle; i < this->amount; ++i)
    {
        if (this->particles[i].Life <= 0.0f)
        {
            lastUsedParticle = i;
            return i;
        }
    }

    // Second: otherwise do a linear search
    for (unsigned int i = 0; i < lastUsedParticle; ++i)
    {
        if (this->particles[i].Life <= 0.0f)
        {
            lastUsedParticle = i;
            return i;
        }
    }

    // Third: all particles are taken, use the first one
    // (note that if it repeatedly hits this case, more particles should be reserved/allocated)
    lastUsedParticle = 0;
    return 0;
}

void ParticleGenerator::respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset)
{
    float random = ((rand() % 100) - 50) / 10.0f;  // [-0.5, 0.5]
    float rColor = 0.3f + (rand() % 100) / 100.0f;
    particle.Position = object.Position + random + offset;
    particle.Color    = glm::vec4(this->particleColor * rColor, 1.0f);
    particle.Scale    = DEFAULT_PARTICLE_SCALE;
    particle.Life     = 1.0f;
    particle.Velocity = object.Velocity * 0.1f;
}

