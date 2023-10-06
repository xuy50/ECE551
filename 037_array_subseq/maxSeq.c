#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0)
    return 0;

  size_t lentemp = 1;
  size_t lenMax = 1;
  int temp = array[0];
  for (int i = 1; i < n; i++) {
    if (temp < array[i]) {
      lentemp++;
    }
    else {
      if (lenMax < lentemp)
        lenMax = lentemp;
      lentemp = 1;
    }
    temp = array[i];
  }
  if (lenMax < lentemp) {
    lenMax = lentemp;
  }
  return lenMax;
}
