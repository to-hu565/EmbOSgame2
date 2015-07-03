#include "gba.h"
#include "color.h"
#include "box.h"
#include "block.h"
#include "racket.h"
#include "game.h"

#define BARRAGE_WIDTH 2
#define BARRAGE_HEIGHT 2
#define DX 1
#define DY 2
#define BLOCK_MAX 300   //ブロックの最大個数*3 = 弾幕の最大個数

static struct box barrage [BLOCK_MAX];
static int flags[BLOCK_MAX];//0:初期(無), 1:あり, 2:消え

static int barrage_count, barrage_die_count;

void barrage_new(int x, int y){
  barrage[barrage_count].x = x;
  barrage[barrage_count].y = y;
  if(x > LCD_WIDTH /2){
    barrage[barrage_count].dx = DX;
  }else{
    barrage[barrage_count].dx = -DX;
  }
  barrage[barrage_count].dy = DY;
  barrage[barrage_count].width = BARRAGE_WIDTH;
  barrage[barrage_count].height = BARRAGE_HEIGHT;
  draw_box(&barrage[barrage_count], x ,y, COLOR_WHITE);
  flags[barrage_count] = 1;
  barrage_count++;

  barrage[barrage_count].x = x;
  barrage[barrage_count].y = y;
  barrage[barrage_count].dx = 0;
  barrage[barrage_count].dy = DY;
  barrage[barrage_count].width = BARRAGE_WIDTH;
  barrage[barrage_count].height = BARRAGE_HEIGHT;
  draw_box(&barrage[barrage_count], x ,y, COLOR_WHITE);
  flags[barrage_count] = 1;
  barrage_count++;
  
  barrage[barrage_count].x = x;
  barrage[barrage_count].y = y;
  if(x > LCD_WIDTH /2){
    barrage[barrage_count].dx = -DX;
  }else{
    barrage[barrage_count].dx = DX;
  }
  barrage[barrage_count].dy = DY;
  barrage[barrage_count].width = BARRAGE_WIDTH;
  barrage[barrage_count].height = BARRAGE_HEIGHT;
  draw_box(&barrage[barrage_count], x ,y, COLOR_WHITE);
  flags[barrage_count] = 1;
  barrage_count++;
}

void barrage_step(){
  int i, bx, by, rl, rr, ry;//bx, by:ボール座標 rl, rr, ry:ラケット左、右、y座標
  
  switch (game_get_state()) {
  case START:
    for(i = 0; i < BLOCK_MAX; i++)
      flags[i] = 0;
    barrage_count = 0;
    barrage_die_count = 0;
    break;
    
  case RUNNING:
    
    if(brake_flag_get()){
      barrage_new(brake_get_x(), brake_get_y());
      brake_flag_reset();
    }
    
    for(i = barrage_die_count; flags[i] != 0; i++){
      if(flags[i] == 1){
	bx = barrage[i].x + barrage[i].dx;
	by = barrage[i].y + barrage[i].dy;
	rl = racket_get_x();
	rr = rl + racket_get_w();
	ry = LCD_HEIGHT-15;
	if(bx >= rl && bx <= rr && by >= ry){
	  racket_hit_barrage();
	  flags[i] = 2;
	}
      }
      
      move_box(&barrage[i], bx ,by, COLOR_WHITE);
      
      if(bx <= 0 || bx >= LCD_WIDTH || by <= 0 || by >= LCD_HEIGHT - 11){
	flags[i] = 2;
	move_box(&barrage[i], bx ,by, COLOR_BLACK);
	barrage_die_count++;
      }
      //move_box(&barrage[i], bx ,by, COLOR_WHITE);
    }
      
    break;
    
  case MISS:
    for(i = 0; i < BLOCK_MAX; i++)
      flags[i] = 0;
    barrage_count = 0;
    barrage_die_count = 0;
    break;
    
  case DEAD:
    //何もしない．
    break;
    
  case RESTART:
    for(i = 0; i < BLOCK_MAX; i++)
      flags[i] = 0;
    barrage_count = 0;
    barrage_die_count = 0;
    break;
    
  case CLEAR:
    //何もしない．
    break;
  }
  
}
