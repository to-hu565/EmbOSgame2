#include "gba.h"
#include "color.h"
#include "ball.h"
#include "game.h"
#include "block.h"
#include "box.h"

#define BLOCK_COLS 24//12
#define BLOCK_ROWS 5
#define BLOCK_TOP 4
#define BLOCK_WIDTH 10//20
#define BLOCK_HEIGHT 10

#define BONUS 20   //bonus状態で壊せるブロック数
#define SPUP 30    //speedupするときのブロック残数
#define DEBUG 0    //debug用クリア時ブロック残数

static struct box boxes[BLOCK_COLS][BLOCK_ROWS];

static int flags[BLOCK_COLS][BLOCK_ROWS];

static int num_blocks,
  updown,
  leftright,
  sp1,            /*speedup*/
  flag_bonus,     /*bonus状態かどうか*/
  count_bonus,    /*bonus状態に壊したブロック数*/
  ri, rj,         /*bonusブロック位置乱数*/
  brake_x, brake_y, /*壊れたブロックの中心位置*/
  brake_flag;     /*ブロック壊れたか判定*/

int brake_flag_get(void){ return brake_flag;}

void brake_flag_reset(void){ brake_flag = 0;}

int brake_get_x(void){ return brake_x;}

int brake_get_y(void){ return brake_y;}

int ball_bonus_state(void) { return flag_bonus; }

void boxes_initialize(){
  hword val;
  val = gba_register(TMR_COUNT0);
  ri = (val>>2) % 24;//12
  rj = (val>>2) % 4;
  
  int i, j;
  for(j = 0; j < BLOCK_ROWS; j++){
    for(i = 0; i < BLOCK_COLS; i++){
      boxes[i][j].x = i * BLOCK_WIDTH;
      boxes[i][j].y = BLOCK_TOP + j * BLOCK_HEIGHT;
      boxes[i][j].width = BLOCK_WIDTH-1;
      boxes[i][j].height = BLOCK_HEIGHT-1;
      flags[i][j] = 1;
      int bx = boxes[i][j].x;
      int by = boxes[i][j].y;
      draw_box(&boxes[i][j], bx ,by, COLOR_WHITE);
      if(i == ri && j == rj)
	draw_box(&boxes[i][j], bx ,by, COLOR_RED);
    }
  }
  num_blocks = (BLOCK_COLS * BLOCK_ROWS);
  updown = 0;
  leftright = 0;
  sp1 = 0;
  flag_bonus = 0;
  count_bonus = 0;
}

static int hit(int x, int y){
  int i = x / BLOCK_WIDTH;
  int j = (y - BLOCK_TOP) / BLOCK_HEIGHT;

  if(i < 0 || j < 0 || i >= BLOCK_COLS || j >= BLOCK_ROWS){
    return 0;
  }else if(flags[i][j] == 0)
    return 0;

  brake_x = i * BLOCK_WIDTH + (BLOCK_WIDTH / 2);
  brake_y = j * BLOCK_HEIGHT + (BLOCK_HEIGHT / 2);
  return 1;
}

static void delete(int x, int y, int ri, int rj){
  int i = x / BLOCK_WIDTH;
  int j = (y - BLOCK_TOP) / BLOCK_HEIGHT;
  if(flags[i][j] == 1){
    flags[i][j] = 0;
    draw_box(&boxes[i][j], boxes[i][j].x, boxes[i][j].y, COLOR_BLACK);
    num_blocks--;
    
    if(num_blocks == SPUP && sp1 == 0){
      ball_set_dy(2*ball_get_dy());
      sp1 = 1;
    }
    
    if(i == ri && j == rj && count_bonus == 0)
      flag_bonus = 1;
    
    if(flag_bonus == 1){
      count_bonus++;     
      if(count_bonus == BONUS)
	flag_bonus = 2;
    }
  }
}

void block_step(void){  
  struct box* ball = ball_get_box();
  
  switch (game_get_state()) {
  case START:    
    boxes_initialize();
    break;

  case RUNNING:
    updown = 0;
    leftright = 0;
    
    int lu = hit(ball->x, ball->y);
    int ru = hit(ball->x + ball->width, ball->y);
    int ld = hit(ball->x, ball->y + ball->height);
    int rd = hit(ball->x + ball->width, ball->y + ball->height);
    
    if(lu) delete(ball->x, ball->y, ri, rj);
    if(ru) delete(ball->x + ball->width, ball->y, ri, rj);
    if(ld) delete(ball->x, ball->y + ball->height, ri, rj);
    if(rd) delete(ball->x + ball->width, ball->y + ball->height, ri, rj);

    if(lu || ru || ld || rd)
      brake_flag = 1;
    
    if(lu || ru)
      updown++;
    if(ld || rd)
      updown--;
    if(lu || ld)
      leftright++;
    if(ru || rd)
      leftright--;
    
    if(flag_bonus != 1){
      if(updown != 0)
	ball_set_dy(-(ball_get_dy()));
      if(leftright != 0)
	ball_set_dx(-(ball_get_dx()));
    }
    
    if(num_blocks <= 0){
      game_set_state(CLEAR);
      break;
    }

  case MISS:
    //何もしない．
    break;
    
  case DEAD:
    //何もしない．
    break;
    
  case RESTART:
    boxes_initialize();
    break;
    
  case CLEAR:
    //何もしない．
    break;
  }
  
}
