/* game.h See LICENSE file for details */

#ifndef _DICES_GAME_H
#define _DICES_GAME_H

struct dice {
  int dice;
  int valid;
};

struct player {
  const char *name;
  int score;
};

struct game {
  int turns;
  int max_score;
  struct player player[2];
  int dices;
  struct dice last_dices[6];
  int last_dices_count;
  int last_occ[6];
  int cur_score;
};

void game_init      (struct game *game);
void game_destroy   (struct game *game);
void game_new       (struct game *game);
void game_roll      (struct game *game);
void game_pass      (struct game *game);
int  current_player (struct game *game);
int  winner         (struct game *game);
int  player_score   (struct game *game, int player);
const char *player_name (struct game *game, int player);
void set_player_name (struct game *game, int player, const char *name);

#endif /* _DICES_GAME_H */

/* EOF */
