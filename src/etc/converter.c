#include "../../inc/converter.h"

void decToBin(int size, int dec, int bin[]) {

  for (int i = 0; i < size; i++) {
    if (dec == 0) {
      bin[size - i - 1] = 0;
    } else {
      bin[size - i - 1] = dec % 2;
      dec /= 2;
    }
  }
  
}

int binToDec(int size, int bin[]) {

  int elem;
  int dec = 0;
  
  for (int i = 0; i < size; i++) {
    elem = bin[size - i - 1];
    for (int j = 0; j < i; j++) {
      elem *= 2;
    }
    dec += elem;
  }

  return dec;

}
