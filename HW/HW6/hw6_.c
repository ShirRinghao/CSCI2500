#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int LRU(int cache[], int mem, int i, int associa) {}

int main(int argc, char *argv[]) {
  int associa = atoi(argv[1]);
  int set_size = 256 / associa;
  char *algor = argv[2];

  int cache[set_size][associa];
  int x, y;
  for (x = 0; x < set_size; x++) {
    for (y = 0; y < associa; y++) {
      cache[x][y] = -1;
    }
  }

  char const *const file = argv[3];
  FILE *myfile;
  myfile = fopen(file, "r");

  int mem[10000];
  int mem_index = 0, tmp = 0;
  while (fscanf(myfile, "%d", &tmp) == 1) {
    mem[mem_index++] = tmp;
  }

  printf("Cache size: 256\n");
  printf("Cache associativity: %d\n", associa);
  printf("Cache sets: %d\n", set_size);
  printf("Cache algorithm: %s\n", algor);

  int i, j, hit_count = 0;
  for (i = 0; i < mem_index; i++) {
    int address = mem[i];
    int index = address % set_size;
    printf("%d", mem[i]);
    for (j = 0; j < associa; j++) {
      if (address == cache[index][j]) {
        printf(" (hit)\n");
        hit_count++;
        break;
      }

      if (j == associa - 1) {
        printf(" (miss)\n");
        for (j = 0; j < associa; j++) {
          if (cache[index][j] == -1) {
            cache[index][j] = address;
            j = associa;
            break;
          }
          if (j == associa - 1) {
            if (!strcmp(algor, "LRU")) {
              cache[index][LRU(cache[index], mem, i, associa)] = mem[i];
            } else if (!strcmp(algor, "Belady")) {
              cache[index][Belady(cache[index], mem, i, associa, mem_index)] =
                  mem[i];
            }
          }
        }
      }
    }
  }
  // output
  float hit_rate = (float)hit_count / mem_index;
  printf("Cache accesses: %d\n", mem_index);
  printf("Cache hits: %d\n", hit_count);
  printf("Cache misses: %d\n", mem_index - hit_count);
  printf("Overall hit rate: %1.6f\n", hit_rate);

  return EXIT_SUCCESS;
}
