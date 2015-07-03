#include "gba.h"
#include "color.h"
#include "racket.h"
#include "ball.h"
#include "game.h"
#include "box.h"
#include "hp.h"

#define WIDTH 50
#define HEIGHT 5
#define X (LCD_WIDTH-WIDTH)/2
#define Y LCD_HEIGHT-10-HEIGHT
#define BOUND 2     //画面端
#define IN 2
#define OUT 2

struct box racket;

int racket_get_x(void) { return racket.x; }

int racket_get_w(void) { return racket.width; }

void racket_hit_barrage(void) {
  int x = racket.x;
  int y = racket.y;
  hp_damage();//体力減少
  //ラケット短くなーる
  draw_box(&racket, x ,y, COLOR_BLACK);
  racket_set_w(racket.width-2);
  draw_box(&racket, x ,y, COLOR_WHITE);
}

void racket_set_w(int new_w) {
  if(new_w > 0)
    racket.width = new_w;
}

void racket_initialize(){
  racket.x = X;
  racket.y = Y;
  racket.width = WIDTH;
  racket.height = HEIGHT;
  int x = racket.x;
  int y = racket.y;
  draw_box(&racket, x ,y, COLOR_WHITE);
}


void racket_step(){
  
  int x = racket.x;
  int y = racket.y;
  int key = gba_register(KEY_STATUS);
  
  hword color = COLOR_WHITE;
  
  switch (game_get_state()) {
  case START:
    
    draw_box(&racket, x, y, COLOR_BLACK);
    racket_initialize();
    
    break;
    
  case RUNNING:
    
    if(cross(ball_get_box(), &racket)){
      /*
      hp_damage();//体力減少
      //ラケット短くなーる
      draw_box(&racket, x ,y, COLOR_BLACK);
      racket_set_w(racket.width-5);
      draw_box(&racket, x ,y, COLOR_WHITE);
      */
      ball_set_dy(-(ball_get_dy()));
    }
    
    if(cross_end_r(ball_get_box(), &racket))
      ball_set_dx(ball_get_dx()+1);
    
    if(cross_end_l(ball_get_box(), &racket))
      ball_set_dx(ball_get_dx()-1);
    
    if(cross_x(ball_get_box(), &racket, OUT))
      ball_set_dx(-(ball_get_dx()));
    
    if(cross_in(ball_get_box(), &racket, IN))
      move_box(ball_get_box(), ball_get_x(), ball_get_y() - 2, COLOR_WHITE);  

    
    if (! (key & KEY_LEFT)){
      if(x <= BOUND){
	;;
      }else{
	x -= 2;
	move_box(&racket, x, y , color);
      }
    }
    
    if (! (key & KEY_RIGHT)){
      if(x >= LCD_WIDTH - BOUND - racket.width){
	;;
      }else{
	x += 2;
	move_box(&racket, x, y, color);
      }
    }
    
    break;
    
  case MISS:
    // ラケットを初期位置、初期状態に戻す
    draw_box(&racket, x, y, COLOR_BLACK);
    racket_initialize();
    break;
    
  case DEAD:
    //未実装：現在地からラケットが弾ける
    draw_box(&racket, x, y, COLOR_BLACK);
    break;
    
  case RESTART:
    /* ラケットを初期位置、初期状態に戻す*/
    draw_box(&racket, x, y, COLOR_BLACK);
    racket_initialize();
    break;

  case CLEAR:
    //何もしない．
    break;
  }
  
}
