#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "battleships_functions.h"
#include "battleships_structs.h"
#include "constants.h"

int main (int argc, char *argv[]) {

	player *player1 = init_player(player1);
	player1->player_num = 1;

	player *player2 = init_player(player2);
	player2->player_num = 2;	

	int num_humans = 0;
	do {
		printf("Human versus computer press 1\n");
		printf("Human versus human press 2\n");
		scanf("%d", &num_humans); 
	}while(num_humans != 1 && num_humans != 2);		

	if (num_humans == 1)
		player2->type = COMPUTER;

	player1 = initial_setup(player1);
	player2 = initial_setup(player2);

	// Create 2 extra player pointers to track current players turn and the oppsing player.
	player *current_player = player1;
	player *opp_player = player2;

	int x = 0;
	int y = 0;
	while (1) {
		if (current_player->type == COMPUTER) {
			srand(time(NULL));
			computers_move(current_player, opp_player->game_b);
			printf("===============\n");
			printf("Computer move x = %d, y = %d\n", current_player->x, current_player->y);
			check_for_hit(current_player, opp_player, current_player->x, current_player->y);	
			printf("===============\n\n");
		}
		else { 
			printf("Player %d enter X coordinate: ", current_player->player_num);
			scanf("%d", &x);

			printf("Plyaer %d enter Y coordinate: ", current_player->player_num);
			scanf("%d", &y);

			//printf("x = %d\n", x);
			//printf("y = %d\n", y);
			check_for_hit(current_player, opp_player, x, y);		
			printf("==============\n");
			printf("Player %d board\n", opp_player->player_num);
			print_board(opp_player->game_b);
			printf("==============\n\n");
		}
		if (opp_player->lives == 0) {
			printf("Player %d wins\n", current_player->player_num);
			break;
		}
		// Swtich the players turn by switching the pointers over. 
		current_player = switch_player(current_player, player1, player2);			
		opp_player = switch_player(current_player, player1, player2);
	}

	destroy_player(player1);
	destroy_player(player2);

	return 0;
}

