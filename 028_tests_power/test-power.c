#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) == expected_ans)
    return;
  printf("The answer doesn't match");
  exit(EXIT_FAILURE);
}

int main() {
  run_check(0, 0, 1);
  run_check(1, 0, 1);
  run_check(2, 0, 1);
  run_check(1, 2, 1);
  run_check(1, 9, 1);
  run_check(2, 2, 4);
  run_check(2, 8, 256);
  run_check(-1, 1, -1);
  run_check(-1, 2, 1);
  run_check(-2, 1, -2);
  run_check(-2, 2, 4);
  run_check(-2, 3, -8);
  printf("All match. Pass.");
  return EXIT_SUCCESS;
}
