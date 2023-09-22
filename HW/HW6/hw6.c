#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// algorithm that deal with two different evict method
int evict(int cache[], int mem[], int i, int associa, int mem_index,
          char *algor) {
  int count = 0, j = 0, insert_loc = 0, max = 0;
  // LRU operation
  if (!strcmp(algor, "LRU")) {
    // Looping through each index in cache
    for (; j < associa; j++) {
      count = 0;
      int k = i;
      // Find the least recent accessed element
      for (; k >= 0; k--) {
        if (mem[k] != cache[j]) {
          count++;
        } else {
          break;
        }
      }
      if (count > max) {
        max = count;
        insert_loc = j;
      }
    }
  }
  // Belady operation
  else if (!strcmp(algor, "Belady")) {
    int notfound = 0;
    // Looping through each index in cache
    for (; j < associa; j++) {
      count = 0;
      int k = i;
      // Find the furthest accessed element
      for (; k < mem_index; k++) {
        if (mem[k] != cache[j]) {
          count++;
        } else {
          break;
        }
      }
      // Count number of elements haven't been used in the future
      if (k == mem_index - 1) {
        notfound++;
      }
      if (count > max) {
        max = count;
        insert_loc = j;
      }
    }
    // When there are multpyng items not been used in the future
    if (notfound > 1) {
      int min = 1000;
      // Looping through to find smallest address
      for (j = 0; j < associa; j++) {
        if (cache[j] < min) {
          min = cache[j];
          insert_loc = j;
        }
      }
    }
  }
  return insert_loc;
}

int main(int argc, char *argv[]) {
  // Find all values
  int associa = atoi(argv[1]);
  int set_size = 256 / associa;
  int cache[set_size][associa];
  char *algor = argv[2];

  // output
  printf("Cache size: 256\n");
  printf("Cache associativity: %d\n", associa);
  printf("Cache sets: %d\n", set_size);
  printf("Cache algorithm: %s\n", algor);

  // Open input file
  char const *const file = argv[3];
  FILE *myfile;
  myfile = fopen(file, "r");

  // initiliaze memory accesses
  int mem[10000];
  int mem_index = 0, tmp = 0;
  while (fscanf(myfile, "%d", &tmp) == 1) {
    mem[mem_index++] = tmp;
  }

  int x, y;
  for (x = 0; x < set_size; x++) {
    for (y = 0; y < associa; y++) {
      cache[x][y] = 0;
    }
  }

  // loop through all memory we need to access
  int i = 0, hit_count = 0;
  for (i = 0; i < mem_index; i++) {
    // Print the value and find the index
    printf("%d", mem[i]);
    int index = mem[i] % set_size;
    int j;
    for (j = 0; j < associa; j++) {
      // Hit
      if (mem[i] == cache[index][j]) {
        hit_count++;
        printf(" (hit)\n");
        break;
      }
      // Miss
      if (j == associa - 1) {
        printf(" (miss)\n");
        for (j = 0; j < associa; j++) {
          // insert if there is an empty spot
          if (cache[index][j] == 0) {
            cache[index][j] = mem[i];
            j = associa;
            break;
          }
          // Use LRU and Belady to find the place to insert when all full
          if (j == associa - 1) {
            cache[index][evict(cache[index], mem, i, associa, mem_index,
                               algor)] = mem[i];
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

  return EXIT_FAILURE;
}
