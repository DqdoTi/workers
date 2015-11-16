#include "chess_board.h"

SDL_Window *window;
SDL_Renderer *renderer;


//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* Wrkr_srfc = NULL;
SDL_Texture* wrkr_Tx;
SDL_Texture* res_Tx;
int done;
int xpos=2,ypos=2;


int FPS = 50;    // Assign a FPS
int NextTick , interval ;

// Initialize FPS_Fn( )
void FPS_Initial(void) {
    NextTick = 0 ;
    interval = 1 * 1000 / FPS ;
    return;
}

// Frame Per Second Function  , put this in a loop
void FPS_Fn(void) {
    if ( NextTick > SDL_GetTicks( ) ) SDL_Delay( NextTick - SDL_GetTicks( ) );
    NextTick = SDL_GetTicks( ) + interval ;
    return;
}





void DrawChessBoard(SDL_Renderer * renderer)
{
    int row = 0,column = 0,x = 0;
    SDL_Rect rect, darea;
    int loadDone=1;

    /* Get the Size of drawing surface */
    SDL_RenderGetViewport(renderer, &darea);
    loadDone=loadMedia("bob.bmp");
    wrkr_Tx= SDL_CreateTextureFromSurface(renderer, Wrkr_srfc);


    for( ; row < 8; row++)
    {
        //  column = row%2;
        // x = column;
        // for( ; column < 4+(row%2); column++)
        for(column=0 ; column < 8; column++)
        {

            //sleep_ms(100);
            rect.w = darea.w/8;
            rect.h = darea.h/8;
            rect.x = column * rect.w;
            rect.y = row * rect.h;
            // x = x + 2;
            //  printf( "row= %d column= %d\n",row,column );
            if(row==ypos && column==xpos)
            {
               // printf( "ypos= %d xpos= %d\n",ypos,xpos );
                if(!loadDone)
                {
                    printf( "Failed to load media!\n" );
                }
                else
                {
                    printf( "ypos= %d xpos= %d\n",ypos,xpos );
                    //Apply the image
                    //SDL_BlitSurface( gHelloWorld, NULL,gScreenSurface , &rect );
                    SDL_RenderCopy(renderer, wrkr_Tx, NULL, &rect);

                    //Update the surface
                    SDL_UpdateWindowSurface( window );


                }

            }
            else
            {

                if(((row+1)+(column+1))%2==0)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
                    SDL_RenderFillRect(renderer, &rect);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }
}

void loop()
{
    SDL_StartTextInput();
   // sleep_ms(100);
    ypos= (ypos<7)?(ypos+1):0;
    xpos= (xpos<7)?(xpos+2):0;

    SDL_Event event;

    SDL_PumpEvents();
     SDL_WaitEvent(&event);
     while( SDL_PollEvent( &event ) ){
         /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
         switch( event.type ){
           case SDL_KEYDOWN:
             printf( "Key press detected\n" );
             break;

           case SDL_KEYUP:
             printf( "Key release detected\n" );
             break;

           default:
             break;
         }
     }

    while (SDL_PollEvent(&event)!=0) {
        printf("event!\n");


        switch( event.type ){
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym ){
            case SDLK_UP:
                ypos= (ypos>0)?(ypos-1):0;
                break;
            case SDLK_DOWN:
                ypos= (ypos<7)?(ypos+1):8;
                break;
            case SDLK_LEFT:
                xpos= (xpos>0)?(xpos-1):0;
                break;
            case SDLK_RIGHT:
                xpos= (xpos<7)?(xpos+1):8;
                break;
            case SDLK_ESCAPE:
                done = 1;

                break;
            default:
                break;
            } // switch( event.key.keysym.sym ){ END
            break; // case SDL_KEYDOWN: END
            case SDL_QUIT:
                done = 1;
                break;
            default:
                break;
        } // switch( event.type ){ END


    }
     SDL_StopTextInput();

    DrawChessBoard(renderer);

    /* Got everything on rendering surface,
	   now Update the drawing image on window screen */
    SDL_UpdateWindowSurface(window);

    //SDL_Delay(1000);
}
void* chess_board_t(void* arg)
{
    chess_board(NULL);
    pthread_exit(NULL);
    return NULL;
}

void* chess_board(void* arg)
{
    SDL_Surface *surface;

    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    /* Initialize SDL */
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
        return (void *) 1;
    }


    /* Create window and renderer for given surface */
    window = SDL_CreateWindow("WORKERS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    if(!window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n",SDL_GetError());
        return (void *) 1;
    }
    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateSoftwareRenderer(surface);
    if(!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n",SDL_GetError());
        return (void *)1;
    }

    /* Clear the rendering surface with the specified color */
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_StartTextInput();


    /* Draw the Image on rendering surface */
    done = 0;
    atexit(SDL_Quit);
    while (!done) {
        loop();
        //SDL_RenderClear(renderer);
       // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
         //  SDL_RenderClear(renderer);
        SDL_Delay(500);
        //sleep_ms(500);
    }

    close_w();
    SDL_Quit();

    return 0;
}

int loadMedia(char* arg)
{

    //Loading success flag
    int success = 1;

    //Load splash image
    Wrkr_srfc = SDL_LoadBMP( arg );
    if( Wrkr_srfc == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", arg, SDL_GetError() );
        success = 0;
    }

    return success;
}

void close_w()
{
    //Deallocate surface
    SDL_FreeSurface( Wrkr_srfc );
    Wrkr_srfc = NULL;

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;


    //Quit SDL subsystems
    SDL_Quit();
}
