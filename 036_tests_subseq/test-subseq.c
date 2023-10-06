#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void testMaxSeq(int * array, size_t n, size_t expect) {
  for (int i = 0; i < n; i++) {
    printf("%d, ", array[i]);
  }
  printf("expect: %ld, ", expect);
  size_t maxr = maxSeq(array, n);
  printf("r = %ld\n", maxr);

  if (expect == maxr) {
    return;
  }
  else {
    printf("Answer does not match the expect answer.\n");
    exit(EXIT_FAILURE);
  }
}

int main() {
  int arr0[0] = {};
  int arr1[1] = {0};
  int arr2[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int arr3[8] = {5, 4, 3, 2, 1, 0, -1, -2};
  int arr4[11] = {-9, -7, -9, -4, -2, 0, -2, 4, 7, 4, 9};
  int arr5[12] = {0, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5};
  int arr6[9] = {0, 1, 2, 3, 4, 5, 4, 3, 4};
  int arr7[7] = {-1, -2, -3, 1, 2, 3, 4};
  int arr8[6] = {1, 1, 1, 1, 1, 1};
  int arr9[3] = {0, 1, 2};
  int arr10[2] = {0, 1};
  int arr11[2] = {1, 0};
  int arr12[6] = {1, 1, 1, 3, 4, 5};
  int arr13[6] = {0, 1, 2, 3, 3, 3};
  int arr14[6] = {1, 0, 2};
  int arr15[2] = {-2147483648, 2147483647};
  testMaxSeq(arr0, 0, 0);
  testMaxSeq(arr1, 1, 1);
  testMaxSeq(arr2, 10, 4);
  testMaxSeq(arr3, 8, 1);
  testMaxSeq(arr4, 11, 4);
  testMaxSeq(arr5, 11, 5);
  testMaxSeq(arr6, 9, 6);
  testMaxSeq(arr7, 7, 5);
  testMaxSeq(arr8, 6, 1);
  testMaxSeq(arr9, 3, 3);
  testMaxSeq(arr10, 2, 2);
  testMaxSeq(arr11, 2, 1);
  testMaxSeq(arr12, 6, 4);
  testMaxSeq(arr13, 6, 4);
  testMaxSeq(arr14, 6, 2);
  testMaxSeq(arr15, 2, 2);
  printf("pass\n");
  return EXIT_SUCCESS;
}
