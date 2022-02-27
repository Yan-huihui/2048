#ifndef __GAME_
#define __GAME_

extern int getch(void);
extern void print2048(int (*arry)[4], int rows);
extern void remove_right(int (*arry)[4],int rows);
extern void remove_left(int (*arry)[4],int rows);
extern void remove_up(int (*arry)[4],int rows);
extern void remove_down(int (*arry)[4],int rows);
extern int isSame(int (*arry)[4]);
extern int  winOrLoseStop(int (*arry)[4]);
extern int randomLess4(void);
extern int random2or4(void);
extern int system(const char *command);
extern int start(void);
extern int copyarry(int (*des)[4], int (*src)[4]);
extern int isSame_OldAndNewArry(int (*old)[4], int (*new)[4]);
#endif
