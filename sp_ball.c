// b a l l . c

#include "gba.h"
#include "screen.h"
#include "sprite.h"

#define MAX_BALLS	12

// Empty interrupt handler

void int_handler(void) {
 }

int main() {
  int i, cnum;
  extern character greenball[];

// Initialize screen

  init_screen();
  
  // Initialize sprite

  init_sprite();

  // Draw multiple balls

  cnum = sprite_register(greenball, 4);
  for (i = 0; i < MAX_BALLS; i++) {
    sprite_setup(i, OBJ_16x16, PRIORITY_2ND, cnum);
    sprite_move(i, LCD_WIDTH / MAX_BALLS * i, LCD_HEIGHT / MAX_BALLS * i);
    sprite_display(i, OBJ_TURNON);
   }

  // Loop forever

  while (1) {
   }
 }
