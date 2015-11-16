/*
 * chess_board.h
 *
 *  Created on: Nov 15, 2015
 *      Author: ico
 */

#ifndef CHESS_BOARD_H_
#define CHESS_BOARD_H_

#include <stdlib.h>
#include <stdio.h>
#include "sleep.h"


#include <SDL2/SDL.h>
#include <pthread.h>


void DrawChessBoard(SDL_Renderer * renderer);
void loop();
void* chess_board_t(void* arg);
void* chess_board(void* arg);
int loadMedia(char* arg);
void close_w();




#endif /* CHESS_BOARD_H_ */
