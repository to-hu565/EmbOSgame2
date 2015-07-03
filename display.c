#include "gba.h"
#include "color.h"
#include "game.h"
#include "8x8.til"

#define FONT_SIZE       8

static int flag_char;//0:消, 1:START, 2:CLEAR, 3:MISS!!

void
draw_char(hword *ptr, hword color, int code)
{
  hword   *p;
  int     i, j;
  unsigned char   *font = char8x8[code];
  
  for (i = 0; i < FONT_SIZE; i++) {
    p = ptr + LCD_WIDTH * i;
    for (j = FONT_SIZE - 1; j >= 0; j--, p++) {
      if (font[i] & (1 << j))
	*p = color;
    }
  }
}

void draw_display(int color)
{
  hword   *base, *d;
  int i,j;
  base = (hword*)VRAM;
  
  for(j = 0; j < LCD_HEIGHT; j++){
    d = base;
    for(i = 0; i < LCD_WIDTH; i++)
      *(d++) = color;
     base += LCD_WIDTH;
  }
}

void display_step(void)
{

  hword   *fb = (hword*)VRAM;
  int     i,x,y;
  
  /* Initialize LCD Control Register to use Mode 3. */
  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;

  //HP
  draw_char(fb + (LCD_WIDTH * 19 * 8) + 0 * 8, COLOR_WHITE, 72);
  draw_char(fb + (LCD_WIDTH * 19 * 8) + 1 * 8, COLOR_WHITE, 80);

  //STOCK
  draw_char(fb + (LCD_WIDTH * 19 * 8) + 21 * 8, COLOR_WHITE, 83);
  draw_char(fb + (LCD_WIDTH * 19 * 8) + 22 * 8, COLOR_WHITE, 84);
  draw_char(fb + (LCD_WIDTH * 19 * 8) + 23 * 8, COLOR_WHITE, 79);
  draw_char(fb + (LCD_WIDTH * 19 * 8) + 24 * 8, COLOR_WHITE, 67);
  draw_char(fb + (LCD_WIDTH * 19 * 8) + 25 * 8, COLOR_WHITE, 75);
  
  switch (game_get_state()) {
    
  case START:

    if(flag_char == 2){
      //GAME CLEAR
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 10 * 8, COLOR_BLACK, 71);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 11 * 8, COLOR_BLACK, 65);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 12 * 8, COLOR_BLACK, 77);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 13 * 8, COLOR_BLACK, 69);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 15 * 8, COLOR_BLACK, 67);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 16 * 8, COLOR_BLACK, 76);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 17 * 8, COLOR_BLACK, 69);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 18 * 8, COLOR_BLACK, 65);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 19 * 8, COLOR_BLACK, 82);
      flag_char = 0;      
    } 
    
    //GAME START
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 10 * 8, COLOR_WHITE, 71);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 11 * 8, COLOR_WHITE, 65);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 12 * 8, COLOR_WHITE, 77);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 13 * 8, COLOR_WHITE, 69);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 15 * 8, COLOR_WHITE, 83);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 16 * 8, COLOR_WHITE, 84);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 17 * 8, COLOR_WHITE, 65);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 18 * 8, COLOR_WHITE, 82);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 19 * 8, COLOR_WHITE, 84);    
    flag_char = 1; 
    break;
    
  case RUNNING:
    
    if(flag_char == 1){
      //GAME START
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 10 * 8, COLOR_BLACK, 71);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 11 * 8, COLOR_BLACK, 65);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 12 * 8, COLOR_BLACK, 77);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 13 * 8, COLOR_BLACK, 69);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 15 * 8, COLOR_BLACK, 83);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 16 * 8, COLOR_BLACK, 84);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 17 * 8, COLOR_BLACK, 65);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 18 * 8, COLOR_BLACK, 82);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 19 * 8, COLOR_BLACK, 84);
      flag_char = 0;
    }else if(flag_char == 3){
      //MISS!!
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 13 * 8, COLOR_BLACK, 77);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 14 * 8, COLOR_BLACK, 73);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 15 * 8, COLOR_BLACK, 83);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 16 * 8, COLOR_BLACK, 83);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 17 * 8, COLOR_BLACK, 19);
      flag_char = 0;
    }
    
    break;

  case MISS:
    //MISS!!
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 13 * 8, COLOR_WHITE, 77);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 14 * 8, COLOR_WHITE, 73);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 15 * 8, COLOR_WHITE, 83);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 16 * 8, COLOR_WHITE, 83);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 17 * 8, COLOR_WHITE, 19);
    flag_char = 3;
    break;
    
  case DEAD:
    //GAME OVER
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 10 * 8, COLOR_WHITE, 71);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 11 * 8, COLOR_WHITE, 65);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 12 * 8, COLOR_WHITE, 77);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 13 * 8, COLOR_WHITE, 69);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 15 * 8, COLOR_WHITE, 79);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 16 * 8, COLOR_WHITE, 86);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 17 * 8, COLOR_WHITE, 69);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 18 * 8, COLOR_WHITE, 82);
    flag_char = 1;
 
    break;
    
  case RESTART:

    if(flag_char == 1){
      //GAME OVER
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 10 * 8, COLOR_BLACK, 71);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 11 * 8, COLOR_BLACK, 65);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 12 * 8, COLOR_BLACK, 77);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 13 * 8, COLOR_BLACK, 69);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 15 * 8, COLOR_BLACK, 79);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 16 * 8, COLOR_BLACK, 86);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 17 * 8, COLOR_BLACK, 69);
      draw_char(fb + (LCD_WIDTH * 10 * 8) + 18 * 8, COLOR_BLACK, 82);
      flag_char = 0;
    }
    
    break;

  case CLEAR:
    //GAME CLEAR
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 10 * 8, COLOR_WHITE, 71);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 11 * 8, COLOR_WHITE, 65);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 12 * 8, COLOR_WHITE, 77);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 13 * 8, COLOR_WHITE, 69);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 15 * 8, COLOR_WHITE, 67);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 16 * 8, COLOR_WHITE, 76);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 17 * 8, COLOR_WHITE, 69);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 18 * 8, COLOR_WHITE, 65);
    draw_char(fb + (LCD_WIDTH * 10 * 8) + 19 * 8, COLOR_WHITE, 82); 
    flag_char = 2;    
    break;
  }
}
