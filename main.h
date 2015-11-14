#ifndef MAIN_H
#define MAIN_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "game_manager.h"




int     remaining_resources = RESOURCES_INIT_SIZE;
int     gathered_resources = PLAYER_RESOURCES_INIT_SIZE;

pthread_mutex_t remaining_resources_mutex;
pthread_mutex_t gathered_resources_mutex;
pthread_cond_t res_empty;
pthread_cond_t resources_available_cv;
char  not_quit=1;



#endif // MAIN_H
