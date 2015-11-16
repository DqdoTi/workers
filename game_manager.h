#ifndef GAME_MANAGER_H_INCLUDED
#define GAME_MANAGER_H_INCLUDED


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "sleep.h"
#include "params.h"
#include "worker.h"
#include "resource_watcher.h"
#include "workers_list.h"
#include "chess_board.h"

extern int remaining_resources ;
extern int gathered_resources ;

extern pthread_mutex_t  remaining_resources_mutex;
extern pthread_mutex_t  gathered_resources_mutex;
extern pthread_cond_t  res_empty;
extern pthread_cond_t  resources_available_cv;
extern char   not_quit;
void game_manager();



#endif // GAME_MANAGER_H_INCLUDED
