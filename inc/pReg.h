#ifndef PREG_H
#define PREG_H

#include "ctrl.h"
#include "def.h"

typedef struct {
    int nextPc[WIDTH];
    int ins[WIDTH];
} IFID_t;

typedef struct {
    WBCtrlSig_t  wbCtrlSig;
    MEMCtrlSig_t memCtrlSig;
    EXCtrlSig_t  exCtrlSig;
    int nextPc[WIDTH];
    int data1[WIDTH];
    int data2[WIDTH];
    int immd[WIDTH];
    int rt[RT_WIDTH];
    int rd[RD_WIDTH];
} IDEX_t;

typedef struct {
    WBCtrlSig_t  wbCtrlSig;
    MEMCtrlSig_t memCtrlSig;
    int nextPc[WIDTH];
    int jumpPc[WIDTH];
    int isZero;
    int result[WIDTH];
    int writeMemData[WIDTH];
    int writeRegIndex[RT_WIDTH];
} EXMEM_t;

typedef struct {
    WBCtrlSig_t wbCtrlSig;
    int data[WIDTH];
    int aluResult[WIDTH];
    int writeRegIndex[RT_WIDTH];
} MEMWB_t;

#endif