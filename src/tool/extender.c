#include "../../inc/tool.h"

void extendSign(int src[], int srcWidth, int dst[], int dstWidth) {

    for (int i = 0; i < dstWidth; i++) {
        if (i < srcWidth) {
            dst[i] = 0;
        } else {
            dst[i] = src[i - srcWidth];
        }
    }

}