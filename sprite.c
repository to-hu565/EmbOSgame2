//
// s p r i t e . c
//
// Sprite driver
//
// July 27, 2003 by Wataru Nishida (http://www.skyfree.org)
//

#include "gba.h"

// External OBJ palette data

extern
hword obj_palette[];		// OBJ palette data

// Global variables

static int sprites = 0;		// Total number of sprites
static int next_char = 0;	// Next character number to be written
				// (32 bytes/character)
// Setup sprite

void sprite_setup(int snum, int shape, int priority, int cnum) {
  int i, j;
  sprite* sp;

  sp = (sprite*) OAM; sp += snum;
  sp->attr0 = OBJ_COLOR_256 + OBJ_SWT_TURNOFF;
  sp->attr1 = 0;
  sp->attr2 = ((priority & 3) << 10);
  sp->attr2 |= (cnum & OBJ_CHAR_MASK);
  sp->padd  = 0;

  i = shape / 4; sp->attr0 |= (i << 14);
  j = shape % 4; sp->attr1 |= (j << 14);
 }

// Control sprite display

void sprite_display(int snum, int swt) {
  sprite* sp;

  sp = (sprite*) OAM; sp += snum;
  if (swt)
    sp->attr0 &= ~OBJ_SWITCH_MASK;
  else
    sp->attr0 |= OBJ_SWT_TURNOFF;
 }

// Move sprite

void sprite_move(int snum, int x, int y) {
  sprite* sp;

  sp = (sprite*) OAM; sp += snum;
  sp->attr1 &= ~OBJ_X_MASK;
  sp->attr1 |= (x & OBJ_X_MASK);
  sp->attr0 &= ~OBJ_Y_MASK;
  sp->attr0 |= (y & OBJ_Y_MASK);
 }

// Register sprite

int sprite_register(character* ch, int size) {
  int i, j, start;
  character* ptr;

  start = next_char;
  if ((start + (size * 2)) > OBJ_MAX_CHARS)
    return -1;
  ptr = (character*) OBJ_CHAR_TILE;
  ptr += (next_char / 2);
  for (i = 0; i < size; i++) {
    for (j = 0; j < 32; j++)
      ptr->data[ j ] = ch[ i ].data[ j ];
    ptr++;
    next_char += 2;
   }
  sprites++;
  return start;
 }

// Initialize sprite module

void init_sprite(void) {
  int i;
  hword* pal = (hword*) OBJ_PALETTE;

  // Initialize OBJ palettes

  for (i = 0; i < LCD_PAL_COLORS; i++)
    *pal++ = obj_palette[ i ];

  // Initialize sprites

  for (i = 0; i < OBJ_MAX_SPRITES; i++)
    sprite_setup(i, OBJ_8x8, PRIORITY_3RD, 0);

  // Turn on OBJ screen!

  gba_register(LCD_CTRL) |= LCD_OBJEN + LCD_OBJMAP1D;
 }
