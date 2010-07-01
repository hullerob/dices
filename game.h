/* game.h See LICENSE file for details */

#ifndef _DICES_GAME_H
#define _DICES_GAME_H

struct dice {
  int dice;
  int valid;
};

struct game {
  int turns;
  int max_score;
  int player_1;
  int player_2;
  int dices;
  struct dice last_dices[6];
  int last_dices_count;
  int last_occ[6];
  int cur_score;
};

void game_new       (struct game *game);
void game_roll      (struct game *game);
void game_pass      (struct game *game);
int  current_player (struct game *game);
int  winner         (struct game *game);

#endif /* _DICES_GAME_H */

/* EOF */
