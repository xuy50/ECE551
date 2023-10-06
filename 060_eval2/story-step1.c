#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

/**
 * Read the story template from. This program should parse the story 
 * template by printing the story and replacing blanks with the word "cat".
 */
int main(int argc, char ** argv) {
  if (argc != 2) {
    printf("clg is %d not 1\n", argc - 1);
    fprintf(stderr, "Argument amount error. Usage: file_name\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Open file error.\n");
    return EXIT_FAILURE;
  }

  // Read the context in the file, and print the resutle after replacing.
  readAndPrintStory(f, NULL, 0);

  if (fclose(f) != 0) {
    perror("Close file error.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
