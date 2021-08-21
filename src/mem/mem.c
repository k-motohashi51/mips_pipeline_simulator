#include <stdio.h>
#include <string.h>
#include "../../inc/mem.h"
#include "../../inc/error.h"
#include "../../inc/converter.h"
#include "../../inc/def.h"

#define MEM_SIZE 32
#define MEM_WIDTH 8

static int mem[MEM_SIZE][MEM_WIDTH];

void dispMem(void);
void initMem(void);
void accessInsMem(int addr[], int out[]);
void accessDataMem(int memReadSig, int memWriteSig, int addr[], int in[], int out[]);
static void readMem(int addr[], int data[]);
static void writeMem(int addr[], int data[]);

void initMem(void) {

    memset(mem, 0, sizeof(mem));

    int ins[WIDTH / MEM_WIDTH][MEM_WIDTH] = {
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 1},
        {0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 1, 0}
    };

    for (int i = 0; i < WIDTH / MEM_WIDTH; i++) {
        memcpy(mem[i], ins[i], MEM_WIDTH * sizeof(int));
    }
}

void accessInsMem(int addr[], int out[]) {

    readMem(addr, out);

}

void accessDataMem(int memReadSig, int memWriteSig, int addr[], int in[], int out[]) {

    // R形式なのでメモリにアクセスしない
    if (memReadSig == 0 && memWriteSig == 0) {
        return;
    }

    // メモリからデータを読み込む
    if (memReadSig == 1) {
        readMem(addr, out);
        return;
    }

    // メモリにデータを書き込む
    if (memWriteSig == 1) {
        writeMem(addr, in);
        return;
    }

    ERROR("制御信号memRead、memWriteのいずれかが予期しない値です");

}

/* メモリからデータを読み込む */
static void readMem(int addr[], int data[]) {

    int decAddr = binToDec(WIDTH, addr);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < MEM_WIDTH; j++) {
            data[i * MEM_WIDTH + j] = mem[decAddr + i][j];
        }
    }

}

/* メモリにデータを書き込む */
static void writeMem(int addr[], int data[]) {
    
    int decAddr = binToDec(WIDTH, addr);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < MEM_WIDTH; j++) {
            mem[decAddr + i][j] = data[i * MEM_WIDTH + j];
        }
    }

}

/* デバッグ用 */
void dispMem(void) {

    printf("\nMemory\n");
    printf("+-----------------------------------");
    printf("-----------------------------------+\n");

    for (int i = 0; i < MEM_SIZE / MEM_WIDTH; i++) {
        printf("| %3d <+%3d> : ", 8 * i, 8 * i);
        for (int j = 0; j < MEM_WIDTH; j++) {
            printf("0x%02x", binToDec(MEM_WIDTH, mem[8 * i + j]));
            printf("   ");
        }
        printf("|\n");
    }
    
    printf("+-----------------------------------");
    printf("-----------------------------------+\n\n");

}
