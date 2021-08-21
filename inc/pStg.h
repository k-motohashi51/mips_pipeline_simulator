#ifndef PSTG_H
#define PSTG_H

#include "pReg.h"

void IF(int pc[], IFID_t*);
void ID(IFID_t*, IDEX_t*);
void EX(IDEX_t*, EXMEM_t*);
void MEM(EXMEM_t*, MEMWB_t*, int nextPc[]);
void WB(MEMWB_t *);

#endif