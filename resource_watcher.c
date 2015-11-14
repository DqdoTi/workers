#include "resource_watcher.h"


void *watch_resources(void *t)
{
  long my_id = (long)t;

  printf("Starting watch_count(): thread %ld\n", my_id);

while(not_quit)
{


    pthread_mutex_lock(&remaining_resources_mutex);
    printf("watch_resources(): thread %ld Remaining resources= %d. Going into wait...\n", my_id,remaining_resources);
    while((not_quit && remaining_resources-WRKR_SIZE>0))
        pthread_cond_wait(&res_empty, &remaining_resources_mutex);

    if(not_quit)
    {
        printf("watch_resources(): thread %ld Condition signal received. Remaining resources= %d\n", my_id,remaining_resources);
        printf("watch_resources(): thread %ld Updating the amount of remaining resources...\n", my_id);
        remaining_resources += RESOURCES_RENEW_SIZE;
        printf("watch_resources(): thread %ld Remaining resources now = %d.\n", my_id, remaining_resources);
        pthread_cond_broadcast(&resources_available_cv);
    }
    pthread_mutex_unlock(&remaining_resources_mutex);

}
  pthread_exit(NULL);

  return NULL;
}
