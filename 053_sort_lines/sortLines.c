#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
void sortLine(void * f) {
  char * lines = NULL;
  char ** arr = NULL;
  size_t sz = 0;
  size_t counter = 0;
  while (getline(&lines, &sz, f) >= 0) {
    arr = realloc(arr, (counter + 1) * sizeof(*arr));
    arr[counter] = strdup(lines);
    counter++;
  }
  free(lines);
  sortData(arr, counter);

  for (size_t i = 0; i < counter; i++) {
    printf("%s", arr[i]);
    free(arr[i]);
  }

  free(arr);
}

void sortFiles(int argc, char ** argv) {
  for (int i = 1; i < argc; i++) {
    FILE * f = fopen(argv[i], "r");
    if (f == NULL) {
      fprintf(stderr, "Could not open file");
      exit(EXIT_FAILURE);
    }
    sortLine(f);
    if (fclose(f) != 0) {
      fprintf(stderr, "Failed to close the input file!");
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    sortLine(stdin);
  }

  if (argc > 1) {
    sortFiles(argc, argv);
  }
  return EXIT_SUCCESS;
}
