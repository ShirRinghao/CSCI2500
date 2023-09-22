#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b) {
  int bigger, smaller, remainder;
  if (a > b) {
    bigger = a;
    smaller = b;
  } else {
    bigger = b;
    smaller = a;
  }
  remainder = bigger % smaller;
  if (remainder == 0) {
    return smaller;
  }
  return gcd(smaller, remainder);
}

int main() {
  /* Insert your four bytes of ASCII for your secret message */
  //'luni'
  int z = 0x6c756e69;
  /* The 0x prefix above indicates a hexadecimal number */
  char *c = (char *)&z;
  printf("%c", *c++);
  printf("%c", *c++);
  printf("%c", *c++);
  printf("%c\n", *c++);

  /****************************checkpoint2**************************/
  int a, b;
  printf("Enter two integers: ");
  scanf("%d %d", &a, &b);
  printf("The gcd of %d and %d is %d\n", a, b, gcd(a, b));
  return EXIT_SUCCESS;
}
