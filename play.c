#include "gba4.h"
#include "color.h"
#include "ball.h"
#include "racket.h"
#include "game.h"
#include "hp.h"

#define INTERVAL        160

void delay(hword val){
  val += gba_register(TMR_COUNT0);
  while (val != gba_register(TMR_COUNT0))
    ;

}

/*
void delay1(hword val){
  wait_until(gba_register(TMR_COUNT0) + val);
}

void wait_until(hword time){
  while (time != gba_register(TMR_COUNT0))
    ;
}
*/

void wait_until_vblank(void) {
  while ((gba_register(LCD_STATUS) & 1) == 0)
    ;
}

void wait_while_vblank(void) {
  while ((gba_register(LCD_STATUS) & 1))
    ;
}

main(){

  /* Initialize LCD Control Register to use Mode 3. */
  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;
  
  /*timer initialize*/
  gba_register(TMR_COUNT0) = 0;
  gba_register(TMR_CTRL0) = TMR_ENABLE + TMR_1024CLOCK;

  while(1){

    wait_until_vblank();  // 垂直ブランク期間になるまで待つ
    
    display_step();
    
    ball_step();
    
    racket_step();

    block_step();

    hp_step();

    barrage_step();
    
    game_step();
    
    //delay1(INTERVAL);

    wait_while_vblank();  // 垂直ブランク期間が終るまで待つ
    
  }
  
}
