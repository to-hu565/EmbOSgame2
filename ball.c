#include "gba.h"
#include "color.h"
#include "ball.h"
#include "game.h"
#include "box.h"

#define DY 1
#define RR 3       //ボール直径
#define BOUND 2     //境界
#define DEADLINE 10

static struct box ball;

int ball_get_dx(void) { return ball.dx; }

void ball_set_dx(int new_dx) {
if(new_dx <= 2 && new_dx >= -2)
  ball.dx = new_dx;
}

int ball_get_dy(void) { return ball.dy; }

void ball_set_dy(int new_dy) {
if(new_dy <= 2 && new_dy >= -2)
  ball.dy = new_dy;
}

struct box *ball_get_box(void) { return &ball; }

int ball_get_x(void) { return ball.x; }

int ball_get_y(void) { return ball.y; }

void ball_initialize(int r){
  ball.x = LCD_WIDTH / 2;
  ball.y = LCD_HEIGHT / 2 - 25;
  ball.width = RR;
  ball.height = RR;
  ball.dx = r - 2;
  ball.dy = DY;
  int bx = ball.x;
  int by = ball.y;
  draw_box(&ball, bx ,by, COLOR_WHITE);;
}

void ball_step(){
  
  int bx = ball.x;
  int by = ball.y;
  int dx = ball.dx;
  int dy = ball.dy;

  hword val;

  val = gba_register(TMR_COUNT0);
  int r = (val>>3) % 5;
  
  switch (game_get_state()) {

    
  case START:

    draw_box(&ball, bx, by, COLOR_BLACK);
    ball_initialize(r);
    
    break;
    
  case RUNNING:
    //ボール移動、壁との反射(ボールが埋まったらもとに戻す)
    bx += dx;
    by += dy;
    
    if((bx > LCD_WIDTH - BOUND - ball.width) || (bx < BOUND)){
      if(bx > LCD_WIDTH - BOUND - ball.width)
	bx = LCD_WIDTH - BOUND - ball.width;
      if(bx < BOUND)
        bx = BOUND;
      dx = -dx;
    }

    if(by < BOUND){
      by = BOUND;  
      dy = -dy;
    }


    if(ball_bonus_state() != 1){
      move_box(&ball, bx ,by, COLOR_WHITE);
    }else{
       move_box(&ball, bx ,by, COLOR_RED);
    }
    
    ball.dx = dx;
    ball.dy = dy;
    
    if (by >= LCD_HEIGHT - DEADLINE - ball.height){
      stock_lose();
      game_set_state(MISS);
    }
    break;

  case MISS:
    /* 現在のボールを画面から消し，
       ボールの位置，速度を初期状態にし，ボールを表示する．*/
    draw_box(&ball, bx, by, COLOR_BLACK);
    ball_initialize(r);
    break;    
    
  case DEAD:
    //何もしない．
    break;
    
  case RESTART:
    /* 現在のボールを画面から消し，
       ボールの位置，速度を初期状態にし，ボールを表示する．*/
    draw_box(&ball, bx, by, COLOR_BLACK);
    ball_initialize(r);
    break;
    
  case CLEAR:
    //何もしない．
    break;
  }
   
}
