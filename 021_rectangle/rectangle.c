#include <stdio.h>
#include <stdlib.h>
//I've provided "min" and "max" functions in
//case they are useful to you
int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

//Declare your rectangle structure here!
struct _rectangle {
  int x;
  int y;
  int width;
  int height;
};
typedef struct _rectangle rectangle;

rectangle canonicalize(rectangle r) {
  //WRITE THIS FUNCTION
  if (r.height < 0) {
    r.y += r.height;
    r.height *= (-1);
  }
  if (r.width < 0) {
    r.x += r.width;
    r.width *= (-1);
  }
  return r;
}
rectangle intersection(rectangle r1, rectangle r2) {
  //WRITE THIS FUNCTION
  r1 = canonicalize(r1);
  r2 = canonicalize(r2);
  rectangle r;
  int xmax = max(r1.x, r2.x);
  int xmin = min(r1.x, r2.x);
  int ymax = max(r1.y, r2.y);
  int ymin = min(r1.y, r2.y);

  r.x = xmax;
  r.y = ymax;

  int check = 1;

  if (xmin == r1.x) {
    if ((r1.x + r1.width) < r2.x) {
      r.width = 0;
      r.height = 0;
      check = 0;
    }
    else {
      if ((r2.x + r2.width) > (r1.x + r1.width))
        r.width = r1.x + r1.width - r2.x;
      else
        r.width = r2.width;
    }
  }
  else {
    if ((r2.x + r2.width) < r1.x) {
      r.width = 0;
      r.height = 0;
      check = 0;
    }
    else {
      if ((r2.x + r2.width) < (r1.x + r1.width))
        r.width = r2.x + r2.width - r1.x;
      else
        r.width = r1.width;
    }
  }

  if (check != 0) {
    if (ymin == r1.y) {
      if ((r1.y + r1.height) < r2.y) {
        r.height = 0;
        r.width = 0;
        check = 0;
      }
      else {
        if ((r2.y + r2.height) > (r1.y + r1.height))
          r.height = r1.y + r1.height - r2.y;
        else
          r.height = r2.height;
      }
    }
    else {
      if ((r2.y + r2.height) < r1.y) {
        r.height = 0;
        r.width = 0;
        check = 0;
      }
      else {
        if ((r2.y + r2.height) < (r1.y + r1.height))
          r.height = r2.y + r2.height - r1.y;
        else
          r.height = r1.height;
      }
    }
  }

  return r;
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, r.x + r.width, r.y + r.height);
  }
}

int main(void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);

  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle i = intersection(r1, r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1, r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);

  i = intersection(r1, r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1, r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2, r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2, r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);

  i = intersection(r2, r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2, r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3, r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3, r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);

  i = intersection(r3, r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3, r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4, r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4, r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);

  i = intersection(r4, r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4, r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);

  return EXIT_SUCCESS;
}
