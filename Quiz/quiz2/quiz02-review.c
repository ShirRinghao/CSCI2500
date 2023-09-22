#include <unistd.h>    /* exec */
#include <stdio.h>     /* printf */
#include <sys/types.h> /* need for wait() */
#include <sys/wait.h>  /* wait() */
#include <stdlib.h>    /* calloc() */
#include <string.h>    /* strtok() */

void write_stdin_to_file(void) {
  int pid = getpid();
  char input[128];

  fgets(input, 128, stdin);
  FILE* file = fopen("out.txt", "w");
  fputs(input, file);
  fclose(file);

  printf("Child (%d) done writing:\n", pid);
//  execl("/bin/cat", "cat", "out.txt", NULL);
  printf("-- If this is output something broke --\n");
}

void read_file_to_stdout(void) {
  int pid = getpid();
  int stat;
  char input[128];

  printf("Parent (%d) waiting for child ...\n", pid);
  wait(&stat);
  printf("Child is done. Parent now reading ...\n");

  FILE* file = fopen("out.txt", "r");
  fgets(input, 128, file);
  fclose(file);
  printf("Parent read:\n");
  printf("%s\n", input);
}

void integers_out(void) {
  int pid = getpid();
  int integers[] = {1,2,3,4,5,6,7,8,9,10};

  FILE* file = fopen("int.txt", "w");
  fwrite(integers, sizeof(int), 10, file);
  fclose(file);

  printf("Child (%d) done writing:\n", pid);
  execl("/bin/hexdump", "hexdump", "int.txt", NULL);

  printf("-- If this is output something broke --\n");

  // lets fix it: 
  int stat;
  char hexdump[128];
  if (!fork())
    execl("/usr/bin/which", "which", "hexdump > hexdump.txt", NULL);
  wait(&stat);

  file = fopen("hexdump.txt", "r");
  fgets(hexdump, 128, file);
  strtok(hexdump, "\n"); // why do we do this????
  printf("Hexdump location: %s\n", hexdump);

  // try again
  printf("Child (%d) done writing (hopefully for real this time):\n", pid);
  execl(hexdump, "hexdump", "int.txt", NULL);
  printf("-- Hopefully this isn't shown --\n");

}

void integers_in(void) {
  int pid = getpid();
  int stat;
  int* integers = calloc(10, sizeof(int));
  int* ptr = integers;
  char* ptr2 = (char*) ptr;

  printf("Parent (%d) waiting for child ...\n", pid);
  wait(&stat);
  printf("Child is done. Parent now reading ...\n");

  FILE* file = fopen("int.txt", "r");

  int num;
  while ((num = fread((int*)ptr2, sizeof(int), 1, file)) > 0)
    ++ptr2;
  fclose(file);

  printf("ptr: %p, integers: %p\n", ptr, integers);
  printf("%li read\n", ptr - integers);
  printf("%li read\n", (long*)ptr - (long*)integers); // what happens here?

  for (int i = 0; i < 10; ++i)
    printf("%d ", integers[i]);
  printf("\n");
}

void main(void) {
  setbuf(stdout, NULL);
  printf("In main - starting things with a fork()\n\n");
/*
  // Do a little bit of ascii I/O
  if (fork()) {
    read_file_to_stdout();
  } else {
    write_stdin_to_file(); exit(0);
  }
*/
  printf("In main - heating things up with another fork()\n");
  
  // Do a little bit of binary I/O
  if (fork()) {
    integers_in();
  } else {
    integers_out();
  }

  printf("Done in main()\n");
}
