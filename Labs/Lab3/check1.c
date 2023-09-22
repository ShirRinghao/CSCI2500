#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *myfile = fopen("lab03-data.dat", "r");
  if (!myfile)
    return EXIT_FAILURE;

  // get the size
  fseek(myfile, 0, SEEK_END);
  long file_size = ftell(myfile);
  int *nums;
  nums = (int *)calloc(file_size + 1, sizeof(int));
  rewind(myfile);

  // get all data into array
  size_t result = fread(nums, sizeof(int), file_size, myfile);
  // print out the result
  int i;
  for (i = 0; i < result; i++) {
    printf("Data point # %3d: %d\n", i, nums[i]);
  }
  fclose(myfile);
  free(nums);
  return EXIT_SUCCESS;
}
