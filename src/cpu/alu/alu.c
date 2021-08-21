#include <string.h>
#include "../../../inc/converter.h"
#include "../../../inc/ctrl.h"
#include "../../../inc/error.h"
#include "../../../inc/def.h"

void alu(int aluCtrlSig[], int src1[], int src2[], int dst[], int* isZero);
static void aluAnd(int src1[], int src2[], int dst[]);
static void aluOr(int src1[], int src2[], int dst[]);
static void aluAdd(int src1[], int src2[], int dst[]);
static void aluSub(int src1[], int src2[], int dst[]);
static void aluSlt(int src1[], int src2[], int dst[]);
static void aluNor(int src1[], int src2[], int dst[]);

/* ALU(外部とのインターフェース) */
void alu(int aluCtrlSig[], int src1[], int src2[], int dst[], int* isZero) {

    int decSig = binToDec(ALU_CTRL_SIG_WIDTH, aluCtrlSig);

    switch (decSig) {
        case ALU_CTRL_SIG_AND:   aluAnd(src1, src2, dst);    break;
        case ALU_CTRL_SIG_OR:    aluOr(src1, src2, dst);     break;
        case ALU_CTRL_SIG_ADD:   aluAdd(src1, src2, dst);    break;
        case ALU_CTRL_SIG_SUB:   aluSub(src1, src2, dst);    break;
        case ALU_CTRL_SIG_SLT:   aluSlt(src1, src2, dst);    break;
        case ALU_CTRL_SIG_NOR:   aluNor(src1, src2, dst);    break;
        default:    ERROR("ALU制御信号が予期しない値です");
    }

    *isZero = (binToDec(WIDTH, dst) == 0) ? 1 : 0;

}

static void aluAnd(int src1[], int src2[], int dst[]) {

    for (int i = 0; i < WIDTH; i++) {
        dst[i] = src1[i] * src2[i];
    }
    
}

static void aluOr(int src1[], int src2[], int dst[]) {

    for (int i = 0; i < WIDTH; i++) {
        dst[i] = (src1[i] + src2[i] > 0) ? 1 : 0;
    }

}

static void aluAdd(int src1[], int src2[], int dst[]) {

    decToBin(WIDTH, binToDec(WIDTH, src1) + binToDec(WIDTH, src2), dst);

}

static void aluSub(int src1[], int src2[], int dst[]) {

    decToBin(WIDTH, binToDec(WIDTH, src1) - binToDec(WIDTH, src2), dst);

}

static void aluSlt(int src1[], int src2[], int dst[]) {

    if (binToDec(WIDTH, src1) < binToDec(WIDTH, src2)) {
        decToBin(WIDTH, 1, dst);
    } else {
        decToBin(WIDTH, 0, dst);
    }
    
} 

static void aluNor(int src1[], int src2[], int dst[]) {

    aluOr(src1, src2, dst);

    for (int i = 0; i < WIDTH; i++) {
        dst[i] = (dst[i] == 0) ? 1 : 0;
    }

}