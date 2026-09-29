#include "timer.h"
#include "dynamic_array.h"

dynarray *allTimers;

void initTimer() 
{
    allTimers = malloc(sizeof(dynarray)); 
    dynarray_init(allTimers, 1);
}

Timer* createTimer(double timePeriod) 
{
    Timer *timer = malloc(sizeof(Timer));

    *timer = (Timer)
    {
        .isActive = false,
        .timeElapsed = 0,
        .timePeriod = timePeriod,
    };

    dynarray_push(allTimers, timer);

    return timer;
} 

void destroyTimer(Timer *timer) 
{
    dynarray_remove(allTimers, timer);
}

bool isTimerReady(Timer *timer) 
{
    if(timer->timeElapsed < timer->timePeriod)
        return false;
    
    timer->timeElapsed = 0;
    return true;
}

double returnTimer(Timer timer) 
{
    return timer.timeElapsed / timer.timePeriod;
}

void iterateTimers() 
{
    for(int i = 0; i < allTimers->size; i++) 
    {
        Timer *temp = allTimers->items[i];

        if(!temp->isActive)
            continue;
        
        temp->timeElapsed += GetFrameTime();
    }
}

void modifyTimer(Timer *timer, double newPeriod) 
{
    double oldTimerElapsed = returnTimer(*timer);

    timer->timePeriod = newPeriod;
    timer->timeElapsed = newPeriod * oldTimerElapsed;
}

void toggleTimer(Timer *timer) 
{
    timer->isActive = !timer->isActive;
}

void resetTimer(Timer *timer) 
{
    timer->timeElapsed = 0;
}

void freeTimers() 
{
    dynarray_free(allTimers);
    free(allTimers);
    allTimers = NULL;
}