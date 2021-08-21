#include "../../inc/tool.h"
#include "../../inc/def.h"
#include "../../inc/converter.h"

void add(int src1[], int src2[], int dst[]) {

    decToBin(WIDTH, binToDec(WIDTH, src1) + binToDec(WIDTH, src2), dst);
    
}