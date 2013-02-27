#include "battleships_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

player *init_player (player *p) {

	p = malloc(sizeof(player));
	p->state_b = malloc(sizeof(battle_board));
	p->game_b = malloc(sizeof(battle_board));
	p->ships = malloc(sizeof(ships));
	p->ships->destroyer = malloc(sizeof(ship));
	p->ships->sub = malloc(sizeof(ship));
	p->ships->boat = malloc(sizeof(ship));
	p->player_num = 1;
	p->lives = 12;

	return p;
}

// Initial setup of player and also calls method to set up the players ship locations.
player *initial_setup (player *p) {

	set_up_board(p->state_b);
	set_up_board(p->game_b);

	p->ships->destroyer->length = 5;
	p->ships->sub->length = 4;
	p->ships->boat->length = 3;
	
	do {
		if (p->type == COMPUTER) {
			srand(time(NULL));
			p->ships->destroyer->orientation = ((rand()%2) + 1);
			
			p->ships->destroyer->x = rand()%10;
			p->ships->destroyer->y = rand()%10;
		
		}
		else {
			printf("Player %d enter 1 for horizontal and 2 for vertial: \n", p->player_num);
			scanf("%d", &p->ships->destroyer->orientation);
			printf("Player %d enter x coord of destroyer (length 5): \n", p->player_num);
			scanf("%d", &p->ships->destroyer->x);
			printf("Player %d enter y coord of destroyer (length 5); \n", p->player_num);
			scanf("%d", &p->ships->destroyer->y);
		}
	}while(!set_up_ship(p->state_b, p->ships->destroyer));
	add_ship(p->state_b, p->ships->destroyer);
	//print_board(p->state_b);
	
	do {
		if (p->type == COMPUTER) {
			srand(time(NULL));
			p->ships->sub->orientation = ((rand()%2) + 1);
			
			p->ships->sub->x = rand()%10;
			p->ships->sub->y = rand()%10;
		
		}
		else {
			printf("Player %d enter 1 for horizontal and 2 for vertial: \n", p->player_num);
			scanf("%d", &p->ships->sub->orientation);
			printf("Player %d enter x coord of sub (length 4): \n", p->player_num);
			scanf("%d", &p->ships->sub->x);
			printf("Player %d enter y coord of sub (length 4); \n", p->player_num);
			scanf("%d", &p->ships->sub->y);
		}
	}while(!set_up_ship(p->state_b, p->ships->sub));
	add_ship(p->state_b, p->ships->sub);
	//print_board(p->state_b);

	do {
		if (p->type == COMPUTER) {
			srand(time(NULL));
			p->ships->boat->orientation = ((rand()%2) +1);
			
			p->ships->boat->x = rand()%10;
			p->ships->boat->y = rand()%10;
		
		}
		else {
			printf("Player %d enter 1 for horizontal and 2 for vertial: \n", p->player_num);
			scanf("%d", &p->ships->boat->orientation);
			printf("Player %d enter x coord of boat (length 3): \n", p->player_num);
			scanf("%d", &p->ships->boat->x);
			printf("Player %d enter y coord of boat (length 3); \n", p->player_num);
			scanf("%d", &p->ships->boat->y);
		}
	}while(!set_up_ship(p->state_b, p->ships->boat));
	add_ship(p->state_b, p->ships->boat);
	//print_board(p->state_b);

	//print_board(p->state_b);

	return p;
}

// Checks orientation and whether the ship will fit. 
int set_up_ship (battle_board *b, ship *s) {
	
	printf("Orientation = %d\n", s->orientation);
	
	if(s->orientation == HORIZONTAL && s->length + s->x > WIDTH) {
		printf("Ship won't fit. Really, what were you thinking???\n");
		return 0;
	}
	else if(s->orientation == VERTICAL && s->length + s->y > HEIGHT) {
		printf("Ship won't fit. Really, what were you thinking???\n");
		return 0;
	}
	if(s->orientation != HORIZONTAL && s->orientation != VERTICAL) {
		printf("Orientation = %d\n", s->orientation);
		printf("Not a supported orientation\n");
		return 0;
	}

	for (int i = 0; i < s->length; i++) {
		if (s->orientation == HORIZONTAL) {
			if (b->board[s->y][s->x+i] == '*') {
				printf("Horizontal - Ship can't be placed as it hits another ship\n");
				return 0;
			}
		}
		else {	
			if (b->board[s->y+i][s->x] == '*') {
				printf("Vertical - Ship can't be placed as it hits another ship\n");
				return 0;
			}
		}
	}	
	return 1;
}

// Sets up the initial board. Used for both the game board and the state board for each player.
void set_up_board (battle_board *b) {

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			b->board[i][j] = '_';
		}
	}
}

void print_board (battle_board *b) {
	
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			printf("%c", b->board[i][j]);
		}
		printf("\n");
	}
}

int add_ship (battle_board *b, ship *s) {

	for (int i = 0; i < s->length; i++) {
		if (s->orientation == HORIZONTAL) 
			b->board[s->y][s->x+i] = '*';	
		else
			b->board[s->y+i][s->x] = '*';
	}
	printf("Ship added ok\n");
	return 1;
}

void check_for_hit (player *current, player *opp, int x, int y) {

	if (opp->state_b->board[y][x] == '*') {
		printf("Hit battleship\n");
		opp->lives--;
		opp->state_b->board[y][x] = 'X';
		opp->game_b->board[y][x] = 'X';
	}
	else if (opp->state_b->board[y][x] == 'X' || opp->state_b->board[y][x] == 'O') {
		printf("Same position as before\n");
	}
	else {
		printf("Did not hit ship\n");
		opp->state_b->board[y][x] = 'O';
		opp->game_b->board[y][x] = 'O';
	}
}

// This switches the players round by switch over the pointers. 
// Not entirely sure if this is the best way to do this.
player *switch_player (player *c, player *p1, player *p2) {
	
	if (c->player_num == 1) {
		c = p2;
	}
	else {
		c = p1;
	}
	return c;
}

// If the computer has hit a ship then we exhaust all possibilies around that hit.
// This means that once the computer hits a ship he will sink it.
// Otherwise we just make a random move on the board.
void computers_move (player *p, battle_board *b) {

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (b->board[i][j] == 'X') {
				if (check_north(p, b, i, j)) {
					//printf("Check North\n x = %d\n y = %d\n", p->x, p->y); 
					return;
				}
				if (check_south(p, b, i, j)) {
					//printf("Check South\n x = %d\n y = %d\n", p->x, p->y);
					return;
				}
				if (check_east(p, b, i, j)) {
					//printf("Check East\n x = %d\n y = %d\n", p->x, p->y);
					return;
				}	
				if (check_west(p, b, i, j)) {
					//printf("Check west\n x = %d\n y = %d\n", p->x, p->y);
					return;
				}
			}	
		}
	}
	srand(time(NULL));
	p->y = rand()%10;
	p->x = rand()%10;

}

// Checks the location North of a hit.
int check_north (player *p, battle_board *b, int i, int j) {

	for (; i >= 0; i--) {
		if (b->board[i][j] == '_') {
			p->y = i;
			p->x = j;
			return 1;
		}
		if (b->board[i][j] == 'O') {
			return 0;
		}
	}
	return 0;
}	

// Check the location South of a hit.
int check_south (player *p, battle_board *b, int i, int j) {

	for (; i < HEIGHT ; i++) {
		if (b->board[i][j] == '_') {
			p->y = i;
			p->x = j;
			return 1;
		}
		if (b->board[i][j] == 'O') {
			return 0;
		}
	}
	return 0;
}

// Checks the location East of a hit.
int check_east (player *p, battle_board *b, int i, int j) {

	for (; j >= 0; j--) {
		if (b->board[i][j] == '_') {
			p->y = i;
			p->x = j;
			return 1;
		}
		if (b->board[i][j] == 'O') {
			return 0;
		}
	}
	return 0;
}

// Checks the location West of a hit.
int check_west (player *p, battle_board *b, int i, int j) {

	for (; j < WIDTH; j++) {
		if (b->board[i][j] == '_') {
			p->y = i;
			p->x = j;
			return 1;
		}
		if (b->board[i][j] == 'O') {
			return 0;
		}
	}
	return 0;
}

void destroy_player (player *p) {
	free(p->ships->destroyer);
	free(p->ships->sub);
	free(p->ships->boat);
	free(p->ships);
	free(p->game_b);
	free(p->state_b);
	free(p);
}
