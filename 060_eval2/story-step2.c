#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

/**
 * Takes one command line argument: the name of the file with the categories and words. 
 * This program should read from the file and store the words into a catarray_t and print
 * them using the provided function printWords.
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

  // create the categories array and read file to get the categories to save
  catarray_t * catArr = readAndSaveWord(f);

  // print check
  //for (size_t i = 0; i < catArr->n; i++) {
  //printf("%s:\n", catArr->arr[i].name);
  //for (size_t j = 0; j < catArr->arr[i].n_words; j++) {
  //  printf("  %s\n", catArr->arr[i].words[j]);
  //}
  //}

  // print the categories array
  printWords(catArr);

  // free the categories array
  freeWords(catArr);

  if (fclose(f) != 0) {
    perror("Close file error.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
