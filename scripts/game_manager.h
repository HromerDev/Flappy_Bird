#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "raylib.h"
#include "../src/object.h"
#include "../src/timer.h"
#include "../src/dynamic_array.h"
#include "../src/particle_system.h"

#include "player_logic.h"
#include "pipe_logic.h"


#define SCREENWIDTH 800
#define SCREENHEIGHT 600
#define FPS 0
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
