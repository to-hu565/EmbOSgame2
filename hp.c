#include "gba.h"
#include "color.h"
#include "racket.h"
#include "game.h"
#include "box.h"

#define WIDTH 50
#define HEIGHT 6
#define X 20
#define Y LCD_HEIGHT - HEIGHT - 1

#define S_WIDTH 6
#define S_HEIGHT 6
#define S_X LCD_WIDTH - 28
#define S_Y LCD_HEIGHT - HEIGHT - 1

struct box hpbar;//体力ゲージ表示

static int hp;//残りhp

struct box stock;//ストック表示

static int stock_count;//残機

int hp_get(void) { return hp; }

void hp_damage(void) {
  draw_box(&hpbar, X ,Y, COLOR_BLACK);
  hp-=2;
  hpbar.width = hp;
  draw_box(&hpbar, X, Y, COLOR_RED);
}

void stock_lose(void) {
  stock_count--;
  draw_box(&stock, S_X + stock_count * 8, stock.y, COLOR_BLACK);
}

void hp_initialize(){
  hpbar.x = X;
  hpbar.y = Y;
  hpbar.width = WIDTH;
  hpbar.height = HEIGHT;
  int x = hpbar.x;
  int y = hpbar.y;
  draw_box(&hpbar, x ,y, COLOR_RED);
  hp = 50;
}

void stock_initialize(){
  stock.x = S_X;
  stock.y = S_Y;
  stock.width = S_WIDTH;
  stock.height = S_HEIGHT;
  draw_box(&stock, stock.x , stock.y, COLOR_BLUE);
  draw_box(&stock, stock.x+8 , stock.y, COLOR_BLUE);
  draw_box(&stock, stock.x+8 , stock.y, COLOR_BLUE);
  stock_count = 3;
}

void hp_step(){
  
  hword color = COLOR_WHITE;
  
  switch (game_get_state()) {
  case START:
    hp_initialize();
    stock_initialize();
    break;
    
  case RUNNING:
    draw_box(&hpbar, hpbar.x, hpbar.y, COLOR_RED);
    if(hp == 0){
      stock_lose();
      if(stock_count == 0){
	game_set_state(DEAD);
	break;
      }
      game_set_state(MISS);
    }
    break;
    
  case MISS:    
    if(stock_count == 0)
      game_set_state(DEAD);
    hp = 50;
    hpbar.width = hp;   
    break;
    
  case DEAD:
    break;
    
  case RESTART:
    hp_initialize();
    stock_initialize();
    break;
    
  case CLEAR:
    break;
    
  }
  
}
    
