#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rot(FILE * f) {
  char mattemp[10][10] = {{0}};
  char line[12] = {0};

  for (int i = 0; i < 10; i++) {
    if (fgets(line, 12, f) != NULL) {
      if (strchr(line, '\n') == NULL) {
        fprintf(stderr, "Usage: row(s) longer than 10 characters\n");
        exit(EXIT_FAILURE);
      }
      if (i < 10 && line[10] != '\n') {
        fprintf(stderr, "Usage: row(s) less than 10 characters\n");
        exit(EXIT_FAILURE);
      }
      if (strchr(line, 255) != NULL) {
        fprintf(stderr, "Usage: the char 255 in the matrix\n");
        exit(EXIT_FAILURE);
      }
      for (int j = 0; j < 10; j++) {
        mattemp[i][j] = line[j];
      }
    }
    else {
      fprintf(stderr, "Usage: less than 10 lines\n");
      exit(EXIT_FAILURE);
    }
  }

  if (fgets(line, 12, f) != NULL) {
    fprintf(stderr, "Usage: more than 10 lines\n");
    exit(EXIT_FAILURE);
  }

  char matrix[10][10] = {{0}};

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      matrix[j][9 - i] = mattemp[i][j];
    }
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file");
    return EXIT_FAILURE;
  }

  rot(f);

  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
