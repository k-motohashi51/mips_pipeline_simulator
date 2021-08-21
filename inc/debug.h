#ifndef DEBUG_H
#define DEBUG_H

#include "pReg.h"

extern void dispPc(int pc[]);
extern void dispIFID(IFID_t);
extern void dispIDEX(IDEX_t);
extern void dispEXMEM(EXMEM_t);
extern void dispMEMWB(MEMWB_t);

#endif