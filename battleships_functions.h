#ifndef BATTLESHIP_FUNCTIONS_H_INCLUDED
#define BATTLESHIP_FUNCTIONS_H_INCLUDED

#include "battleships_structs.h"
#include "constants.h"

player *init_player (player *p);
player *initial_setup (player *p);
int set_up_ship (battle_board *b, ship *s);
void set_up_board (battle_board *b);
void print_board (battle_board *b);
int add_ship (battle_board *b, ship *s);
void check_for_hit (player *current, player *opp, int x, int y);
void computers_move (player *p, battle_board *b);
int check_north (player *p, battle_board *b, int x, int y);
int check_south (player *p, battle_board *b, int x, int y);
int check_east(player *p, battle_board *b, int x, int y);
int check_west (player *p, battle_board *b, int x, int y);
player *switch_player (player *c, player *p1, player *p2);
void destroy_player (player *p);

#endif
