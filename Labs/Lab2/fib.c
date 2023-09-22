#include "math.h"
#include "stdio.h"
#include "stdlib.h"

int fib(long i) {
  if (i == 1 || i == 2) {
    return 1;
  }
  return fib(i - 1) + fib(i - 2);
}

int pre_fill(int n, int *arr) {
  if (n == 1 || n == 2) {
    return 1;
  }
  if (arr[n] != -1) {
    return arr[n];
  }
  int i;
  arr[0] = 0;
  arr[1] = arr[2] = 1;
  for (i = 3; i <= n; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }
  return arr[n];
}

// int memoization(int n, int *arr) {
//   // the number has been calculated already
//   if (arr[n] != -1) {
//     return arr[n];
//   }
//   int result;
//   // number = 1 or 2
//   if (n == 1 || n == 2) {
//     result = 1;
//   }
//   // other numbers inputted
//   else {
//     result = memorization(n - 1, arr) + memorization(n - 2, arr);
//   }
//   arr[n] = result;
//   return result;
// }

int main(int argc, char *argv[]) {
  if (argc > 10) {
    printf("ERROR: Too many inputs!\n");
    return EXIT_FAILURE;
  }
  int i, num;
  int arr[50];
  for (i = 0; i < 50; i++) {
    arr[i] = -1;
  }
  // for (i = 1; i < argc; i++) {
  //   num = atoi(argv[i]);
  //   printf("fib(%d) is %d\n", i, fib(num));
  // }
  for (i = 1; i < argc; i++) {
    num = atoi(argv[i]);
    printf("fib(%d) is %d\n", num, pre_fill(num, arr));
  }
  return EXIT_SUCCESS;
}
