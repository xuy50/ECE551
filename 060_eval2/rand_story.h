#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use

/**
 * check whether the category has a same word
 */
int isUniqueWord(const category_t cat, const char * word);

/**
 * check whether have a name for words category,if not, add a new name, otherwise check whetherthe word is in the category, if not add into.
 */
void addWord(catarray_t * catArr, const char * name, const char * word);

/**
 * read the words file and save all word to catarray_t
 */
catarray_t * readAndSaveWord(FILE * f);

/**
 * free the memory for the cats array
 */
void freeWords(catarray_t * catArr);

/**
 * free used category
 */
void freeUsedCat(category_t * usedCat);

/**
 * add the uesd category into used catarray and used catarray array
 */
void addIntoUsedCat(const char * nWord, category_t * usedCat);

/**
 * add the uesd category into used catarray array
 */
void addIntoUsedCatArr(const char * name, const char * nWord, catarray_t * usedCatArr);

/**
 * check the number of the words in the category for the special name 
 */
size_t getNameWordNum(char * name, catarray_t * catArr);

/**
 * Check wheteher the category is used before, if yes rerutn 1, otherwise return 0.
 */
int checkUsedCat(const char * nWord,
                 const char * name,
                 catarray_t * usedCatArr,
                 size_t nameWordNum);

/**
 * Check the '_'s if error give error massage, if not, replace the word.
 */
char * checkIntegerBlank(const char * blank, category_t * usedCat);

/**
 * Check the '_'s if error give error massage, if not, replace the word.
*/
char * parseStory(char * line,
                  catarray_t * catArr,
                  category_t * usedCat,
                  catarray_t * usedCatArr,
                  const int operN);

/**
 * Parse the story template by printing the story and replacing blanks with the word "cat".
 * The operN is a int to check whether the word can be the used words, if operN is 1, cannot
 * use the used words, otherwise, the words have no limit.
 */
void readAndPrintStory(FILE * f, catarray_t * catArr, const int operN);

#endif
