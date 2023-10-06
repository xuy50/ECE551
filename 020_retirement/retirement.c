#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double tasks(int startAge, double initial, retire_info wr) {
  int age = startAge;
  double saving = initial;
  for (int i = 0; i < wr.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", (age / 12), (age % 12), saving);
    saving = saving * (1 + wr.rate_of_return) + wr.contribution;
    age++;
  }
  return saving;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int age = startAge;
  double saving = initial;

  saving = tasks(age, saving, working);
  age += working.months;

  saving = tasks(age, saving, retired);
  age += retired.months;

  //printf("Age %3d month %2d you have $%.2f\n", (age / 12), (age % 12), saving);
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  int startAge = 327;
  double initial = 21345;

  retirement(startAge, initial, working, retired);

  return EXIT_SUCCESS;
}
