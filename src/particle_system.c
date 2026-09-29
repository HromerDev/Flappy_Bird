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

ParticleHandler* createParticleHandler(Vector2 origin, Sprite* sprite) 
{
    ParticleHandler* particleHandler = malloc(sizeof(ParticleHandler));
    particleHandler->origin = origin;
    particleHandler->originObject = NULL;

    particleHandler->sprite = sprite;
    particleHandler->currentParticleEmitted = 0;

    dynarray_push(allParticleHandlers, particleHandler);

    return particleHandler;
}

void configureParticleHandler(ParticleHandler* particleHandler, Vector2 particleMinMaxSpawnDistanceRange, Vector2 particleMinMaxRotationRange, Vector2 particleMinMaxSizeRange, float particleAliveTime, int particlesPerSecond)
{
    particleHandler->particleMinMaxSpawnDistanceRange = particleMinMaxSpawnDistanceRange;
    particleHandler->particleMinMaxRotationRange = particleMinMaxRotationRange;
    particleHandler->particleMinMaxSizeRange = particleMinMaxSizeRange;
    particleHandler->particleAliveTime = particleAliveTime;
    particleHandler->particleSpawnTimer = createTimer(1.0 / particlesPerSecond);
    particleHandler->particleSpawnTimer->isActive = true;
    particleHandler->particleAmount = particlesPerSecond * particleAliveTime;

    particleHandler->particles = malloc(sizeof(Particle*) * particleHandler->particleAmount);

    for(int i = 0; i < particleHandler->particleAmount; i++) 
    {        
        Particle* particle = malloc(sizeof(Particle));
        particle->particleAliveTime = particleAliveTime;
        particle->isEnabled = false;

        particle->sprite = createSprite((Rectangle) {0,0,0,0}, particleHandler->sprite->texture, particleHandler->sprite->layer, 0); 

        dynarray_push(allParticles, particle);  

        particleHandler->particles[i] = allParticles->items[allParticles->size - 1];
    }
}

void moveParticleHandler(ParticleHandler* particleHandler, Vector2 newPosition) 
{
    particleHandler->origin = newPosition;
    DrawCircleV(particleHandler->origin, 10, GREEN);
}

void moveParticlesRelative(ParticleHandler* particleHandler, Vector2 newPosition) 
{
    for (size_t i = 0; i < particleHandler->particleAmount; i++)
    {        
        if(particleHandler->particles[i]->isEnabled)  
        {
            particleHandler->particles[i]->origin = Vector2Add(particleHandler->particles[i]->origin, newPosition);
            particleHandler->particles[i]->sprite->centerAnchor = particleHandler->particles[i]->origin;
        }
              
    }
    
}

void handleParticles() 
{
    float delta = GetFrameTime();

    for(int i = 0; i < allParticles->size; i++) 
    {
        Particle* temp = allParticles->items[i];
        
        if(!temp->isEnabled)
            continue;

        temp->timeAlive += delta;

        if(temp->timeAlive > temp->particleAliveTime)
            temp->isEnabled = false;

        temp->sprite->opacity = 255 * (1.0f - temp->timeAlive / temp->particleAliveTime);
        
    }
}

int returnParticleAliveAmount(ParticleHandler* particleHandler) 
{
    short sum = 0;
    for (size_t i = 0; i < particleHandler->particleAmount; i++)
    {
        if(particleHandler->particles[i]->isEnabled)
            sum++;
    }
    
    particleHandler->particleActiveAmount = sum;
    return particleHandler->particleActiveAmount;
}

void emitParticles(ParticleHandler* particleHandler) 
{
    if(isTimerReady(particleHandler->particleSpawnTimer)) 
    {
        int randomParticleDistanceX = GetRandomValue((int)particleHandler->particleMinMaxSpawnDistanceRange.x, (int)particleHandler->particleMinMaxSpawnDistanceRange.y);            
        int randomParticleDistanceY = GetRandomValue((int)particleHandler->particleMinMaxSpawnDistanceRange.x, (int)particleHandler->particleMinMaxSpawnDistanceRange.y);

        //particleHandler->sprite->opacity = particleHandler->particles[particleHandler->currentParticleEmitted]->opacity;

        particleHandler->particles[particleHandler->currentParticleEmitted]->origin = Vector2Add(particleHandler->origin, (Vector2){randomParticleDistanceX, randomParticleDistanceY});
        particleHandler->particles[particleHandler->currentParticleEmitted]->sprite->angle = GetRandomValue(particleHandler->particleMinMaxRotationRange.x, particleHandler->particleMinMaxRotationRange.y);
        particleHandler->particles[particleHandler->currentParticleEmitted]->sprite->textureArea.width = GetRandomValue(particleHandler->particleMinMaxSizeRange.x, particleHandler->particleMinMaxSizeRange.y);
        particleHandler->particles[particleHandler->currentParticleEmitted]->sprite->textureArea.height = particleHandler->particles[particleHandler->currentParticleEmitted]->sprite->textureArea.width;
        particleHandler->particles[particleHandler->currentParticleEmitted]->timeAlive = 0;
        particleHandler->particles[particleHandler->currentParticleEmitted]->isEnabled = true;
        particleHandler->currentParticleEmitted++;

        particleHandler->currentParticleEmitted %= particleHandler->particleAmount;

        //allParticleHandlers->items[i] = temp;
        }

}

void drawParticles() 
{
    for(int i = 0; i < allParticleHandlers->size; i++) 
    {
        ParticleHandler* temp = allParticleHandlers->items[i];

        for(int j = 0; j < temp->particleAmount; j++) 
        {
            Particle* tempParticle = temp->particles[j];

            if(!temp->particles[j]->isEnabled)
                continue;;
            
            //DrawTexturePro(textureArray[temp->sprite->texture], (Rectangle){0,0, textureArray[temp->sprite->texture].width, textureArray[temp->sprite->texture].height}, (Rectangle) {tempParticle->origin.x , tempParticle->origin.y, tempParticle->widthHeight, tempParticle->widthHeight}, (Vector2){tempParticle->widthHeight / 2, tempParticle->widthHeight / 2}, tempParticle->angle, (Color) {255,255,255,tempParticle->opacity});
        }
    }
}


void freeParticles()
{
    if (allParticleHandlers != NULL)
    {
        for (int i = 0; i < allParticleHandlers->size; i++)
        {
            ParticleHandler* handler = allParticleHandlers->items[i];

            free(handler->particles);
        }

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


