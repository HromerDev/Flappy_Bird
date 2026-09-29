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
    gameStart();
    
    while (!WindowShouldClose()) 
    {        
        update();

        BeginDrawing();
            
            drawSprites();   
            //drawParticles();
            
            draw();
        EndDrawing();
        
        iterateTimers();
    }       
        
    end();
    freeCoreComponents();
    CloseWindow();        

    return 0;
}

