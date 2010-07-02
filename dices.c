/* dices.c See LICENSE file for details. */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
    printf ("Player 1: %s%4d%s\n", C_YELLOW_B, game.player[0], C_NORMAL);
    printf ("Player 2: %s%4d%s\n\n", C_YELLOW_B, game.player[1], C_NORMAL);
    while (1) {
      int i;
      int new_score;
      int cp = current_player ( &game );
      int tot = cp == 1 ? game.player[0] : game.player[1];
      game_roll ( &game );
      printf("Player %s%d%s rolls:", C_YELLOW_B, cp, C_NORMAL);
      for (i = 0; i < game.last_dices_count; i++) {
        const char *str1, *str2, *str3;
        str1 = game.last_dices[i].valid ? C_GREEN_B : C_RED_B;
        str2 = C_NORMAL;
        str3 = game.last_dices[i].valid ? C_GREEN_B : C_RED_B;
        printf(" %s[%s%d%s]%s", str1, str2
          , game.last_dices[i].dice, str3, C_NORMAL);
      }
      for (i = 0; i < 6 - game.last_dices_count; i++)
        printf ("    ");
      new_score = (game.cur_score >= 50 || (tot > 0 && game.cur_score >= 35) )
        ? tot + game.cur_score : tot;
      printf (" S[ %s%4d%s ] T[ %s%4d%s ] d[ %s%d%s ]\n"
        , (tot == new_score) ? C_RED_B : C_YELLOW_B, game.cur_score, C_NORMAL
        , C_GREEN_B, new_score, C_NORMAL
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

void init_seed (void) {
  unsigned int seed;
  FILE *f;
  f = fopen("/dev/urandom", "r");
  if (f == NULL) {
    perror("Can not open /dev/urandom");
    fprintf(stderr, "Using system time to seed RNG.\n");
    seed = (unsigned int) time (NULL);
  } else {
    if (1 != fread(&seed, sizeof(seed), 1, f)) {
      fprintf(stderr, "Can not read from /dev/urandom. "
        "Using system time to seed RNG.\n");
      seed = (unsigned int) time (NULL);
    }
    if (fclose(f) == EOF) {
      perror("Can not close /dev/urandom");
    }
  }
  srand (seed);
}

int main (int argc, char **argv) {
  if (argc > 1) {
    fprintf(stderr, "Usage: %s\n", argv[0]);
    return 1;
  }
  init_seed ();
  dices ();
  return 0;
}

/* EOF */
