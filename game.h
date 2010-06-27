/* game.h */

#ifndef _DICES_GAME_H
#define _DICES_GAME_H

struct game {
  int turns;
  int max_score;
  int player_1;
  int player_2;
  int dices;
  int cur_score;
};

void game_new       (struct game *game);
void game_roll      (struct game *game);
void game_pass      (struct game *game);
int  current_player (struct game *game);
int  winner         (struct game *game);

#endif /* _DICES_GAME_H */

/* EOF */
