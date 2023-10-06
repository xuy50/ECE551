#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * n_c = (counts_t *)malloc(sizeof(*n_c));

  n_c->counts = NULL;
  n_c->size = 0;
  n_c->unknown = 0;

  return n_c;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown++;
  }
  else {
    int check = 0;
    for (size_t i = 0; i < c->size; i++) {
      if (strcmp(c->counts[i].str, name) == 0) {
        c->counts[i].count++;
        check = 1;
        break;
      }
    }
    if (!check) {
      one_count_t n_c;
      n_c.count = 1;
      n_c.str = strdup(name);
      c->size++;
      c->counts = realloc(c->counts, c->size * sizeof(*(c->counts)));
      c->counts[c->size - 1] = n_c;
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %zu\n", c->counts[i].str, c->counts[i].count);
  }
  if (c->unknown > 0)
    fprintf(outFile, "<unknown> : %zu\n", c->unknown);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->size; i++) {
    free(c->counts[i].str);
  }
  free(c->counts);
  free(c);
}
