#include "unit_system.h"
#include "object.h"
#include "../scripts/game_manager.h"
#include "raylib.h"

double UNIT_PIXEL_SIZE = 0;
int scaler = 60;

void recalculateUnitSize(int newScreenWidth, int newScreenHeight)
{
    double shortestScreenSide = (newScreenWidth < newScreenHeight) ? newScreenWidth : newScreenHeight;
    //double shortestScreenSide = newScreenHeight;
    double newUnitSize = shortestScreenSide / scaler;
    SCREENWIDTH = newScreenWidth;
    SCREENHEIGHT = newScreenHeight;
    UNIT_PIXEL_SIZE = newUnitSize;
    
    //for(size_t i = 0; i < scaler; i++)
    //{
    //   DrawRectangleLines(SCREENWIDTH - UNIT_PIXEL_SIZE * 2, i * UNIT_PIXEL_SIZE, UNIT_PIXEL_SIZE, UNIT_PIXEL_SIZE, GREEN);
    //}

    SetWindowSize(SCREENWIDTH, SCREENHEIGHT);
    recalculateAllUnits();
}

