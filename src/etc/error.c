#include <stdio.h>
#include <stdlib.h>
#include "../../inc/error.h"

void error(char* str, char* file, char* func, int line) {

  fprintf(stderr, "ERROR : %s (%s : %s : %d)\n", str, file, func, line);
  exit(1);

}
