#include "player_logic.h"

Player player;


void initPlayer(short w, short h)
{
    player.playerObject = createObject((Rectangle) {0, 0, w /4, h /4}, createSprite((Rectangle) {0, 0, w, h}, TEXTURE_PLAYER, LAYERS_PLAYER, 0), 0);
    player.holdTimer = 0;
    moveObject(player.playerObject, 100, SCREENHEIGHT / 2 - 25);
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
    player.acceleration += 1200 * GetFrameTime();

    if(player.playerObject->collider.y > SCREENHEIGHT - player.playerObject->collider.height) 
    {
        moveObject(player.playerObject, player.playerObject->collider.x, SCREENHEIGHT - player.playerObject->collider.height);
        player.acceleration = 0;
    }       
}

void playerJump() 
{
    player.holdTimer -= 400 * GetFrameTime();    
    if(player.playerObject->topLeftAnchor.y > 0)
        player.acceleration = -300 + player.holdTimer;
    else
        player.acceleration = 0;

    emitParticles(particle);
}
