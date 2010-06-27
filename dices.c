/* dices.c See LICENSE file for details. */

#include <stdio.h>
#include "game.h"

#ifdef WITH_COLOR
#define C_NORMAL   "\033[0m"
#define C_RED      "\033[31m"
#define C_GREEN    "\033[32m"
#define C_YELLOW   "\033[33m"
#define C_BLUE     "\033[34m"
#define C_RED_B    "\033[31;1m"
#define C_GREEN_B  "\033[32;1m"
#define C_YELLOW_B "\033[33;1m"
#define C_BLUE_B   "\033[34;1m"
#else /* WITH_COLOR */
#define C_NORMAL   ""
#define C_RED      ""
#define C_GREEN    ""
#define C_YELLOW   ""
#define C_BLUE     ""
#define C_RED_B    ""
#define C_GREEN_B  ""
#define C_YELLOW_B ""
#define C_BLUE_B   ""
#endif /* WITH_COLOR */

void dices (void) {
  struct game game;
  game_new ( &game );
  while (winner ( &game ) == 0) {
    printf ("\n--[ %3d ]------------------\n", game.turns / 2 + 1);
    printf ("Player 1: %s%4d%s\n", C_YELLOW_B, game.player_1, C_NORMAL);
    printf ("Player 2: %s%4d%s\n\n", C_YELLOW_B, game.player_2, C_NORMAL);
    while (1) {
      int i, j, ndic;
      int cp = current_player ( &game );
      int tot = cp == 1 ? game.player_1 : game.player_2;
      game_roll ( &game );
      printf("Player %s%d%s rolls:", C_YELLOW_B, cp, C_NORMAL);
      ndic = 0;
      for (i = 0; i < 6; i++) {
        for (j = 0; j < game.last_occ[i]; j++) {
          const char *stc;
          /* FIXME straight */
          if (i == 0 || i == 4 || game.last_occ[i] >= 3) {
            stc = C_GREEN_B;
          } else {
            stc = C_RED_B;
          }
          printf (" %s[%s%d%s]%s", stc, C_NORMAL, i+1, stc, C_NORMAL);
          ndic ++;
        }
      }
      for (i = 0; i < 6 - ndic; i++)
        printf ("    ");
      printf (" S[ %s%4d%s ] T[ %s%4d%s ] d[ %s%d%s ]\n"
        , C_YELLOW_B, game.cur_score, C_NORMAL
        , C_GREEN_B, tot + game.cur_score, C_NORMAL
        , C_RED_B, game.dices, C_NORMAL);
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
