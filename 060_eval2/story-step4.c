#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

/**
 * Help function to output the error massage.
 */
void printErrorMas() {
  fprintf(stderr,
          "Argument amount error. Usage: categories/words_file_name "
          "story_template_file_name, or, -n categories/words_file_name "
          "story_template_file_name\n");
}

/**
 * step4  
 */
int main(int argc, char ** argv) {
  if (argc != 3 && argc != 4) {
    printf("clg is %d not 2 or 3\n", argc - 1);
    printErrorMas();
    return EXIT_FAILURE;
  }

  int operN = 0;
  if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      printf("option '-n' using error.\n");
      printErrorMas();
      return EXIT_FAILURE;
    }
  }
  if (strcmp(argv[1], "-n") == 0) {
    if (argc == 4) {
      operN = 1;
    }
    else {
      printf("option '-n' using error.\n");
      printErrorMas();
      return EXIT_FAILURE;
    }
  }
  if (argc == 3) {
    if (strcmp(argv[1], "-n") == 0 || strcmp(argv[2], "-n") == 0) {
      printf("option '-n' using error.\n");
      printErrorMas();
      return EXIT_FAILURE;
    }
  }

  // read the categories/words file and get the catarray from the file
  FILE * fW;
  if (operN)
    fW = fopen(argv[2], "r");
  else
    fW = fopen(argv[1], "r");
  if (fW == NULL) {
    perror("Open categories/words file error.\n");
    return EXIT_FAILURE;
  }
  catarray_t * catArr = readAndSaveWord(fW);

  if (fclose(fW) != 0) {
    perror("Close categories/words file error.\n");
    return EXIT_FAILURE;
  }

  // read the story template file and get and print the story
  FILE * fS;
  if (operN)
    fS = fopen(argv[3], "r");
  else
    fS = fopen(argv[2], "r");
  if (fS == NULL) {
    perror("Open story template file error.\n");
    return EXIT_FAILURE;
  }

  // Read the context in the file, and print the resutle after replacing
  // with a '-n' operation mode
  readAndPrintStory(fS, catArr, operN);

  freeWords(catArr);

  if (fclose(fS) != 0) {
    perror("Close story template file error.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
