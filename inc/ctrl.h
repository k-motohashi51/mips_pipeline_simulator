#ifndef ALUCTRL_H
#define ALUCTRL_H

#define ALU_CTRL_SIG_WIDTH 4
#define ALU_CTRL_SIG_AND 0
#define ALU_CTRL_SIG_OR 1  
#define ALU_CTRL_SIG_ADD 2
#define ALU_CTRL_SIG_SUB 6
#define ALU_CTRL_SIG_SLT 7
#define ALU_CTRL_SIG_NOR 12

/* EXで使用する制御 */
typedef struct {
    int regDst;
    int aluSrc;
    int aluOp[2];
} EXCtrlSig_t;

/* MEMで使用する制御 */
typedef struct {
    int memRead;
    int memWrite;
    int branch;
    int pcSrc;
} MEMCtrlSig_t;

/* WBで使用する制御 */
typedef struct {
    int memToReg;
    int regWrite;
} WBCtrlSig_t;

typedef struct {
    EXCtrlSig_t  exCtrlSig;
    MEMCtrlSig_t memCtrlSig;
    WBCtrlSig_t  wbCtrlSig;
} ctrlSig_t;

extern void mainCtrl(int op[], ctrlSig_t* ctrlSig);
extern void aluCtrl(int aluOpSig[], int funct[], int aluCtrlSig[]);

#endif