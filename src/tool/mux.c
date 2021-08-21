#include <string.h>
#include "../../inc/def.h"
#include "../../inc/tool.h"

void mux(int sig, int in0[], int in1[], int out[], int width) {

    memcpy(out, (sig == 0) ? in0 : in1, width * sizeof(int));

}