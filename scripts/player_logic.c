#include "player_logic.h"
#include "../src/unit_system.h"
#include "../src/object.h"
#include "raylib.h"
Player player;


void initPlayer(short w, short h)
{
    player.playerObject = createObject((Rectangle) {0, 0, (float)(float)w /4, (float)h /4}, createSprite((Rectangle) {0, 0, w, h}, TEXTURE_PLAYER, LAYERS_PLAYER, 0), 0);
    player.holdTimer = 0;
    moveObject(player.playerObject, 12, ((float)SCREENHEIGHT / UNIT_PIXEL_SIZE - 6) / 2);
}

void processPlayerMovement() 
{
    moveObjectRelative(player.playerObject, 0, player.acceleration * GetFrameTime());
}

void processPlayerRotation() 
{
    if(player.acceleration > 1)
        player.playerObject->sprite->angle += 360 * GetFrameTime();
    else if(player.acceleration < 0)
        player.playerObject->sprite->angle -= 360 *GetFrameTime();

    if(player.playerObject->sprite->angle > 90)
        player.playerObject->sprite->angle = 90;
    else if(player.playerObject->sprite->angle < -45)
        player.playerObject->sprite->angle = -45;
}

void processPlayerAcceleration() 
{
    player.acceleration += 145 * GetFrameTime();

    if(player.playerObject->collider.y > SCREENHEIGHT - player.playerObject->collider.height) 
    {
        moveObject(player.playerObject, player.playerObject->collider.x / UNIT_PIXEL_SIZE, (SCREENHEIGHT - player.playerObject->collider.height) / UNIT_PIXEL_SIZE);
        player.acceleration = 0;
    }       
}

void playerJump() 
{
    player.holdTimer -= 55 * GetFrameTime();    
    if(player.playerObject->topLeftAnchor.y > 0)
        player.acceleration = -36 + player.holdTimer;
    else
        player.acceleration = 0;
    emitParticles(particle);
}

void playerForceFall() 
{
    player.holdTimerDrop = 100 * GetFrameTime();    
    if(player.playerObject->topLeftAnchor.y > 0)
        player.acceleration += player.holdTimerDrop ;
    else
        player.acceleration = 0;

    emitParticles(particle);
}
