/* game.c See LICENSE file for details */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"

int random_number (void) {
  int rnd;
  rnd = rand();
  return rnd % 6;
}

int get_score(int *occ) {
  int score, i;
  if (occ[0] == 1 && occ[1] == 1 && occ[2] == 1
    && occ[3] == 1 && occ[4] == 1 && occ[5] == 1) {
    return 120;
  }
  score = 0;
  if (occ[0] >= 3) {
    score += 100 * (occ[0] - 2);
  } else {
    score += 10 * occ[0];
  }
  for (i = 1; i < 6; i++) {
    if (occ[i] >= 3) {
      score += (i+1) * 10 * (occ[i] - 2);
    }
  }
  if (occ[4] < 3) {
    score += 5 * occ[4];
  }
  return score;
}

void update_dices (struct game *game) {
  int i, j;
  int dice_cout = 0;
  int straight = game -> last_occ[0] == 1 && game -> last_occ[1] == 1
    && game -> last_occ[2] == 1 && game -> last_occ[3] == 1
    && game -> last_occ[4] == 1 && game -> last_occ[5] == 1;
  for (i = 0; i < 6; i++) {
    for (j = 0; j < game -> last_occ[i]; j++) {
      game -> last_dices[dice_cout].valid
        = i == 0 || i == 4 || game -> last_occ[i] >= 3 || straight;
      game -> last_dices[dice_cout].dice = i+1;
      dice_cout ++;
    }
  }
  game -> last_dices_count = dice_cout;
}

int get_dices (int *occ) {
  int dices = 0;
  if (occ[0] == 1 && occ[1] == 1
    && occ[2] == 1 && occ[3] == 1
    && occ[4] == 1 && occ[5] == 1)
    return 6;
  if (occ[1] < 3) dices += occ[1];
  if (occ[2] < 3) dices += occ[2];
  if (occ[3] < 3) dices += occ[3];
  if (occ[5] < 3) dices += occ[5];
  return dices ? dices : 6;
}

void game_init      (struct game *game) {
  game -> player[0].name = NULL;
  game -> player[1].name = NULL;
}

void game_destroy   (struct game *game) {
  free ((void *) game -> player[0].name);
  free ((void *) game -> player[1].name);
  game -> player[0].name = NULL;
  game -> player[1].name = NULL;
}

void game_new       (struct game *game) {
  int i;
  game -> turns = 0;
  game -> max_score = 1000;
  game -> player[0].score = 0;
  game -> player[1].score = 0;
  game -> dices = 6;
  game -> cur_score = 0;
  for (i = 0; i < 6; i++)
    game -> last_occ[i] = 0;
}

void game_roll      (struct game *game) {
  int i;
  int occ[6] = {0, 0, 0, 0, 0, 0};
  int score;
  for (i = 0; i < game -> dices; i++) {
    occ[random_number()] ++;
  }
  score = get_score(occ);
  if (score == 0) {
    game -> cur_score = 0;
    game -> turns ++;
    game -> dices = 6;
  } else {
    game -> cur_score += score;
    game -> dices = get_dices (occ);
  }
  for (i = 0; i < 6; i++)
    game -> last_occ[i] = occ[i];
  update_dices (game);
}

void game_pass      (struct game *game) {
  int player = game -> turns & 1;
  if (player) {
    if ( ((game -> player[1].score > 0) && (game -> cur_score >= 35))
      || (game -> cur_score >= 50))
      game -> player[1].score += game -> cur_score;
  } else {
    if ( ((game -> player[0].score > 0) && (game -> cur_score >= 35))
      || (game -> cur_score >= 50))
      game -> player[0].score += game -> cur_score;
  }
  game -> cur_score = 0;
  game -> turns ++;
  game -> dices = 6;
}

int  player_score   (struct game *game, int player) {
  return game -> player[player-1].score;
}

int  current_player (struct game *game) {
  return (game -> turns & 1) + 1;
}

int  winner         (struct game *game) {
  if (game -> player[0].score < game -> max_score
    && game -> player[1].score < game -> max_score)
    return 0;
  if (game -> player[0].score > game -> player[1].score)
    return 1;
  else
    return 2;
}

const char *player_name (struct game *game, int player) {
  return game -> player[player-1].name;
}

void set_player_name (struct game *game, int player, const char *name) {
  size_t len = strlen (name) + 1;
  free ((void *) game -> player[player-1].name);
  game -> player[player-1].name
    = (const char *) malloc (sizeof (char) * len);
  assert(game -> player[player-1].name != NULL);
  strcpy((char *) game -> player[player-1].name, name);
}

/* EOF */
