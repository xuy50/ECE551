#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

/**
 * Takes two command line arguments: the name of the file
 * with the categories/words and the name of the file for the story template.
 * If the category name is a valid integer of at least one,
 * should replace the blank with a previously used word,
 * counting backwards from the current word, such that 1
 * refers to the immediate previous word.
 */
int main(int argc, char ** argv) {
  if (argc != 3) {
    printf("clg is %d not 2\n", argc - 1);
    fprintf(stderr,
            "Argument amount error. Usage: categories/words_file_name "
            "story_template_file_name\n");
    return EXIT_FAILURE;
  }

  // read the categories/words file and get the catarray from the file
  FILE * fW = fopen(argv[1], "r");
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
  FILE * fS = fopen(argv[2], "r");
  if (fS == NULL) {
    perror("Open story template file error.\n");
    return EXIT_FAILURE;
  }

  // read story file and use categories array to get the story and print it
  readAndPrintStory(fS, catArr, 0);

  // free categories array
  freeWords(catArr);

  if (fclose(fS) != 0) {
    perror("Close story template file error.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
