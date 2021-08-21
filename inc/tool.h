#ifndef TOOL_H
#define TOOL_H

extern int  and(int src1, int src2);
extern void add(int src1[], int src2[], int dst[]);
extern void mux(int sig, int in0[], int in1[], int out[], int width);
extern void shift(int src[], int dst[], int amount);
extern void extendSign(int src[], int srcWidth, int dst[], int dstWidth);

#endif