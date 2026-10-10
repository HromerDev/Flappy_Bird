#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "raylib.h"
#include "../src/object.h"
#include "../src/timer.h"
#include "../src/dynamic_array.h"
#include "../src/particle_system.h"

extern int SCREENWIDTH;
extern int SCREENHEIGHT;

extern int FPS;
#define WINDOWNAME "FLAPPY BIRD (DEMO)"

extern ParticleHandler* particle;

void start();
void gameStart();
void restart();
void update();
void draw();
void end();
void freeCoreComponents();

#endif
