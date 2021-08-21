#include "../../../inc/ctrl.h"
#include "../../../inc/converter.h"
#include "../../../inc/error.h"
#include "../../../inc/def.h"

#define ALU_OP_WIDTH 2  // 制御信号aluOpのビット幅

/* 制御信号aluOpの形式の種類 */
#define ALU_OP_I 0
#define ALU_OP_BEQ 1
#define ALU_OP_R 2

/* functフィールドの命令の種類 */
#define FUNCT_ADD   32
#define FUNCT_SUB   34
#define FUNCT_AND   36
#define FUNCT_OR    37
#define FUNCT_SLT   42

/* ALU制御ユニット */
void aluCtrl(int aluOpSig[], int funct[], int aluCtrlSig[]) {

    if (binToDec(ALU_OP_WIDTH, aluOpSig) == ALU_OP_I) {
        decToBin(ALU_CTRL_SIG_WIDTH, ALU_CTRL_SIG_ADD, aluCtrlSig);
        return;
    }

    if (binToDec(ALU_OP_WIDTH, aluOpSig) == ALU_OP_BEQ) {
        decToBin(ALU_CTRL_SIG_WIDTH, ALU_CTRL_SIG_SUB, aluCtrlSig);
        return;
    }

    if (binToDec(ALU_OP_WIDTH, aluOpSig) == ALU_OP_R) {

        switch (binToDec(FUNCT_WIDTH, funct)) {
            case FUNCT_ADD: decToBin(ALU_CTRL_SIG_WIDTH, ALU_CTRL_SIG_ADD, aluCtrlSig); break;
            case FUNCT_SUB: decToBin(ALU_CTRL_SIG_WIDTH, ALU_CTRL_SIG_SUB, aluCtrlSig); break;
            case FUNCT_AND: decToBin(ALU_CTRL_SIG_WIDTH, ALU_CTRL_SIG_AND, aluCtrlSig); break;
            case FUNCT_OR:  decToBin(ALU_CTRL_SIG_WIDTH, ALU_CTRL_SIG_OR, aluCtrlSig);  break;
            case FUNCT_SLT: decToBin(ALU_CTRL_SIG_WIDTH, ALU_CTRL_SIG_SLT, aluCtrlSig); break;
            default:    ERROR("functフィールドが予期しない値です");
        }
        return;
    }

    ERROR("制御信号aluOpが予期しない値です");

}