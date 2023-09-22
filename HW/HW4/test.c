#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test(int value, int num[], int count) {
  int i;
  for (i = 0; i < 10; i++) {
    if (num[i] == value) {
      return i;
    }
  }
  return count++;
}

int main() {
  int num[10];
  int i, count = 10;
  for (i = 1; i < 10; i++) {
    num[i] = i + 100;
  }
  for (i = 0; i < 10; i++) {
    printf("count now is:%d\n", test(i, num, count));
  }
  return EXIT_SUCCESS;
}
