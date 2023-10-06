#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Open file error.");
    exit(EXIT_FAILURE);
  }

  counts_t * nc = createCounts();

  char * lines = NULL;
  size_t sz = 0;
  ssize_t pos;
  while ((pos = getline(&lines, &sz, f)) >= 0) {
    if (pos > 0 && lines[pos - 1] == '\n') {
      lines[pos - 1] = '\0';
      addCount(nc, lookupValue(kvPairs, lines));
    }
  }
  free(lines);

  if (fclose(f) != 0) {
    fprintf(stderr, "Close file error.");
    exit(EXIT_FAILURE);
  }

  return nc;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 2) {
    fprintf(stderr, "need one or more file to read");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    free(outName);

    //print the counts from c into the FILE f
    printCounts(c, f);

    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Close file error.");
      return EXIT_FAILURE;
    }

    //free the memory for outName and c
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
