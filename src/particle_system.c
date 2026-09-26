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

void particleHandlerCore(ParticleHandler* particleHandler, Sprite* sprite) 
{
    particleHandler->sprite = sprite;
    particleHandler->currentParticleEmitted = 0;

    dynarray_push(allParticleHandlers, particleHandler);    
}

ParticleHandler* createParticleHandler(Vector2 origin, Sprite* sprite) 
{
    ParticleHandler* particleHandler = malloc(sizeof(ParticleHandler));
    particleHandler->origin = origin;
    particleHandler->originObject = NULL;

    particleHandlerCore(particleHandler, sprite);
    return particleHandler;
}

ParticleHandler* createParticleHandlerOnObject(Object* object, Vector2 offset, Sprite* sprite) 
{
    ParticleHandler* particleHandler = malloc(sizeof(ParticleHandler));

    particleHandler->originObject = object;
    particleHandler->offset = offset;

    particleHandler->origin = Vector2Add(object->centerAnchor, offset);

    particleHandlerCore(particleHandler, sprite);
    return particleHandler;
}

void configureParticleHandler(ParticleHandler* particleHandler, Vector2 particleMinMaxSpawnDistanceRange, Vector2 particleMinMaxRotationRange, Vector2 particleMinMaxSizeRange, unsigned short particleAmount, float particleAliveTime, float particleDelay)
{
    particleHandler->particleMinMaxSpawnDistanceRange = particleMinMaxSpawnDistanceRange;
    particleHandler->particleMinMaxRotationRange = particleMinMaxRotationRange;
    particleHandler->particleMinMaxSizeRange = particleMinMaxSizeRange;
    particleHandler->particleAliveTime = particleAliveTime;
    particleHandler->particleSpawnTimer = createTimer(particleDelay);
    particleHandler->particleSpawnTimer->isActive = true;
    particleHandler->particleAmount = particleAmount;

    particleHandler->particles = malloc(sizeof(Particle*) * particleAmount);

    for(int i = 0; i < particleAmount; i++) 
    {        
        Particle* particle = malloc(sizeof(Particle));
        particle->particleAliveTime = particleAliveTime;
        particle->isEnabled = false;

        dynarray_push(allParticles, particle);  

        particleHandler->particles[i] = allParticles->items[allParticles->size - 1];
    }
}

void moveParticleHandlers() 
{
    for(int i = 0; i < allParticleHandlers->size; i++) 
    {
        ParticleHandler* temp = allParticleHandlers->items[i];

        if(temp->originObject == NULL)
            continue;

        temp->origin = Vector2Add(temp->originObject->centerAnchor, temp->offset);     
        //DrawCircleV(temp->origin, 10, GREEN);   
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

        temp->opacity = 255 * (1.0f - temp->timeAlive / temp->particleAliveTime);
        
    }
}

void emitParticles() 
{
    for(int i = 0; i < allParticleHandlers->size; i++) 
    {
        ParticleHandler *temp = allParticleHandlers->items[i];

        if(isTimerReady(temp->particleSpawnTimer)) 
        {
            int randomParticleDistanceX = GetRandomValue((int)temp->particleMinMaxSpawnDistanceRange.x, (int)temp->particleMinMaxSpawnDistanceRange.y);            
            int randomParticleDistanceY = GetRandomValue((int)temp->particleMinMaxSpawnDistanceRange.x, (int)temp->particleMinMaxSpawnDistanceRange.y);

            temp->sprite->opacity = temp->particles[temp->currentParticleEmitted]->opacity;

            temp->particles[temp->currentParticleEmitted]->origin = Vector2Add(temp->origin, (Vector2){randomParticleDistanceX, randomParticleDistanceY});
            temp->particles[temp->currentParticleEmitted]->angle = GetRandomValue(temp->particleMinMaxRotationRange.x, temp->particleMinMaxRotationRange.y);
            temp->particles[temp->currentParticleEmitted]->widthHeight = GetRandomValue(temp->particleMinMaxSizeRange.x, temp->particleMinMaxSizeRange.y);
            temp->particles[temp->currentParticleEmitted]->timeAlive = 0;
            temp->particles[temp->currentParticleEmitted]->isEnabled = true;
            temp->currentParticleEmitted++;

            temp->currentParticleEmitted %= temp->particleAmount;

            allParticleHandlers->items[i] = temp;
        }
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
            
            DrawTexturePro(textureArray[temp->sprite->texture], (Rectangle){0,0, textureArray[temp->sprite->texture].width, textureArray[temp->sprite->texture].height}, (Rectangle) {tempParticle->origin.x , tempParticle->origin.y, tempParticle->widthHeight, tempParticle->widthHeight}, (Vector2){tempParticle->widthHeight / 2, tempParticle->widthHeight / 2}, tempParticle->angle, (Color) {255,255,255,tempParticle->opacity});
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


