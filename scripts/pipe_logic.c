#include "pipe_logic.h"
#include "player_logic.h"
#include "../src/unit_system.h"
#include "raylib.h"
#include "../src/object.h"
#include "game_manager.h"
#include <stdio.h>

float pipeSpeed = 33;
int pipeWidth = 13;
int pipePairMinGap = 12;
int pipePairMaxGap = 25;
int pipeMinGap = 14;
int pipeMaxGap = 21;
int score = 0;

dynarray *allPipePairs;
void initPipePairs() 
{   
    allPipePairs = malloc(sizeof(dynarray)); 
    dynarray_init(allPipePairs, 1);

    for (int i = 0; i < 10; i++)
        spawnPipePair();
}

void spawnPipePair() 
{
    PipePair *pipePair = malloc(sizeof(PipePair));

    pipePair->scored = false;
    int currentGap = GetRandomValue(pipeMinGap, pipeMaxGap);
    //int currentGap = (rand() % (pipeMaxGap - pipeMinGap)) + pipeMinGap;
    Rectangle pipe0RECT = {SCREENWIDTH / UNIT_PIXEL_SIZE,GetRandomValue(0, (int)(SCREENHEIGHT / UNIT_PIXEL_SIZE) - currentGap) - SCREENHEIGHT / UNIT_PIXEL_SIZE, pipeWidth, SCREENHEIGHT / UNIT_PIXEL_SIZE};
   
    if(allPipePairs->size > 0) 
    {
        PipePair *lastPipe = allPipePairs->items[0];
        
        for (int i = 1; i < allPipePairs->size; i++)
        {
            PipePair *temp = allPipePairs->items[i];

            if (temp->pipes[0]->collider.x > lastPipe->pipes[0]->collider.x)        
                lastPipe = temp; 
        }
        
        pipe0RECT.x = lastPipe->pipes[0]->collider.x / UNIT_PIXEL_SIZE + lastPipe->pipes[0]->collider.width / UNIT_PIXEL_SIZE + GetRandomValue(pipePairMinGap, pipePairMaxGap - 1);
    }

    pipePair->pipes[0] = createObject(pipe0RECT, createSprite(pipe0RECT, TEXTURE_PIPE1, LAYERS_PIPES, 0), 0);
    
    Rectangle pipe1RECT = (Rectangle) {pipePair->pipes[0]->originalCollider.x,pipePair->pipes[0]->originalCollider.y + SCREENHEIGHT / UNIT_PIXEL_SIZE + currentGap, pipeWidth, SCREENHEIGHT / UNIT_PIXEL_SIZE};

    pipePair->pipes[1] = createObject(pipe1RECT, createSprite(pipe1RECT, TEXTURE_PIPE2, LAYERS_PIPES, 0), 0);

    pipePair->pipeCenter = (Rectangle) 
    {
        .x = pipePair->pipes[0]->collider.x,
        .y = pipePair->pipes[0]->collider.y + pipePair->pipes[0]->collider.height,
        .width = pipeWidth * UNIT_PIXEL_SIZE,
        .height = currentGap * UNIT_PIXEL_SIZE,
    };

    dynarray_push(allPipePairs, pipePair);
}

    void movePipePairs() 
{
    if (allPipePairs->size == 0)
        return;
    
    for (int i = allPipePairs->size - 1; i >= 0; i--) 
    {
        PipePair* temp = allPipePairs->items[i];
        
        for(int j = 0; j < 2; j++) 
            moveObjectRelative(temp->pipes[j], -pipeSpeed * GetFrameTime(), 0);
        
        temp->pipeCenter.x -= pipeSpeed * UNIT_PIXEL_SIZE * GetFrameTime();
        
        if(temp->pipes[0]->topRightAnchor.x < 0) 
        {
            destroyObject(temp->pipes[0]);
            destroyObject(temp->pipes[1]);

            dynarray_remove(allPipePairs, temp);
            
            spawnPipePair();
        }          
    }
}

bool checkPipePairCollisions() 
{
    if(allPipePairs->size == 0) 
        return false;

    for(int i = 0; i < allPipePairs->size; i++) 
    {
        PipePair* temp = allPipePairs->items[i];
  
        for(int j = 0; j < 2; j++)              
            if(CheckCollisionRecs(player.playerObject->collider, temp->pipes[j]->collider))  
            {   
                if(!gameOver) 
                {
                    PlaySound(sounds[SOUND_DEATH]);
                    gameOver = true;
                }

                return true;  
            }

        if(CheckCollisionRecs(player.playerObject->collider, temp->pipeCenter)) 
        {
            if(!temp->scored) 
            {
                PlaySound(sounds[SOUND_SCORE]);
                temp->scored = true;
                score++;            
            }
        }
    }
    return false;
}

int returnPipeAmount() 
{
    return allPipePairs->size;
}

void freePipes() 
{
    dynarray_free(allPipePairs);
    free(allPipePairs);
    allPipePairs = NULL;
}
