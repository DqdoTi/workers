#include "main.h"




int main(int argc, char *argv[])
{
    game_manager();
printf("End;\n");

    getchar();
    pthread_exit (NULL);

    return 0;
}

