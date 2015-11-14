#include "worker.h"
void *work(void *t)
{
    int i;
    long my_id = (long)t;
    while(not_quit)
    {
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_testcancel();
        sleep_ms(3000*my_id);
        pthread_testcancel();
        printf("Worker %ld, found %d remaining resources. Started. \n",
                my_id, remaining_resources);
        for (i=0; i < WRKR_LIMIT/WRKR_SIZE&&not_quit; i++) {
            pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
            pthread_mutex_lock(&remaining_resources_mutex);


            while(remaining_resources-WRKR_SIZE<0) {
                printf("Worker %ld, found %d remaining resources. Sending  signal.\n ",
                        my_id, remaining_resources);
                pthread_cond_signal(&res_empty);
                //printf("Just sent signal.\n");
                pthread_cond_wait(&resources_available_cv, &remaining_resources_mutex);
            }

            remaining_resources-=WRKR_SIZE;

            // printf("Worker %ld, remaining_resources = %d, unlocking mutex. Worker load %d\n",
            //       my_id, remaining_resources,i);
            pthread_mutex_unlock(&remaining_resources_mutex);
            pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
            pthread_testcancel();
            sleep_ms(2000);
        }
        pthread_setcancelstate(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
        pthread_testcancel();
        printf("Worker %ld full. Load %d\n", my_id,i*WRKR_SIZE);
        sleep_ms(3000*my_id);
        pthread_mutex_lock(&gathered_resources_mutex);
        gathered_resources+=i*WRKR_SIZE;
        printf("Worker %ld unloaded %d resources. Gathered resources now: %d\n", my_id,i*WRKR_SIZE,gathered_resources);
        pthread_mutex_unlock(&gathered_resources_mutex);


    }
    pthread_exit(NULL);

    return NULL;
}
