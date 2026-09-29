#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H
#include "raylib.h"
#include "object.h"
#include "timer.h"
#include "raymath.h"

typedef struct 
{
    Vector2 origin;
    Sprite* sprite; 
    bool isEnabled;
    float timeAlive;
    float particleAliveTime;
    float velocity;
} Particle;

typedef struct 
{
    unsigned short particleAmount;
    unsigned short particleActiveAmount;
    Vector2 particleMinMaxSpawnDistanceRange;
    Vector2 particleMinMaxRotationRange;
    Vector2 particleMinMaxSizeRange;

    float particleAliveTime;
    unsigned short currentParticleEmitted;
    Object* originObject;
    Vector2 offset;
    Vector2 origin; 
    Particle** particles;
    Sprite* sprite; 
    Timer* particleSpawnTimer;
    
} ParticleHandler;

void initParticleSystem();
ParticleHandler* createParticleHandler(Vector2 origin, Sprite* sprite);
void configureParticleHandler(ParticleHandler* particleHandler, Vector2 particleMinMaxSpawnDistanceRange, Vector2 particleMinMaxRotationRange, Vector2 particleMinMaxSizeRange, float particleAliveTime, int particlesPerSecond);
void moveParticleHandler(ParticleHandler* particleHandler, Vector2 newPosition);
void moveParticlesRelative(ParticleHandler* particleHandler, Vector2 newPosition);
void emitParticles(ParticleHandler* particleHandler);
int returnParticleAliveAmount(ParticleHandler* particleHandler);
void handleParticles();
void drawParticles();
void freeParticles();

#endif