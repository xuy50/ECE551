#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream f(fname);
  if (!f.is_open()) {
    std::cerr << "open file error" << std::endl;
    exit(EXIT_FAILURE);
  }
  uint64_t * count = new uint64_t[257]();

  char c;
  while (f.get(c)) {
    ++count[(unsigned char)c];
  }
  f.close();

  count[256] = 1;

  return count;
}
