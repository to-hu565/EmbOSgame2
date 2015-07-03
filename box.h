#ifndef _BOX_H_
#define _BOX_H_

#define COLOR_WHITE     BGR(31, 31, 31)
#define COLOR_BLACK     0

struct box {
  int x, y;//座標
  int width, height;//大きさ
  int dx, dy;//速度
  //int exi;//block存在
};

extern void draw_box(struct box *b, int x, int y, hword color);
extern void move_box(struct box *b, int x, int y, hword color);
extern int cross(struct box *b1, struct box *b2);
extern int cross_x(struct box *b1, struct box *b2, int out);
extern int cross_y(struct box *b1, struct box *b2);
extern int cross_in(struct box *b1, struct box *b2, int in);
extern int cross_end_r(struct box *b1, struct box *b2);
extern int cross_end_l(struct box *b1, struct box *b2);

#endif
