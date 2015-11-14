#ifndef SLEEP_H
#define SLEEP_H

#ifdef WIN32
#include <windows.h>
//#elif _POSIX_C_SOURCE >= 199309L
//#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds);

#endif // SLEEP_H_INCLUDED
