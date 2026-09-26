#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H
#include "raylib.h"
#include "object.h"
#include "timer.h"
#include "raymath.h"

typedef struct 
{
    Vector2 origin;
    bool isEnabled;
    float widthHeight;
    float angle;
    float opacity;
    float timeAlive;
    float particleAliveTime;
    float velocity;
} Particle;

typedef struct 
{
    unsigned short particleAmount;
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
ParticleHandler* createParticleHandlerOnObject(Object* object, Vector2 offset, Sprite* sprite);
void configureParticleHandler(ParticleHandler* particleHandler, Vector2 particleMinMaxSpawnDistanceRange, Vector2 particleMinMaxRotationRange, Vector2 particleMinMaxSizeRange, unsigned short particleAmount, float particleAliveTime, float particleDelay);
void moveParticleHandlers();
void emitParticles();
void handleParticles();
void drawParticles();
void freeParticles();

#endif