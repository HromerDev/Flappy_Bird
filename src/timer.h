#ifndef TIMER_H
#define TIMER_H

#include "stdlib.h"
#include "raylib.h"

typedef struct  
{
    bool isActive;
    double timeElapsed;
    double timePeriod;
} Timer;

void initTimer();
Timer* createTimer(double timePeriod);
void destroyTimer(Timer *timer);
bool isTimerReady(Timer *timer);
double returnTimer(Timer timer);

void iterateTimers();

void modifyTimer(Timer *timer, double newPeriod);
void toggleTimer(Timer *timer);
void resetTimer(Timer *timer);

void freeTimers();

#endif