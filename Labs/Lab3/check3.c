#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *myfile = fopen("book-1984.txt", "r");
  char line[128];
  char *p, *q;
  if (!myfile) {
    return EXIT_FAILURE;
  }
  while (fgets(line, 128, myfile)) {
    if (isalnum(line[0])) {
      for (p = line, q = line; *p != '\0'; p++) {
        if (isalnum(*p)) {
          printf("%c", *p);
        } else {
          q++;
        }
      }
      printf(" [%ld alnum chars]\n", p - q);
    }
  }

  fclose(myfile);

  return EXIT_SUCCESS;
}
