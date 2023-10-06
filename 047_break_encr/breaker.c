#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int getlete(FILE * f) {
  int letters[26] = {0};
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      letters[c - 'a']++;
    }
  }

  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file!\n");
    exit(EXIT_FAILURE);
  }

  int result = 0;
  for (int i = 1; i < 26; i++) {
    if (letters[result] < letters[i]) {
      result = i;
    }
  }
  return result;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key input FileName\n");
    //return EXIT_FAILURE;
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
    //return EXIT_FAILURE;
  }

  int lete = getlete(f);
  //printf("%d\n", lete);
  int key = (lete - 4 + 26) % 26;
  fprintf(stdout, "%d\n", key);

  //if (fclose(f) != 0) {
  //fprintf(stderr, "Failed to close the input file!\n");
  //exit(EXIT_FAILURE);
  //return EXIT_FAILURE;
  //}

  return EXIT_SUCCESS;
}
