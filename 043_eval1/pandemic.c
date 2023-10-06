#include "pandemic.h"

#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  //ans.name[0] = '\0';
  //ans.population = 0;

  //if (line == NULL) {
  //}

  country_t ans;
  size_t strsize = strlen(line);
  size_t counter = 0;  // the counter for checking the position after the ','
  for (size_t i = 0; i < strsize; i++) {
    // the Max name length is 64, if it will over 64, it will output a error massage and exit_failure
    if (counter >= MAX_NAME_LEN) {
      fprintf(stderr, "this line country name longer than limited.\n");
      exit(EXIT_FAILURE);
    }
    // check current char wheather it is a ',', is not write it into name, else write the '\0'
    if (line[i] != ',') {
      ans.name[i] = line[i];
    }
    else {
      ans.name[i] = '\0';
      counter++;
      break;
    }
    counter++;
  }
  if (counter > MAX_NAME_LEN) {
    fprintf(stderr, "this line country name longer than limited.\n");
    exit(EXIT_FAILURE);
  }

  // check wheter the name is illegal, if illegal output error massage and exit_failure
  if (counter == strsize || line[counter] == '\n' || line[counter] == '\0') {
    fprintf(stderr, "this line do not have a population.\n");
    exit(EXIT_FAILURE);
  }

  // use the founction strtoul to check whether the line is a integer number after the ',', if not a integer output a error massage and exit_failure
  char * popuCheck = NULL;
  ans.population = strtoul(&line[counter], &popuCheck, 10);
  if (*popuCheck != '\0' && *popuCheck != '\n') {
    fprintf(stderr, "this line's poluation is not a number.\n");
    exit(EXIT_FAILURE);
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  // if n_days is 0, return back without any work.
  if (n_days < 7) {
    return;
  }
  // data is NULL, output error massage and exit_failure.
  if (n_days < 7 || data == NULL) {
    fprintf(stderr, "The data is NULL.\n");
    exit(EXIT_FAILURE);
  }
  //// if n_days is less than 7, will do the average by n_days.
  //if (n_days < 7) {
  //unsigned total7 = 0;
  //for (size_t i = 0; i < n_days; i++) {
  //  total7 += data[i];
  //}
  //*avg = total7 / (double)n_days;
  //printf("%f\n", avg[0]); // check the output
  //}
  else {  // do the "smooth" average calculte
    for (size_t i = 0; i < n_days - 6; i++) {
      unsigned total7 = 0;
      for (int j = 0; j < 7; j++) {
        total7 += data[i + j];
      }
      avg[i] = total7 / 7.0;
    }
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  // if n_days is 0, return back without any work.
  if (n_days < 1) {
    return;
  }
  // data is NULL, the funciton will do nothing, and output error massage and exit_failure
  if (data == NULL) {
    fprintf(stderr, "The data is NULL.\n");
    exit(EXIT_FAILURE);
  }
  // get sum by loop for each day and get the day's cumulative
  unsigned totalSum = 0;
  for (size_t i = 0; i < n_days; i++) {
    totalSum += data[i];
    cum[i] = totalSum / (double)pop * 100000;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  // if number of countries is 0, return without any work.
  if (n_countries < 1) {
    return;
  }
  // if the data of countries is NULL, exit failure
  if (countries == NULL) {
    fprintf(stderr, "The countries data is NULL.\n");
    exit(EXIT_FAILURE);
  }
  // if number of data is 0, return without any work.
  if (n_days < 1) {
    return;
  }
  // if the data is NULL, exit failure
  if (data == NULL) {
    fprintf(stderr, "The data is NULL.\n");
    exit(EXIT_FAILURE);
  }

  size_t countryNo = 0;           // use for saving the checked maxdata's country
  unsigned maxdata = data[0][0];  // the maxdata for saving the max data
  // loop for all data to find the maxdata in all days.
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (maxdata < data[i][j]) {
        maxdata = data[i][j];
        countryNo = i;
      }
    }
  }

  printf("%s has the most daily cases with %u\n", countries[countryNo].name, maxdata);
}
