#ifndef MEM_H
#define MEM_H

extern void accessInsMem(int addr[], int out[]);
extern void accessDataMem(int memReadSig, int memWriteSig, int addr[], int in[], int out[]);
extern void dispMem(void);
extern void initMem(void);

#endif