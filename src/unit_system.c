#include "unit_system.h"
#include "scripts/game_manager.h"

int UNIT_PIXEL_SIZE = 0;

void recalculateUnitSize(int newScreenWidth, int newScreenHeight)
{
    int shortestScreenSide = (newScreenWidth < newScreenHeight) ? newScreenWidth : newScreenHeight;
      
    

    UNIT_PIXEL_SIZE = newUnitSize;
    SCREENWIDTH = newScreenWidth;
    SCREENHEIGHT = newScreenHeight;

}
    
