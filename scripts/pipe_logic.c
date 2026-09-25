#include "pipe_logic.h"

#include <stdio.h>

float pipeSpeed = 275;
int pipeWidth = 100;
int pipePairMinGap = 150;
int pipePairMaxGap = 250;
int pipeMinGap = 110;
int pipeMaxGap = 170;
int score = 0;

dynarray *allPipePairs;
void initPipePairs() 
{   
    allPipePairs = malloc(sizeof(dynarray)); 
    dynarray_init(allPipePairs, 1);

    for (int i = 0; i < 5; i++)
        spawnPipePair();
}

void spawnPipePair() 
{
    PipePair *pipePair = malloc(sizeof(PipePair));

    pipePair->scored = false;

    int currentGap = (rand() % (pipeMaxGap - pipeMinGap)) + pipeMinGap;

    Rectangle pipe0RECT = {SCREENWIDTH,(rand() % (SCREENHEIGHT - currentGap)) - SCREENHEIGHT, pipeWidth, SCREENHEIGHT};

    pipePair->pipes[0] = createObject(pipe0RECT, createSprite(pipe0RECT, TEXTURE_PIPE1, LAYERS_PIPES, 0), 0);

    if(allPipePairs->size > 0) 
    {
        PipePair *lastPipe = allPipePairs->items[allPipePairs->size - 1];

        int pairGap = (rand() % (pipePairMaxGap - pipePairMinGap)) + pipePairMinGap;
        
        float x = lastPipe->pipes[0]->topRightAnchor.x + pairGap;

        moveObject( pipePair->pipes[0], x, pipePair->pipes[0]->collider.y);
    }

    Rectangle pipe1RECT = (Rectangle) {pipePair->pipes[0]->collider.x,pipePair->pipes[0]->collider.y + pipePair->pipes[0]->collider.height + currentGap, pipeWidth, SCREENHEIGHT};

    pipePair->pipes[1] = createObject(pipe1RECT, createSprite(pipe1RECT, TEXTURE_PIPE2, LAYERS_PIPES, 0), 0);

    pipePair->pipeCenter = (Rectangle) 
    {
        .x = pipePair->pipes[0]->collider.x,
        .y = pipePair->pipes[0]->collider.y + pipePair->pipes[0]->collider.height,
        .width = pipeWidth,
        .height = currentGap,
    };

    dynarray_push(allPipePairs, pipePair);
}

void movePipePairs() 
{
    if (allPipePairs->size == 0)
        return;
    
    for(int i = 0; i < allPipePairs->size; i++) 
    {
        PipePair* temp = allPipePairs->items[i];
        
        for(int j = 0; j < 2; j++) 
            moveObjectRelative(temp->pipes[j], -pipeSpeed * GetFrameTime(), 0);
        
        temp->pipeCenter.x -= pipeSpeed * GetFrameTime();
        
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
                return true;  

        if(CheckCollisionRecs(player.playerObject->collider, temp->pipeCenter)) 
        {
            if(!temp->scored) 
            {
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