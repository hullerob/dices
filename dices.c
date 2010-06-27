/* dices.c See LICENSE file for details. */

#include <stdio.h>
#include "game.h"

void dices (void) {
  struct game game;
  game_new ( &game );
  while (winner ( &game ) == 0) {
    printf ("\n--[ %3d ]------------------\n", game.turns / 2 + 1);
    printf ("Player 1: %4d\n", game.player_1);
    printf ("Player 2: %4d\n\n", game.player_2);
    while (1) {
      int i, ndic;
      int cp = current_player ( &game );
      int tot = cp == 1 ? game.player_1 : game.player_2;
      game_roll ( &game );
      printf("Player %d rolls:", cp);
      ndic = 0;
      for (i = 0; i < 6; i++) {
        while (game.last_occ[i] --> 0) {
          printf (" [%d]", i+1);
          ndic ++;
        }
      }
      for (i = 0; i < 6 - ndic; i++)
        printf ("    ");
      printf (" S[ %4d ] T[ %4d ] d[ %d ]\n"
        , game.cur_score, tot + game.cur_score, game.dices);
      if (game.cur_score == 0) {
        break;
      }
      printf ("Continue? [Y/n]: ");
      fflush (stdout);
      switch (getchar()) {
        case 'n':
          game_pass ( &game );
          while (getchar() != '\n');
          goto roll_br;
        case '\n':
          break;
        default:
          while (getchar() != '\n');
          break;
      }
    }
roll_br: ;
  }
  printf("Player %d wins.\n", winner( &game ));
}

int main (int argc, char **argv) {
  if (argc > 1) {
    fprintf(stderr, "Usage: %s\n", argv[0]);
    return 1;
  }
  dices ();
  return 0;
}

/* EOF */
