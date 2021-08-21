#include "../../inc/tool.h"
#include "../../inc/def.h"

void shift(int src[], int dst[], int amount) {
    
    for (int i = 0; i < WIDTH; i++) {
        if (WIDTH - amount <= i) {
            dst[i] = 0;
        } else {
            dst[i] = src[i + amount];
        }
    }

}