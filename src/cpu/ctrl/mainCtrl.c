#include "../../../inc/converter.h"
#include "../../../inc/ctrl.h"
#include "../../../inc/error.h"
#include "../../../inc/def.h"

/* opフィールドの形式の種類 */
#define OP_R 0
#define OP_LW 35
#define OP_SW 43
#define OP_BEQ 4
#define OP_J 2

static int refRegDst[] = {1, 0, 0, 0};
static int refAluSrc[] = {0, 1, 1, 0};
static int refAluOp0[] = {1, 0, 0, 0};
static int refAluOp1[] = {0, 0, 0, 1};
static int refMemRead[] = {0, 1, 0, 0};
static int refMemWrite[] = {0, 0, 1, 0};
static int refBranch[] = {0, 0, 0, 1};
static int refPcSrc[] = {0, 0, 0, 0};
static int refMemToReg[] = {0, 1, 0, 0};
static int refRegWrite[] = {1, 1, 0, 0};

void mainCtrl(int op[], ctrlSig_t* ctrlSig);
static int judgeOp(int op[]);

/* メイン制御ユニット(外部とのインターフェース) */
void mainCtrl(int op[], ctrlSig_t* ctrlSig) {

    int type = judgeOp(op);

    if (type == 4) {
        ERROR("opフィールドが予期しない値です");
    }

    ctrlSig->exCtrlSig.regDst = refRegDst[type];
    ctrlSig->exCtrlSig.aluSrc = refAluSrc[type];
    ctrlSig->exCtrlSig.aluOp[0] = refAluOp0[type];
    ctrlSig->exCtrlSig.aluOp[1] = refAluOp1[type];
    ctrlSig->memCtrlSig.memRead = refMemRead[type];
    ctrlSig->memCtrlSig.memWrite = refMemWrite[type];
    ctrlSig->memCtrlSig.branch = refBranch[type];
    ctrlSig->memCtrlSig.pcSrc = refPcSrc[type];
    ctrlSig->wbCtrlSig.memToReg = refMemToReg[type];
    ctrlSig->wbCtrlSig.regWrite = refRegWrite[type];
    
}

/* opフィールドの命令の種類を判別する */
static int judgeOp(int op[]) {

    switch (binToDec(OP_WIDTH, op)) {
        case OP_R:   return 0;
        case OP_LW:  return 1;
        case OP_SW:  return 2;
        case OP_BEQ: return 3;
        default:  return 4;
    }

}
