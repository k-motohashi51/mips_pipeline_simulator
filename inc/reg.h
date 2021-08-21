#ifndef REG_H
#define REG_H

#define REG_SIZE 32
#define REG_WIDTH 32

extern void accessReg(int regWriteSig, int regIndex[], int in[], int out[]);
extern void dispReg(void);
extern void initReg(void);

#endif