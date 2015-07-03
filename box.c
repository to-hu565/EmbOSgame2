#include "gba.h"
#include "color.h"
#include "box.h"

void
draw_box(struct box *b, int x, int y, hword color)
{
  hword   *base, *d;
  int     w, h;
  
  /* Base point is at (x, y). */
  base = (hword*)VRAM + LCD_WIDTH * y + x;
  
  /* Draw ball from (x, y). */
  for (h = b->height; h > 0; h--) {
    d = base;
    for (w = b->width; w > 0; w--)
      *(d++) = color;
    base += LCD_WIDTH;
  }
  
  /* Set the current position. */
  b->x = x;
  b->y = y;
}

void
move_box(struct box *b, int x, int y, hword color)
{
  draw_box(b, b->x, b->y, COLOR_BLACK);
  draw_box(b, x, y, color);
}


int cross(struct box *b1, struct box *b2){
  //b1:ボール, b2:相手
  int b1x = b1->x;
  int b1y = b1->y;
  int b1w = b1->width;
  int b1h = b1->height;
  int b2x = b2->x;
  int b2y = b2->y;
  int b2w = b2->width;
  int b2h = b2->height;
  
  if((b2x <= b1x + b1w) && (b2x + b2w >= b1x) &&
     (b2y <= b1y + b1h) && (b2y + b2h >= b1y) ){
    return 1;
  } else {
    return 0;
  }
}

int cross_x(struct box *b1, struct box *b2, int out){
  //ボールより１回り大きい範囲で
  int b1x = b1->x - out;
  int b1y = b1->y - out;
  int b1w = b1->width + out;
  int b1h = b1->height + out;
  int b2x = b2->x;
  int b2y = b2->y;
  int b2w = b2->width;
  int b2h = b2->height;
  
  if((b2x <= b1x + b1w) && (b2x + b2w >= b1x) &&
     (b2y <= b1y + b1h) && (b2y + b2h >= b1y) &&
     ( ((b1x + b1w  - b2x > b2y + b2h - b1y) && (b1x < b2x)) ||
       ((b2x + b2w - b1x > b2y + b2h - b1y) && (b1x + b1w > b2x + b2w)) )){
    return 1;
  } else {
    return 0;
  }
}

int cross_in(struct box *b1, struct box *b2, int in){
  //ボールが埋まった時の判定
  int b1x = b1->x;
  int b1y = b1->y;
  int b1w = b1->width;
  int b1h = b1->height;
  int b2x = b2->x + in;
  int b2y = b2->y + in;
  int b2w = b2->width - in;
  int b2h = b2->height - in;
  
  if((b2x <= b1x + b1w) && (b2x + b2w >= b1x) &&
     (b2y <= b1y + b1h) && (b2y + b2h >= b1y) ){
    return 1;
  } else {
    return 0;
  }
}

int cross_end_r(struct box *b1, struct box *b2){
  //右端での当たり判定
  int b1x = b1->x;
  int b1y = b1->y;
  int b1w = b1->width;
  int b1h = b1->height;
  int b2w = (b2->width / 4);
  int b2h = b2->height;
  int b2x = b2->x + 3*b2w;
  int b2y = b2->y;
 
  
  if((b2x <= b1x + b1w) && (b2x + b2w >= b1x) &&
     (b2y <= b1y + b1h) && (b2y + b2h >= b1y) ){
    return 1;
  } else {
    return 0;
  }
}

int cross_end_l(struct box *b1, struct box *b2){
  //左端での当たり判定
  int b1x = b1->x;
  int b1y = b1->y;
  int b1w = b1->width;
  int b1h = b1->height;
  int b2w = (b2->width / 4);
  int b2h = b2->height;
  int b2x = b2->x;
  int b2y = b2->y;
  
  if((b2x <= b1x + b1w) && (b2x + b2w >= b1x) &&
     (b2y <= b1y + b1h) && (b2y + b2h >= b1y) ){
    return 1;
  } else {
    return 0;
  }
}
