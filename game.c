#include "gba.h"
#include "game.h"

static enum state current_state;  // 現在の状態

enum state game_get_state(void) { return current_state; }
void game_set_state(enum state new_state) {
  current_state = new_state;
}

void game_step(void)
{
  int key = gba_register(KEY_STATUS);
  
  switch (game_get_state()) {
  case START:

    if (! (key & KEY_START))  //STARTキーが押された
      game_set_state(RUNNING);
    break;

  case RUNNING:
    if (! (key & KEY_R))  //Rキーが押された(デバッグ用)
      game_set_state(CLEAR);
    if (! (key & KEY_L))  //Lキーが押された(デバッグ用)
      game_set_state(MISS);
    break;

  case MISS:
    if (! (key & KEY_START))  //STARTキーが押された
      game_set_state(RUNNING);
    break;
    
  case DEAD:
    if (! (key & KEY_START))  //STARTキーが押された
      game_set_state(RESTART);
    break;
    
  case RESTART:
    /* 次のティックはRUNNING状態にする．*/
    game_set_state(RUNNING);
    break;

  case CLEAR:
    if (! (key & KEY_SELECT))  //SELECTキーが押された(STARTの場合1tickだけボタン押さないとRUNNINGに移動してしまうため)
      game_set_state(START);
    break;
  }
}
