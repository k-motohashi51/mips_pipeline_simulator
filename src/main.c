#include <stdio.h>
#include "../inc/pReg.h"
#include "../inc/pStg.h"
#include "../inc/mem.h"
#include "../inc/reg.h"
#include "../inc/debug.h"

int main(void) {

    int pc[WIDTH] = {0};
    IFID_t ifid;
    IDEX_t idex;
    EXMEM_t exmem;
    MEMWB_t memwb;

    printf("初期化前\n");
    dispPc(pc);

    initMem();
    initReg();

    printf("\n\n\n初期化後\n");
    dispPc(pc);
    dispMem();
    dispReg();

    IF(pc, &ifid);

    printf("\n\n\nIF後\n");
    dispPc(pc);
    dispIFID(ifid);
    
    ID(&ifid, &idex);

    printf("\n\n\nID後\n");
    dispIDEX(idex);

    EX(&idex, &exmem);

    printf("\n\n\nEX後\n");
    dispEXMEM(exmem);

    MEM(&exmem, &memwb, pc);

    printf("\n\n\nMEM後\n");
    dispPc(pc);
    dispMem();
    dispMEMWB(memwb);

    WB(&memwb);

    printf("\n\n\nWB後\n");
    dispReg();

    return 0;

}
