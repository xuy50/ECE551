#include "rand_story.h"
/**
 * check whether the category has a same word
 */
int isUniqueWord(const category_t cat, const char * word) {
  for (size_t i = 0; i < cat.n_words; i++) {
    if (strcmp(cat.words[i], word) == 0)
      return 0;
  }

  return 1;
}

/**
 * check whether have a name for words category, if not, add a new name,
 * otherwise check whether the word is in the category, if not add into.
 */
void addWord(catarray_t * catArr, const char * name, const char * word) {
  int uniqueName = 1;  // for checking whether the name is unique
  for (size_t i = 0; i < catArr->n; i++) {
    if (strcmp(catArr->arr[i].name, name) == 0) {
      uniqueName = 0;
      if (isUniqueWord(catArr->arr[i], word)) {
        size_t nw = catArr->arr[i].n_words;
        catArr->arr[i].words =
            realloc(catArr->arr[i].words, (nw + 1) * sizeof(*(catArr->arr[i].words)));
        catArr->arr[i].words[nw] = strdup(word);
        catArr->arr[i].n_words++;
      }
    }
  }
  // if the name is not appeared in the catarray, create a new category and initialize it
  if (uniqueName) {
    size_t arrN = catArr->n;
    catArr->n++;
    catArr->arr = realloc(catArr->arr, (arrN + 1) * sizeof(*(catArr->arr)));
    catArr->arr[arrN].n_words = 1;
    catArr->arr[arrN].name = strdup(name);
    catArr->arr[arrN].words = malloc(sizeof(*catArr->arr[arrN].words));
    catArr->arr[arrN].words[0] = strdup(word);
  }
}

/**
 * read the words file and save all word to catarray_t
 */
catarray_t * readAndSaveWord(FILE * f) {
  // initialize a new catarray
  catarray_t * nc = malloc(sizeof(*nc));
  nc->n = 0;
  nc->arr = NULL;

  // read file by lines
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    if (line[0] != '\0' && line[0] != '\n' && line != NULL) {
      // change the '\n' in the line to '\0'
      size_t linelen = strlen(line);
      if (line[linelen - 1] == '\n')
        line[linelen - 1] = '\0';
      if (line[linelen - 2] == '\n')
        line[linelen - 2] = '\0';
      char * colon = NULL;
      colon = strchr(line, ':');
      // if no colon ":" in the line, show an error massage and exit failure
      if (colon == NULL) {
        free(line);
        freeWords(nc);
        perror("Cannot find the colon ':', please check file.");
        exit(EXIT_FAILURE);
      }
      else {
        // create temp variables for adding name and word into the catarray
        char * wordTemp = strdup(colon + 1);
        size_t namelen = colon - line + 1;
        char * nameTemp = strndup(line, namelen);
        nameTemp[namelen - 1] = '\0';

        // try to add name and word into the catarray
        addWord(nc, nameTemp, wordTemp);

        // free all temp value;
        free(wordTemp);
        free(nameTemp);
      }
    }
  }
  free(line);

  return nc;
}

/**
 * free the memory for the cats array
 */
void freeWords(catarray_t * catArr) {
  // free all category
  for (size_t i = 0; i < catArr->n; i++) {
    for (size_t j = 0; j < catArr->arr[i].n_words; j++) {
      // free all words in word container
      free(catArr->arr[i].words[j]);
    }
    // free word container in category
    free(catArr->arr[i].words);
    // free name in category
    free(catArr->arr[i].name);
  }
  // free category container
  free(catArr->arr);
  // free catarray
  free(catArr);
}

/**
 * free used category
 */
void freeUsedCat(category_t * usedCat) {
  for (size_t i = 0; i < usedCat->n_words; i++) {
    free(usedCat->words[i]);
  }
  free(usedCat->words);
  free(usedCat);
}

/**
 * add the uesd category into used catarray
 */
void addIntoUsedCat(const char * nWord, category_t * usedCat) {
  size_t n = usedCat->n_words;
  usedCat->n_words++;
  usedCat->words = realloc(usedCat->words, (n + 1) * sizeof(*(usedCat->words)));
  usedCat->words[n] = strdup(nWord);
}

/**
 * add the uesd category into used catarray array
 */
void addIntoUsedCatArr(const char * name, const char * nWord, catarray_t * usedCatArr) {
  addWord(usedCatArr, name, nWord);
}

/**
 * check the number of the words in the category for the special name
 */
size_t getNameWordNum(char * name, catarray_t * catArr) {
  size_t result = 0;
  for (size_t i = 0; i < catArr->n; i++) {
    if (strcmp(name, catArr->arr[i].name) == 0) {
      return catArr->arr[i].n_words;
    }
  }
  fprintf(stderr, "Cannot find the category name: %s\n", name);
  exit(EXIT_FAILURE);
  return result;
}

/**
 * Check wheteher the category is used before, if yes rerutn 1, otherwise return 0.
 */
int checkUsedCat(const char * nWord,
                 const char * name,
                 catarray_t * usedCatArr,
                 size_t nameWordNum) {
  for (size_t i = 0; i < usedCatArr->n; i++) {
    if (strcmp(name, usedCatArr->arr[i].name) == 0) {
      if (nameWordNum <= usedCatArr->arr[i].n_words) {
        fprintf(stderr,
                "No more unique word can use for the category name: %s.\n",
                usedCatArr->arr[i].name);
        exit(EXIT_FAILURE);
      }
      for (size_t j = 0; j < usedCatArr->arr[i].n_words; j++) {
        if (strcmp(nWord, usedCatArr->arr[i].words[j]) == 0)
          return 1;
      }
    }
  }
  return 0;
}

/**
 * check the blank whether it is a integer and it can be replaced by a used word
 */
char * checkIntegerBlank(const char * blank, category_t * usedCat) {
  if (blank[0] != '-') {
    char * toIntEndPtr = NULL;
    size_t bInt = strtol(blank, &toIntEndPtr, 10);
    if (*toIntEndPtr == '\0') {
      if (bInt > 0 && bInt <= usedCat->n_words) {
        return usedCat->words[usedCat->n_words - bInt];
      }
    }
  }
  return NULL;
}

/**
 * Check the '_'s if error give error massage, if not, replace the word.
 */
char * parseStory(char * line,
                  catarray_t * catArr,
                  category_t * usedCat,
                  catarray_t * usedCatArr,
                  const int operN) {
  char * l_ = NULL;  // left'_'
  char * r_ = line;  // right'_'

  // do the loop till to the end of the line
  do {
    // get the left '_'
    l_ = strchr(r_, '_');
    if (l_ != NULL) {
      r_ = strchr((l_ + 1), '_');
      // if the no right '_', give a error massage
      if (r_ == NULL) {
        perror("Don't have a matching underscore on the same line, please check "
               "file.\n");
        exit(EXIT_FAILURE);
      }

      // get the blank position,
      char * blank = strndup((l_ + 1), (r_ - l_ - 1));
      // save all of text after the blank
      char * temp = strdup(r_ + 1);

      // check whether the blank is a integer, if get NULL, cannot find a used word
      char * reWordTemp = checkIntegerBlank(blank, usedCat);
      char * reWord = NULL;
      if (reWordTemp == NULL) {
        // check if the '-n' operation is needed use the cannot use uesed words mode
        if (operN == 1) {
          int usedCheck = 0;
          size_t nameWordNum = getNameWordNum(blank, catArr);
          do {
            // get the word to replace the blank by the function chooseWord
            reWord = strdup(chooseWord(blank, catArr));
            if (checkUsedCat(reWord, blank, usedCatArr, nameWordNum)) {
              free(reWord);
              usedCheck = 1;
            }
            else {
              // add the word into integer category
              addIntoUsedCat(reWord, usedCat);
              addIntoUsedCatArr(blank, reWord, usedCatArr);
              usedCheck = 0;
            }
          } while (usedCheck != 0);
        }
        else {
          // get the word to replace the blank by the function chooseWord
          reWord = strdup(chooseWord(blank, catArr));
          // add the word into integer category
          addIntoUsedCat(reWord, usedCat);
        }
      }
      else {
        reWord = strdup(reWordTemp);
        addIntoUsedCat(reWord, usedCat);
      }
      *l_ = '\0';  // replace the first '_' to '\0' for replace the word

      size_t nLinelen = strlen(line) + strlen(reWord) + strlen(temp) + 1;
      line = realloc(line, nLinelen * sizeof(*line));
      // combine everything, appended replaced word and context after the temp line
      strcat(line, reWord);
      strcat(line, temp);

      // free all memory for temp string
      free(blank);
      free(reWord);
      free(temp);
      r_ = line;  // make the r_ to the new position for next time loop
    }
  } while (l_ != NULL);

  return line;
}

/**
 * Read the context in the file, and print the resutle after replacing.
 */
void readAndPrintStory(FILE * f, catarray_t * catArr, const int operN) {
  char * line = NULL;
  size_t sz = 0;
  // create a used category for integer blanks
  category_t * usedCat = malloc(sizeof(*usedCat));
  usedCat->name = "integer";
  usedCat->n_words = 0;
  usedCat->words = NULL;
  // create a used category array for check
  catarray_t * usedCatArr = malloc(sizeof(*usedCatArr));
  usedCatArr->n = 0;
  usedCatArr->arr = NULL;
  while (getline(&line, &sz, f) >= 0) {
    if (line[0] != '\0' && line[0] != '\n' && line != NULL) {
      // parse the story file line and replace the words for the line
      line = parseStory(line, catArr, usedCat, usedCatArr, operN);
    }
    printf("%s", line);
    free(line);
    line = NULL;
  }
  free(line);
  freeUsedCat(usedCat);
  freeWords(usedCatArr);
}
