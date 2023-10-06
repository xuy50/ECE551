int max(int size1, int oss) {
  return (size1 > oss ? size1 : oss);
}

int is_betweent(int xy, int os, int oss) {
  if (xy >= os && xy < oss)
    return 1;
  else
    return 0;
}

int is_equal(int xy, int os, int oss_1) {
  if (xy == os || xy == oss_1)
    return 1;
  else
    return 0;
}

void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, (x_offset + size2));
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, (y_offset + size2));
  //count from 0 to h. Call the number you count with y
  for (int y = 0; y < h; y++) {
    //count from 0 to w. Call the number you count with x
    for (int x = 0; x < w; x++) {
      //check if  EITHER
      //    ((x is between x_offset  and x_offset +size2) AND
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      //  OR
      //    ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      // if so, print a *
      if ((is_betweent(x, x_offset, (x_offset + size2)) &&
           is_equal(y, y_offset, (y_offset + size2 - 1))) ||
          (is_betweent(y, y_offset, (y_offset + size2)) &&
           is_equal(x, x_offset, (x_offset + size2 - 1)))) {
        printf("%c", '*');
      }
      //if not,
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
      //if so, print a #
      else {
        if (((x < size1) && (y == 0 || y == (size1 - 1))) ||
            ((y < size1) && (x == 0 || x == (size1 - 1)))) {
          printf("#");
        }
        else {  //else print a space
          printf(" ");
        }
      }
    }
    //when you finish counting x from 0 to w,
    //print a newline
    printf("\n");
  }
}
