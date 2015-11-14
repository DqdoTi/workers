#include "game_manager.h"
#define INIT_WRKR_HEALTH 3

int health=INIT_WRKR_HEALTH;
//pthread_t threads[100];
node* workers_ls=NULL;
int num_wrkrs= INIT_NUM_WORKERS;
pthread_attr_t attr;
void createWorker(void);
void wound_worker(int i);
void kill_worker(int i);

void game_manager()
{
    long t1=0,i;




    pthread_mutex_init(&remaining_resources_mutex, NULL);
    pthread_mutex_init(&gathered_resources_mutex, NULL);
    pthread_cond_init (&res_empty, NULL);
    pthread_cond_init (&resources_available_cv, NULL);


    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_t res_watch;
    pthread_create(&res_watch, &attr, watch_resources, (void *)t1);


    for (i = 1; i <= num_wrkrs; i++) {
        pthread_t wrkr_t;

        pthread_create(&wrkr_t, &attr, work, (void *)i);
        worker *wrkr= (worker *) malloc(sizeof(worker));
        wrkr->thread = wrkr_t;
        wrkr->id =i;
        wrkr->health =INIT_WRKR_HEALTH;
        wrkr->x_pos =1;
        wrkr->y_pos =1;
        workers_ls=add_worker(workers_ls,wrkr);
    }
    char input;
    while(not_quit)
    {
        input = getchar();
        if(input=='w'||input=='W')
        {
            createWorker();

        }else if(input=='q'||input=='Q')
        {
            not_quit=0;
            pthread_mutex_lock(&remaining_resources_mutex);
            pthread_cond_signal(&res_empty);
            pthread_mutex_unlock(&remaining_resources_mutex);
        }else if(input=='E'||input=='e')
        {
            wound_worker(num_wrkrs);
        }else if(input=='k'||input=='K')
        {
            kill_worker(num_wrkrs);
        }


    }

    pthread_join(res_watch,NULL);
    for (i = 1; i <= num_wrkrs; i++) {
        //pthread_join(threads[i], NULL);

        pthread_join(get_worker_at(workers_ls,i)->thread,NULL);
    }
    printf ("Created %d workers. Remaining resources = %d. Gathered resources = %d. Done.\n",
            num_wrkrs, remaining_resources,gathered_resources);
    getchar();
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&remaining_resources_mutex);
    pthread_mutex_destroy(&gathered_resources_mutex);
    pthread_cond_destroy(&res_empty);
    pthread_cond_destroy(&resources_available_cv);


}


void createWorker()
{
    pthread_mutex_lock(&gathered_resources_mutex);

    if(gathered_resources-WRKR_COST>=0)
    {
        gathered_resources-=WRKR_COST;
        num_wrkrs++;
        printf("CREATING WORKER NUMBER: %d\n",num_wrkrs);
        sleep_ms(5000);
        printf("CREATING WORKER NUMBER: %d CREATED\n",num_wrkrs);
        //pthread_create(&threads[num_wrkrs], &attr, work, (void *)num_wrkrs);
        pthread_t wrkr_t;
        pthread_create(&wrkr_t, &attr, work, (void *)num_wrkrs);
        worker *wrkr= (worker *) malloc(sizeof(worker));
        wrkr->thread = wrkr_t;
        wrkr->id =num_wrkrs;
        wrkr->health =INIT_WRKR_HEALTH;
        wrkr->x_pos =1;
        wrkr->y_pos =1;
        workers_ls=add_worker(workers_ls,wrkr);

    }else{
        printf("NOT ENOUGH RESOURCES TO CREATE WORKER: %d\n",gathered_resources);

    }
    pthread_mutex_unlock(&gathered_resources_mutex);
}
void wound_worker(int i)
{

    if (num_wrkrs>0)
    {
        printf("attempting to wound worker %d\n",num_wrkrs);
        int wrkr_health=get_worker_at(workers_ls,i)->health;

        if(wrkr_health>1)
        {
            //health--;
            get_worker_at(workers_ls,i)->health=wrkr_health-1;
            printf(" worker %d wounded. remaining health %d\n",num_wrkrs,wrkr_health);
        }else{
            kill_worker(i);
        }
    }else
    {
        printf("No one to kill");
    }
}

void kill_worker(int i)
{
    if (num_wrkrs>0)
    {
        printf("attempting to kill worker %d\n",i);

        int s=  pthread_cancel(get_worker_at(workers_ls,i)->thread);



        // pthread_join(get_worker_at(workers_ls,i)->thread,NULL);
        printf("HAHA killed worker %d\n%d\n",i,s);
        workers_ls=remove_worker_at(workers_ls,i);
        num_wrkrs--;
        //health=INIT_WRKR_HEALTH;
    }else
    {
        printf("No one to kill");
    }
}
