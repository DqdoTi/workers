#ifndef RESOURCE_WATCHER_H
#define RESOURCE_WATCHER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "sleep.h"
#include "params.h"

extern int remaining_resources ;
extern int gathered_resources ;

extern pthread_mutex_t  remaining_resources_mutex;
extern pthread_mutex_t  gathered_resources_mutex;
extern pthread_cond_t  res_empty;
extern pthread_cond_t  resources_available_cv;
extern char   not_quit;
void *watch_resources(void *t);

#endif // RESOURCE_WATCHER_H
