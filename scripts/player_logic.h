#ifndef PLAYER_LOGIC_H
#define PLAYER_LOGIC_H
#include "game_manager.h"

typedef struct 
{
    float acceleration;
    short speed;
    Object* playerObject;
    float holdTimer;

} Player;

extern Player player;

void initPlayer(short w, short h);
void processPlayerMovement();
void processPlayerRotation();
void processPlayerAcceleration();
void playerJump();
void returnPlayer(Player *playerInfo);

#endif
