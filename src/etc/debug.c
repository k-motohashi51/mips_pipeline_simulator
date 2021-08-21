#include <stdio.h>
#include "../../inc/mem.h"
#include "../../inc/reg.h"
#include "../../inc/converter.h"
#include "../../inc/debug.h"

void dispPc(int pc[]);
void dispIFID(IFID_t);
void dispIDEX(IDEX_t);
void dispEXMEM(EXMEM_t);
void dispMEMWB(MEMWB_t);

void dispPc(int pc[]) {

    printf("pc:0x%08x\n", binToDec(WIDTH, pc));

}

void dispIFID(IFID_t ifid) {

    printf("IFIDレジスタ\n");
    printf("\tnextPc:0x%08x\t",binToDec(WIDTH, ifid.nextPc));
    printf("ins:0x%08x\n", binToDec(WIDTH, ifid.ins));

}

void dispIDEX(IDEX_t idex) {

    printf("IDEXレジスタ\n");
    printf("\tnextPc:0x%08x\t", binToDec(WIDTH, idex.nextPc));
    printf("data1:0x%08x\t", binToDec(WIDTH, idex.data1));
    printf("data2:0x%08x\t", binToDec(WIDTH, idex.data2));
    printf("immd:%d\t", binToDec(WIDTH, idex.immd));
    printf("rt:%d\t", binToDec(RT_WIDTH, idex.rt));
    printf("rd:%d\n", binToDec(RD_WIDTH, idex.rd));

    printf("\t\texsig.aluOp[0]:%d\n", idex.exCtrlSig.aluOp[0]);
    printf("\texsig.aluOp[1]:%d\n", idex.exCtrlSig.aluOp[1]);
    printf("\texsig.aluSrc:%d\n", idex.exCtrlSig.aluSrc);
    printf("\texsig.regDst:%d\n", idex.exCtrlSig.regDst);

    printf("\tmemsig.branch:%d\n", idex.memCtrlSig.branch);
    printf("\tmemsig.memRead:%d\n", idex.memCtrlSig.memRead);
    printf("\tmemsig.memWrite:%d\n", idex.memCtrlSig.memWrite);
    printf("\tmemsig.pcSrc:%d\n", idex.memCtrlSig.pcSrc);

    printf("\twbsig.memToReg:%d\n", idex.wbCtrlSig.memToReg);
    printf("\twbsig.regWrite:%d\n", idex.wbCtrlSig.regWrite);

}

void dispEXMEM(EXMEM_t exmem) {

    printf("EXMEMレジスタ\n");
    printf("\tnextPc:0x%08x\t", binToDec(WIDTH, exmem.nextPc));
    printf("jumpPc:0x%08x\t", binToDec(WIDTH, exmem.jumpPc));
    printf("isZeor:%d\t", exmem.isZero);
    printf("result:0x%08x\t", binToDec(WIDTH, exmem.result));
    printf("writeMemData:0x%08x\t", binToDec(WIDTH, exmem.writeMemData));
    printf("writeRegIndex:%d\n", binToDec(RT_WIDTH, exmem.writeRegIndex));

    printf("\t\tmemsig.branch:%d\t", exmem.memCtrlSig.branch);
    printf("memsig.memRead:%d\t", exmem.memCtrlSig.memRead);
    printf("memsig.memWrite:%d\t", exmem.memCtrlSig.memWrite);
    printf("memsig.pcSrc:%d\n", exmem.memCtrlSig.pcSrc);

    printf("\t\twbsig.memToReg:%d\t", exmem.wbCtrlSig.memToReg);
    printf("wbsig.regWrite:%d\n", exmem.wbCtrlSig.regWrite);
 
}

void dispMEMWB(MEMWB_t memwb) {

    printf("MEMWBレジスタ\n");
    printf("\tdata:0x%08x\t", binToDec(WIDTH, memwb.data));
    printf("aluResult:0x%08x\t", binToDec(WIDTH, memwb.aluResult));
    printf("writeRegIndex:%d\n", binToDec(RT_WIDTH, memwb.writeRegIndex));

    printf("\t\tsig.memToReg:%d\t", memwb.wbCtrlSig.memToReg);
    printf("sig.regWrite:%d\n", memwb.wbCtrlSig.regWrite);

}