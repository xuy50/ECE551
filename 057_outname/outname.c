#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * suffix = ".counts";
  int outLength = strlen(inputName) + strlen(suffix) + 1;
  char * outputName = strdup(inputName);
  outputName = realloc(outputName, outLength * sizeof(*outputName));
  strcat(outputName, suffix);

  return outputName;
}
