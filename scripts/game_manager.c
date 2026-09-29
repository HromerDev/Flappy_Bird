#include "game_manager.h"

bool gameOver = false;
ParticleHandler* particle;
void start() //initializations
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, WINDOWNAME);
    SetTargetFPS(FPS); 
}

void gameStart()
{
    initTextures();
    initTimer();
    initParticleSystem();

    initPlayer(35, 35);
    initPipePairs();
    score = 0;

    particle = createParticleHandler((Vector2){0,0}, createSprite((Rectangle){0,0,1,1}, TEXTURE_PARTICLE, LAYERS_PARTICLE, 0));
    configureParticleHandler(particle, (Vector2){0, 5,}, 
                                        (Vector2){0, 360},
                                        (Vector2){25,45},                                        
                                        0.5, 20);
}


void restart() 
{
    freeCoreComponents();
    gameStart();
}
void update() //input handling, logic
{   
    if(checkPipePairCollisions()) 
    {           
        gameOver = true;

        if(IsKeyPressed(KEY_SPACE)) 
        {
            gameOver = false;
            restart();
            
        }     
        return;
    }

    if(IsKeyDown(KEY_SPACE))
    playerJump();
    else   
        player.holdTimer = 0;

    processPlayerMovement();
    processPlayerAcceleration();
    processPlayerRotation();

    movePipePairs();
    checkPipePairCollisions(); 

    handleParticles();

    moveParticleHandler(particle, player.playerObject->centerAnchor);    
    moveParticlesRelative(particle, (Vector2){-275 * GetFrameTime(), 0});
    
}

void draw() //drawing a frame (primarely for text)
{   
    if(gameOver)
        DrawText("GAME OVER! PRESS SPACE TO GO AGAIN", 10, 10, 30, GOLD);
    else 
        DrawText(TextFormat("%d",score), 10, 10, 100, GOLD);  

    int frameRate = 1 / GetFrameTime();
    Color frameColor = (frameRate > FPS * 0.8) ? GREEN : RED;
    
    DrawText(TextFormat("FPS:%d", frameRate), 1, SCREENHEIGHT - 20, 20, frameColor);
    /**/
    (checkPipePairCollisions()) ? DrawText("COLLIDED", 1, SCREENHEIGHT - 40, 20, BLACK) : DrawText("NOT COLLIDED", 0, SCREENHEIGHT - 40, 20, BLACK);
    DrawText(TextFormat("Pipes: %d", returnPipeAmount()), 1, SCREENHEIGHT - 60, 20, BLACK);    
    DrawText(TextFormat("X:%.2f Y:%.2f", player.playerObject->topLeftAnchor.x, player.playerObject->topLeftAnchor.y), 1, SCREENHEIGHT - 80, 20, GOLD);
    DrawText(TextFormat("Objects: %d", returnObjectAmount()), 1, SCREENHEIGHT - 100, 20, BLACK);
    DrawText(TextFormat("Acceleration: %.2f", player.acceleration), 1, SCREENHEIGHT - 120, 20, BLACK);
    DrawText(TextFormat("Angle: %.2f", player.playerObject->sprite->angle), 1, SCREENHEIGHT - 140, 20, BLACK);
    (layersSortedCorrectly()) ? DrawText("Layers sorted correctly", 1, SCREENHEIGHT - 160, 20, GREEN) : DrawText("Layers sorted wrongly", 1, SCREENHEIGHT - 160, 20, RED);
    DrawText(TextFormat("Particles Active: %d/%d", returnParticleAliveAmount(particle), particle->particleAmount), 1, SCREENHEIGHT - 180, 20, BLACK);
}


void end() 
{ 
    
}

void freeCoreComponents() 
{
    freeSprites();
    freeObjects();
    freeTimers();
    freePipes();
    freeParticles();
}