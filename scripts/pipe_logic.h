#ifndef PIPE_LOGIC_H
#define PIPE_LOGIC_H
#include "game_manager.h"

typedef struct 
{
    Object* pipes[2];
    Rectangle pipeCenter;
    float speedX;    
    bool scored;

} PipePair;

extern int score;

void initPipePairs();
void spawnPipePair();
void movePipePairs();
bool checkPipePairCollisions();
int returnPipeAmount();
void freePipes();


#endif