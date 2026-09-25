#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H
#include "raylib.h"
#include "object.h"
#include "raymath.h"

typedef struct 
{
    Vector2 origin;
    bool isEnabled;
    unsigned short alpha;
    float widthHeight;
    float angle;
    
    float velocity;
} Particle;

typedef struct 
{
    unsigned short particleAmount;
    Object* originObject;
    Vector2 offset;
    Vector2 origin; 
    Particle* particles;
    Sprite* sprite; 
} ParticleHandler;

void initParticleSystem();
ParticleHandler* createParticleHandler(Vector2 origin, Sprite* sprite, unsigned short particleAmount);
ParticleHandler* createParticleHandlerOnObject(Object* object, Vector2 offset, Sprite* sprite, unsigned short particleAmount);
void moveParticleHandlers();

void freeParticles();
#endif