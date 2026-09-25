#include "particle_system.h"
#include "dynamic_array.h"
#include "stdlib.h"

dynarray *allParticleHandlers;
dynarray *allParticles;

void initParticleSystem() 
{
    allParticleHandlers = malloc(sizeof(dynarray)); 
    dynarray_init(allParticleHandlers, 1);

    allParticles = malloc(sizeof(dynarray));
    dynarray_init(allParticles, 1);
}

void particleHandlerCore(ParticleHandler* particleHandler, int particleAmount, Sprite* sprite) 
{
    particleHandler->sprite = sprite;
    particleHandler->particleAmount = particleAmount;

    for(int i = 0; i < particleAmount; i++) 
    {        
        Particle* particle = malloc(sizeof(Particle));

        dynarray_push(allParticles, particle);  

        particleHandler->particles = allParticles->items[allParticles->size - 1];
    }

    dynarray_push(allParticleHandlers, particleHandler);    
}

ParticleHandler* createParticleHandler(Vector2 origin, Sprite* sprite, unsigned short particleAmount) 
{
    ParticleHandler* particleHandler = malloc(sizeof(ParticleHandler));
    particleHandler->origin = origin;

    particleHandlerCore(particleHandler, particleAmount, sprite);
    return particleHandler;
}

ParticleHandler* createParticleHandlerOnObject(Object* object, Vector2 offset, Sprite* sprite, unsigned short particleAmount) 
{
    ParticleHandler* particleHandler = malloc(sizeof(ParticleHandler));

    particleHandler->originObject = object;
    particleHandler->offset = offset;

    particleHandler->origin = Vector2Add(object->centerAnchor, offset);

    particleHandlerCore(particleHandler, particleAmount, sprite);
    return particleHandler;
}

void moveParticleHandlers() 
{
    for(int i = 0; i < allParticleHandlers->size; i++) 
    {
        ParticleHandler* temp = allParticleHandlers->items[i];

        if(temp->originObject == NULL)
            continue;

        temp->origin = Vector2Add(temp->originObject->centerAnchor, temp->offset);        
        DrawCircleV(temp->origin, 10, GREEN);
    }
}

void freeParticles()
{
    if (allParticleHandlers != NULL)
    {
        dynarray_free(allParticleHandlers);
        free(allParticleHandlers);
        allParticleHandlers = NULL;
    }

    if (allParticles != NULL)
    {
        dynarray_free(allParticles);
        free(allParticles);
        allParticles = NULL;
    }
}
