#include <math.h>

#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low > high)
    return low;
  //exit(EXIT_FAILURE);

  int result = low;
  int lowB = low;
  int highB = high;
  int resultChecker = 0;

  while (lowB < highB) {
    int midInd = lowB + (highB - lowB) / 2;
    int midInvoke = f->invoke(midInd);
    result = midInd;
    if (midInvoke == 0) {
      resultChecker = 0;
      break;
    }
    else if (midInvoke < 0) {
      lowB = midInd + 1;
      resultChecker = -1;
    }
    else if (midInvoke > 0) {
      highB = midInd;
      resultChecker = 1;
    }
  }
  //std::cout << result << std::endl;
  //if (resultChecker == -1)
  //return high - 1;
  if (resultChecker == 1 && result != low)
    return result - 1;
  return result;
}
