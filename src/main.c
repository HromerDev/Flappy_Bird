#include "raylib.h"
#include "object.h"
#include "timer.h"
#include "../scripts/pipe_logic.h"
#include "../scripts/game_manager.h"
#include <time.h>

int main()
{
    srand(time(NULL));
    start();
    
    while (!WindowShouldClose()) 
    {        
        update();
        moveParticleHandlers();

        BeginDrawing();
            
            drawSprites();   
            drawParticles();
            
            draw();
        EndDrawing();
        
        iterateTimers();
    }       
    
    freeSprites();
    freeObjects();
    freeTimers();
    freePipes();
    freeParticles();
    
    end();
    CloseWindow();        

    return 0;
}