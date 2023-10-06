#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * addPair(const char * line) {
  kvpair_t * newPair = malloc(sizeof(*newPair));
  char * prt_p;
  char * prt_l;
  prt_p = strchr(line, '=');
  prt_l = strchr(prt_p + 1, '\n');
  if (prt_p == NULL || prt_l == NULL) {
    fprintf(stderr, "no =, key is unknown");
    exit(EXIT_FAILURE);
  }
  else {
    newPair->key = malloc((prt_p - line + 1) * sizeof(*newPair->key));
    strncpy(newPair->key, line, prt_p - line);
    newPair->key[prt_p - line] = '\0';
    newPair->value = malloc((prt_l - prt_p) * sizeof(*newPair->value));
    strncpy(newPair->value, prt_p + 1, prt_l - prt_p - 1);
    newPair->value[prt_l - prt_p - 1] = '\0';
  }
  return newPair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("cannot open file");
    exit(EXIT_FAILURE);
  }
  kvarray_t * result = malloc(sizeof(*result));
  result->pair = NULL;
  result->count = 0;

  char * lines = NULL;
  size_t sz = 0;
  ssize_t length = 0;

  while ((length = getline(&lines, &sz, f)) > 0) {
    result->pair = realloc(result->pair, (result->count + 1) * sizeof(*result->pair));
    result->pair[result->count] = addPair(lines);
    result->count++;
  }
  free(lines);

  if (fclose(f) != 0) {
    fprintf(stderr, "close file frror.\n");
    exit(EXIT_FAILURE);
  }

  return result;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->count; i++) {
    free(pairs->pair[i]->key);
    free(pairs->pair[i]->value);
    free(pairs->pair[i]);
  }
  free(pairs->pair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->count; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pair[i]->key, pairs->pair[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->count; i++) {
    if (strcmp(pairs->pair[i]->key, key) == 0) {
      return pairs->pair[i]->value;
    }
  }
  return NULL;
}
