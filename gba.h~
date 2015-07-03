//
// G B A . H
//
// Include header file for GCC-GBA programming (for chapter-3)
//
// June 25, 2003 by Wataru Nishida (http://www.wnishida.com)
//

#ifndef _GBA_H_
#define _GBA_H_

typedef unsigned short hword;		// Half word (2 bytes)
typedef unsigned char  byte;		// Byte

#define BG_PALETTE	0x05000000	// Background palette RAM
#define OBJ_PALETTE	0x05000200	// Object palette RAM
#define VRAM		0x06000000	// Video RAM frame buffer
#define VRAM_TILE(n)	(VRAM+n*0x4000)	// Tile data base address
#define VRAM_MAP(n)	(VRAM+n*0x0800)	// Map data base address

#define LCD_WIDTH	240		// 240 dots / horizontal line
#define LCD_HEIGHT	160		// 160 dots / vertical line
#define LCD_RWIDTH	30		// Real width in tile
#define LCD_RHEIGHT	20		// Real height in tile
#define LCD_VWIDTH	32		// Virtual width in tile
#define LCD_VHEIGHT	32		// Virtual height in tile
#define LCD_TILE_BYTE	(8 * 8)		// Byte size of single tile
#define LCD_TILE_HWORD	(8 * 4)		// Half word size of single tile

#define LCD_PAL_COLORS	256		// Total color number per palette
#define BGR(r, g, b)	(((b) << 10) + ((g) << 5) + (r))

#define gba_register(p)	*((volatile hword*) p)	// I/O register handling macro
#define IOBASE		0x04000000	// I/O register base address

#define LCD_CTRL	(IOBASE + 0)	// LCD control
#define   LCD_BG0EN	0x0100		//   Enable BG0
#define   LCD_BG1EN	0x0200		//   Enable BG1
#define   LCD_BG2EN	0x0400		//   Enable BG2
#define   LCD_BG3EN	0x0800		//   Enable BG3
#define   LCD_OBJEN	0x1000		//   Enable OBJ
#define   LCD_OBJMAP2D	0		//   OBJ 2D mapping
#define   LCD_OBJMAP1D	0x0040		//   OBJ 1D mapping
#define   LCD_MODE0	0		//   Video mode 0
#define   LCD_MODE1	1		//   Video mode 1
#define   LCD_MODE2	2		//   Video mode 2
#define   LCD_MODE3	3		//   Video mode 3
#define   LCD_MODE4	4		//   Video mode 4
#define   LCD_MODE5	5		//   Video mode 5
#define LCD_BG0		(IOBASE + 8)	// LCD BG0 control
#define LCD_BG1		(IOBASE + 10)	// LCD BG1 control
#define LCD_BG2		(IOBASE + 12)	// LCD BG2 control
#define LCD_BG3		(IOBASE + 14)	// LCD BG3 control
#define   LCD_SIZE3232	0x0000		//   BG size 32 x 32 tiles
#define   LCD_SIZE6432	0x4000		//   BG size 64 x 32 tiles
#define   LCD_SIZE3264	0x8000		//   BG size 32 x 64 tiles
#define   LCD_SIZE6464	0xC000		//   BG size 64 x 64 tiles
#define   LCD_COLOR16	0		//   BG 16 colors x 16 palettes
#define   LCD_COLOR256	0x0080		//   BG 256 colors x 1 palette
#define   LCD_BGTILE(n)	(n << 2)	//   BG tile base block #
#define   LCD_BGMAP(n)	(n << 8)	//   BG map base block #
#define LCD_BG0_HOFFSET	(IOBASE + 16)	// LCD BG0 Horizontal offset
#define LCD_BG0_VOFFSET	(IOBASE + 18)	// LCD BG0 Vertical offset
#define LCD_BG1_HOFFSET	(IOBASE + 20)	// LCD BG1 Horizontal offset
#define LCD_BG1_VOFFSET	(IOBASE + 22)	// LCD BG1 Vertical offset
#define LCD_BG2_HOFFSET	(IOBASE + 24)	// LCD BG2 Horizontal offset
#define LCD_BG2_VOFFSET	(IOBASE + 26)	// LCD BG2 Vertical offset
#define LCD_BG3_HOFFSET	(IOBASE + 28)	// LCD BG3 Horizontal offset
#define LCD_BG3_VOFFSET	(IOBASE + 30)	// LCD BG3 Vertical offset

typedef struct {
  hword* map;	// Map data pointer
  hword* tile;	// Tile data pointer
  int x, y;	// Position
 } screen;

#define BG_BLACK	0		// BG color: black
#define BG_WHITE	1		// BG color: white

#define BG_TEXT1	0		// Text page 1 background
#define BG_TEXT2	1		// Text page 2 background
#define BG_GRAPHIC	2		// Graphic background

#define KEY_STATUS	(IOBASE + 304)	// Key status
#define KEY_INTCNT	(IOBASE + 306)	// Key interrupt controller
#define   KEY_INTAND	0x8000		//   Mode flag (0: OR, 1:AND)
#define   KEY_INTEN	0x4000		//   Interrupt request enable
#define   KEY_L		0x200		//   L
#define   KEY_R		0x100		//   R
#define   KEY_DOWN	0x080		//   Down
#define   KEY_UP	0x040		//   Up
#define   KEY_LEFT	0x020		//   Left
#define   KEY_RIGHT	0x010		//   Right
#define   KEY_START	0x008		//   Start
#define   KEY_SELECT	0x004		//   Select
#define   KEY_B		0x002		//   B
#define   KEY_A		0x001		//   A
#define   KEY_ALL	0x3FF		// All key bits

#define TMR_COUNT0	(IOBASE + 256)	// Timer 0 counter
#define TMR_CTRL0	(IOBASE + 258)	// Timer 0 control
#define TMR_COUNT1	(IOBASE + 260)	// Timer 1 counter
#define TMR_CTRL1	(IOBASE + 262)	// Timer 1 control
#define TMR_COUNT2	(IOBASE + 264)	// Timer 2 counter
#define TMR_CTRL2	(IOBASE + 266)	// Timer 2 control
#define TMR_COUNT3	(IOBASE + 268)	// Timer 3 counter
#define TMR_CTRL3	(IOBASE + 270)	// Timer 3 control

#define   TMR_ENABLE	0x0080		// Timer enable
#define   TMR_INTREN	0x0040		// Timer interrupt request enable
#define   TMR_CASCADE	0x0004		// Cascade mode (non prescalar mode)
					// Prescalar
#define   TMR_1CLOCK	0x0000		//    1 clock
#define   TMR_64CLOCK	0x0001		//   64 clocks
#define   TMR_256CLOCK	0x0002		//  256 clocks
#define   TMR_1024CLOCK	0x0003		// 1024 clocks

#define INT_VECTOR	0x03007FFC	// Interrupt address in internal WRAM
#define INT_IME		(IOBASE + 520)	// IME: Interrupt Master Enable
#define   INT_IME_OFF	0		//   Disable
#define   INT_IME_ON	1		//   Enable
#define INT_IE		(IOBASE + 512)	// IE: Interrupt Enable
#define INT_IF		(IOBASE + 514)	// IF: Interrupt request Flag
#define   INT_PAK	0x2000		//   Game pak
#define   INT_KEY	0x1000		//   Key
#define   INT_DMA3	0x0800		//   DMA ch3
#define   INT_DMA2	0x0400		//   DMA ch2
#define   INT_DMA1	0x0200		//   DMA ch1
#define   INT_DMA0	0x0100		//   DMA ch0
#define   INT_SIO	0x0080		//   Serial I/O
#define   INT_TMR3	0x0040		//   Timer ch3
#define   INT_TMR2	0x0020		//   Timer ch2
#define   INT_TMR1	0x0010		//   Timer ch1
#define   INT_TMR0	0x0008		//   Timer ch0
#define   INT_VCOUNT	0x0004		//   V-counter matching
#define   INT_HBLANK	0x0002		//   Horizontal blanking
#define   INT_VBLANK	0x0001		//   Vertical blanking

// Priority index

#define PRIORITY_1ST    0		// 1st priority
#define PRIORITY_2ND    1		// 2nd priority
#define PRIORITY_3RD    2		// 3rd priority
#define PRIORITY_4TH    3		// 4th priority

#endif
