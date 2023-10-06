#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  std::ifstream inF(inFile);
  if (!inF.is_open()) {
    std::cerr << "open file error" << std::endl;
    exit(EXIT_FAILURE);
  }

  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  char c;
  typename std::map<unsigned, BitString>::const_iterator it;

  while (inF.get(c)) {
    it = theMap.find((uint8_t)c);
    if (it == theMap.end())
      std::cerr << "cannot find " << c << " in map" << std::endl;
    bfw.writeBitString((*it).second);
  }

  //dont forget to lookup 256 for the EOF marker, and write it out.
  it = theMap.find(256);
  //assert(it != theMap.end());
  //it = theMap.end();
  if (it == theMap.end())
    std::cerr << "cannot find EOF" << std::endl;
  bfw.writeBitString((*it).second);

  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
  inF.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this
  char * inFile = argv[1];
  char * outFile = argv[2];

  uint64_t * counts = readFrequencies(inFile);
  Node * tree = buildTree(counts);
  delete[] counts;

  BitString empty;
  std::map<unsigned, BitString> theMap;
  tree->buildMap(empty, theMap);
  writeCompressedOutput(inFile, outFile, theMap);
  delete tree;
  return EXIT_SUCCESS;
}
