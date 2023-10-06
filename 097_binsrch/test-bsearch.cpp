#include <assert.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"
#include "search.cpp"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int n = 1;
  if (high > low)
    n = log2(high - low) + 1;

  CountedIntFn * wrapF = new CountedIntFn(n, f, mesg);
  int result = binarySearchForZero(wrapF, low, high);
  std::cout << result << std::endl;

  assert(result == expected_ans);
}

class testFunc : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class halfFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 2 * arg + 3; }
};

class nagFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -1; }
};

class halfFunction1 : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 2 * arg - 3; }
};

int main() {
  //testFunc * f = new testFunc();
  //check(f, 0, 1, 0, "pass\n");
  //check(f, 1, 2, 1, "all positive without solution\n");
  //check(f, -2, 0, -1, "all nagtive with right bound 0\n");
  //check(f, -3, -1, -2, "all nagtive\n");
  //check(f, -2, 1, 0, "pass\n");
  //check(f, 0, 0, 0, "high <= low\n");
  //check(f, -1, -4, -1, "high <= low\n");
  //check(f, -1, 0, -1, "all nagtive\n");
  //check(f, 1, 1, 1, "high <= low\n");
  //SinFunction * sf = new SinFunction();
  //check(sf, 0, 150000, 52359, "pass");
  //check(sf, 0, 52358, 52357, "pass\n");
  //check(sf, -1, 0, -1, "all nagtive\n");
  //check(sf, 0, 0, 0, "0");
  //check(sf, 52360, 52387, 52360, "high <= low\n");
  //check(sf, -1, 1, 0, "pass");
  //check(sf, 0, 2, 1, "all positive without solution\n");
  halfFunction pf;
  check(&pf, -3, 5, -2, "0.5 answer choose\n");
  //nagFunction nf;
  //check(&nf, 0, 5, 4, "nagetive function without solution\n");
  halfFunction1 hf1;
  check(&hf1, 0, 3, 1, "0.5 answer choose\n");
  return EXIT_SUCCESS;
}
