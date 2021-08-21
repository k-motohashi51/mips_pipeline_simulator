#include <string.h>
#include "../../inc/mem.h"
#include "../../inc/reg.h"
#include "../../inc/converter.h"
#include "../../inc/tool.h"
#include "../../inc/ctrl.h"
#include "../../inc/alu.h"
#include "../../inc/def.h"
#include "../../inc/pStg.h"

#define RS_OFFSET (OP_WIDTH)
#define RT_OFFSET (RS_OFFSET + RS_WIDTH)
#define RD_OFFSET (RT_OFFSET + RT_WIDTH)
#define SHAMT_OFFSET (RD_OFFSET + RD_WIDTH)
#define FUNCT_OFFSET (SHAMT_OFFSET + SHAMT_WIDTH)
#define IMMD_OFFSET (RD_OFFSET)

/* Instruction Fetch Stage */
void IF(int pc[], IFID_t* ifid) {

    int a[WIDTH];

    // メモリから命令をフェッチ
    accessInsMem(pc, ifid->ins);

    // 次のpcを算出
    decToBin(WIDTH, 4, a);
    add(pc, a, ifid->nextPc);

}

/* Instruction Decode Stage */
void ID(IFID_t* ifid, IDEX_t* idex) {

    int op[OP_WIDTH];
    int rs[RS_WIDTH];
    int rt[RT_WIDTH];
    int rd[RD_WIDTH];
    int immd[IMMD_WIDTH];
    ctrlSig_t ctrlSig;

    int regWriteSig = 0;
    int buf[WIDTH] = {0};

    // 各フィールドの値を読み出す
    memcpy(op, ifid->ins, OP_WIDTH * sizeof(int));
    memcpy(rs, &(ifid->ins[RS_OFFSET]), RS_WIDTH * sizeof(int));
    memcpy(rt, &(ifid->ins[RT_OFFSET]), RT_WIDTH * sizeof(int));
    memcpy(rd, &(ifid->ins[RD_OFFSET]), RD_WIDTH * sizeof(int));
    memcpy(immd, &(ifid->ins[IMMD_OFFSET]), IMMD_WIDTH * sizeof(int));

    // 制御信号の生成
    mainCtrl(op, &ctrlSig);

    // レジスタから演算に使用するデータを読み出す
    accessReg(regWriteSig, rs, buf, idex->data1);
    accessReg(regWriteSig, rt, buf, idex->data2);

    // 後のステージで使用する制御信号群を受け渡す
    idex->wbCtrlSig = ctrlSig.wbCtrlSig;
    idex->memCtrlSig = ctrlSig.memCtrlSig;
    idex->exCtrlSig = ctrlSig.exCtrlSig;
    
    // その他の受け渡し
    memcpy(idex->nextPc, ifid->nextPc, WIDTH * sizeof(int));
    memcpy(idex->rt, rt, RT_WIDTH * sizeof(int));
    memcpy(idex->rd, rd, RD_WIDTH * sizeof(int));
    extendSign(immd, IMMD_WIDTH, idex->immd, WIDTH);

}

void EX(IDEX_t* idex, EXMEM_t* exmem) {

    int shiftedImmd[WIDTH];
    int aluCtrlSig[ALU_CTRL_SIG_WIDTH];
    int aluInput2[WIDTH];
    int extractedImmd[FUNCT_WIDTH];

    // 分岐先アドレスを算出する
    shift(idex->immd, shiftedImmd, 2);
    add(idex->nextPc, shiftedImmd, exmem->jumpPc);

    // ALU制御信号を生成する
    memcpy(extractedImmd, &(idex->immd[FUNCT_OFFSET]), FUNCT_WIDTH * sizeof(int));
    aluCtrl(idex->exCtrlSig.aluOp, extractedImmd, aluCtrlSig);

    // ALUで計算を行い、結果を求める
    mux(idex->exCtrlSig.aluSrc, idex->data2, idex->immd, aluInput2, WIDTH);
    alu(aluCtrlSig, idex->data1, aluInput2, exmem->result, &(exmem->isZero));

    // レジスタへ書き込むデータの決定
    mux(idex->exCtrlSig.regDst, idex->rt, idex->rd, exmem->writeRegIndex, RT_WIDTH);

    // 後のステージで使用する制御信号群を受け渡す
    exmem->wbCtrlSig = idex->wbCtrlSig;
    exmem->memCtrlSig = idex->memCtrlSig;

    // その他の受け渡し
    memcpy(exmem->nextPc, idex->nextPc, WIDTH * sizeof(int));
    memcpy(exmem->writeMemData, idex->data2, WIDTH * sizeof(int));

}

void MEM(EXMEM_t* exmem, MEMWB_t* memwb, int nextPc[]) {

    // 制御信号pcSrcの生成
    exmem->memCtrlSig.pcSrc = and(exmem->memCtrlSig.branch, exmem->isZero);

    // jumpか4先のpcか判断
    mux(exmem->memCtrlSig.pcSrc, exmem->nextPc, exmem->jumpPc, nextPc, WIDTH);

    // メモリの読み書き
    accessDataMem(exmem->memCtrlSig.memRead, exmem->memCtrlSig.memWrite, exmem->result, exmem->writeMemData, memwb->data);

    // 後のステージで使用する制御信号群を受け渡す
    memwb->wbCtrlSig = exmem->wbCtrlSig;

    // その他の受け渡し
    memcpy(memwb->aluResult, exmem->result, WIDTH * sizeof(int));
    memcpy(memwb->writeRegIndex, exmem->writeRegIndex, RT_WIDTH * sizeof(int));

}

void WB(MEMWB_t* memwb) {

    int regData[WIDTH];
    int buf[WIDTH] = {0};

    // レジスタに書き込むデータの決定
    mux(memwb->wbCtrlSig.memToReg, memwb->aluResult, memwb->data, regData, WIDTH);

    // レジスタにデータを書き込む
    accessReg(memwb->wbCtrlSig.regWrite, memwb->writeRegIndex, regData, buf);

}