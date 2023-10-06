#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream & operator<<(std::ostream & s, std::vector<T> & v) {
  std::string delim;
  for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it) {
    s << delim << *it << std::endl;
  }
  return s;
}

void sortLine(std::istream & f) {
  std::vector<std::string> read;
  std::string line;
  while (getline(f, line)) {
    if (!std::cin.good()) {
      //throw std::exception("Getline error.");
      std::cerr << "Getline error." << std::endl;
      exit(EXIT_FAILURE);
    }
    read.push_back(line);
  }

  std::sort(read.begin(), read.end());

  std::cout << read;
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sortLine(std::cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream rf(argv[i]);
      if (!rf.is_open()) {
        //throw "Open file error.";
        std::cerr << "Open file error." << std::endl;
        return EXIT_FAILURE;
      }
      sortLine(rf);
      rf.close();
    }
  }
  return EXIT_SUCCESS;
}
