#ifndef TIMER_H
#define TIMER_H
#include "base.h"

// en ms
typedef int timer;

#define from_ms(ms) (ms)
#define from_s(s)   (s*1000)

#define frequence_s(fps)   (1000/(fps))

#endif