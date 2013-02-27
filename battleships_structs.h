#ifndef BATTLESHIP_STRUCTS_H_INCLUDED
#define BATTLESHIP_STRUCTS_H_INCLUDED

#include "constants.h"

typedef struct {
	char board[HEIGHT][WIDTH];
}battle_board;

typedef struct {
	int length;
	int orientation;
	int x;
	int y;
}ship;

typedef struct {
	ship *destroyer;
	ship *sub;
	ship *boat;
}ships;

typedef struct {
	battle_board *state_b;
	battle_board *game_b;
	ships *ships;
	int x;
	int y;
	int lives;
	int player_num;
	int type;
}player;

#endif
