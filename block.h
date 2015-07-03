#ifndef _BLOCK_H_
#define _BLOCK_H_


extern void block_step(void);

extern int brake_flag_get(void);
extern void brake_flag_reset(void);
extern int brake_get_x(void);
extern int brake_get_y(void);
extern int ball_bonus_state(void);

#endif
