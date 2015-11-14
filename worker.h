#ifndef WORKER_H
#define WORKER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "sleep.h"
#include "params.h"


typedef struct{
    pthread_t thread;
    int id;
    int health;
    int x_pos;
    int y_pos;
} worker;

extern int remaining_resources ;
extern int gathered_resources ;

extern pthread_mutex_t  remaining_resources_mutex;
extern pthread_mutex_t  gathered_resources_mutex;
extern pthread_cond_t  res_empty;
extern pthread_cond_t  resources_available_cv;
extern char   not_quit;
void *work(void *t);


#endif // WORKER_H
