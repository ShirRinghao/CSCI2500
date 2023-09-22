#include "math.h"
#include "stdio.h"
#include "stdlib.h"

long fib(long i) {
  if (i == 1)
    return 0;
  if (i == 2)
    return 1;
  return fib(i - 1) + fib(i - 2);
}

void check1() {
  printf("Checkpoint1:\n");
  int i, j, k;
  printf("What is N? ");
  scanf("%d", &k);
  for (i = 0; i < k; i++) {
    for (j = 0; j < i + 1; j++) {
      if (j == 0) {
        printf("*");
      } else {
        (printf("**"));
      }
    }
    printf("\n");
  }
  printf("Checkpoint1 ends here.\n\n");
  return;
}

void check2() {
  printf("Checkpoint2:\n");
  long i;
  printf("Type a non-negative integer: ");
  scanf("%ld", &i);
  printf("Fibonacci number is: %ld\n", fib(i));
  printf("Checkpoint2 ends here.\n\n");
  return;
}

int main() {
  check1();
  check2();
  return 0;
}
