#include "raylib.h"
#include "object.h"
#include "timer.h"
#include "../scripts/pipe_logic.h"
#include "../scripts/game_manager.h"
#include <time.h>
#include "unit_system.h"

int main()
{
    SetRandomSeed(time(NULL));
    start();
    gameStart();
    
    while (!WindowShouldClose()) 
    {        
        update();
        iterateTimers();
        
        BeginDrawing();
            drawSprites();   
            draw();
        EndDrawing();
    }       

    end();
    freeCoreComponents();
    CloseWindow();        

    return 0;
}

