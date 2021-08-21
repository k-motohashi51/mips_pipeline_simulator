#include <string.h>
#include <stdio.h>
#include "../../../inc/reg.h"
#include "../../../inc/converter.h"
#include "../../../inc/error.h"
#include "../../../inc/def.h"

#define REG_SIZE 32

static int reg[REG_SIZE][WIDTH];

void initReg(void);
void dispReg(void);
void accessReg(int regWriteSig, int regIndex[], int in[], int out[]);
static void readReg(int regIndex[], int data[]);
static void writeReg(int regIndex[], int data[]);

/* レジスタの初期状態を設定 */
void initReg(void) {

    /*************************************************/
    /*                 sw $s1, 2($s0)                */
    /* +--------+-------+-------+------------------+ */
    /* |   op   |  rs   |  rt   |       addr       | */
    /* | 100011 | 10000 | 10001 | 0000000000000010 | */
    /* +--------+-------+-------+------------------+ */
    /*************************************************/

    /*******************************************************/
    /*                 sub $t0, $t1, $t2                   */
    /* +--------+-------+-------+-------+-------+--------+ */
    /* |   op   |  rs   |  rt   |  rd   | shamt | funct  | */
    /* | 000000 | 01000 | 01001 | 01010 | 00000 | 100010 | */
    /* +--------+-------+-------+-------+-------+--------+ */
    /*******************************************************/

    memset(reg, 0, sizeof(reg));

    int t0[WIDTH] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1
    };

    int t1[WIDTH] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0
    };

    memcpy(reg[0b01000], t0, WIDTH * sizeof(int));

    memcpy(reg[0b01001], t1, WIDTH * sizeof(int));

}

/* デバッグ用 */
void dispReg(void) {

    int index;

    printf("Register\n");

    for (int i = 0; i < 8; i++) {
        printf("+-----------------");
    }
    printf("+\n");

    for (int i = 0; i < 4; i++) {
        printf("| ");
        for (int j = 0; j < 8; j++) {
            index = 8 * i + j;
            printf("[%2d]:0x%08x", index, binToDec(WIDTH, reg[index]));
            printf(" | ");
        }
        printf("\n");
    }

    for (int i = 0; i < 8; i++) {
        printf("+-----------------");
    }
    printf("+\n\n");

}

/* 外部へのインターフェース */
void accessReg(int regWriteSig, int regIndex[], int in[], int out[]) {

    // レジスタからデータ読み込み
    if (regWriteSig == 0) {
        readReg(regIndex, out);
        return;
    }

    if (regWriteSig == 1) {
        writeReg(regIndex, in);
        return;
    }

    ERROR("制御信号regWriteが予期しない値です\n");

}

/* レジスタからデータを読み込む */
static void readReg(int regIndex[], int data[]) {

    //TODO:いい感じのマクロ
    int decRegIndex = binToDec(5, regIndex);

    memcpy(data, reg[decRegIndex], WIDTH * sizeof(int));

}

/* レジスタにデータを書き込む */
static void writeReg(int regIndex[], int data[]) {

    //TODO:いい感じのマクロ
    int decRegIndex = binToDec(5, regIndex);

    memcpy(reg[decRegIndex], data, WIDTH * sizeof(int));

}
