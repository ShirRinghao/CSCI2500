/* hw1.c */
/* NAME: Linghao (Jerry) SHi */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  /* Ensure we have the correct number of command-line arguments */
  if (argc != 5) {
    fprintf(stderr, "ERROR: Invalid inputs!\n");
    return EXIT_FAILURE;
  }

  // Get the size of the two matrix
  int first_row = atoi(argv[1]), first_col = atoi(argv[2]),
      second_row = atoi(argv[3]), second_col = atoi(argv[4]);

  // Create two int array to store matrix
  int first_matrix[first_row][first_col];
  int second_matrix[second_row][second_col];
  int count_row, count_col;
  int length1[first_col], length2[second_col], length3[second_col];

  // initialize the array that stores the longest length of each column
  for (count_row = 0; count_row < first_col; count_row++) {
    length1[count_row] = 0;
  }
  for (count_col = 0; count_col < second_col; count_col++) {
    length2[count_col] = 0;
    length3[count_col] = 0;
  }

  // Error checking of two matrix multiplication
  if (first_row < 1 || first_col < 1 || second_row < 1 || second_col < 1 ||
      first_col != second_row) {
    fprintf(stderr, "ERROR: Invalid inputs!\n");
    return EXIT_FAILURE;
  }
  // Reading data input
  printf("Please enter the values for the first matrix (%dx%d):\n", first_row,
         first_col);
  // Get all values of the first matrix
  for (count_row = 0; count_row < first_row; count_row++) {
    for (count_col = 0; count_col < first_col; count_col++) {
      // initialize it, then store the number from input
      first_matrix[count_row][count_col] = 0;
      scanf("%d", &first_matrix[count_row][count_col]);
      if (first_matrix[count_row][count_col] < 0) {
        fprintf(stderr, "ERROR: Invalid inputs!\n");
        return EXIT_FAILURE;
      }
      // Check if it is a number that has more digits
      int tmp_length =
          floor(log10(abs(first_matrix[count_row][count_col]))) + 1;
      if (length1[count_col] < tmp_length) {
        length1[count_col] = tmp_length;
      }
    }
  }

  printf("Please enter the values for the second matrix (%dx%d):\n\n",
         second_row, second_col);
  // Get all values of the second matrix
  for (count_row = 0; count_row < second_row; count_row++) {
    for (count_col = 0; count_col < second_col; count_col++) {
      // initialize it, then store the number from input
      second_matrix[count_row][count_col] = 0;
      scanf("%d", &second_matrix[count_row][count_col]);
      if (second_matrix[count_row][count_col] < 0) {
        fprintf(stderr, "ERROR: Invalid inputs!\n");
        return EXIT_FAILURE;
      }
      // Check if it is a number that has more digits
      int tmp_length =
          floor(log10(abs(second_matrix[count_row][count_col]))) + 1;
      if (length2[count_col] < tmp_length) {
        length2[count_col] = tmp_length;
      }
    }
  }
  // Calculation
  int result[first_row][second_col];
  int i, j;

  for (count_row = 0; count_row < first_row; count_row++) {
    for (i = 0; i < second_col; i++) {
      result[count_row][i] = 0;
      for (j = 0; j < first_col; j++) {
        result[count_row][i] +=
            first_matrix[count_row][j] * second_matrix[j][i];
        int tmp_length = floor(log10(abs(result[count_row][i]))) + 1;
        if (length3[i] < tmp_length) {
          length3[i] = tmp_length;
        }
      }
    }
  }

  // printing out two inital matrix
  for (count_row = 0; count_row < first_row; count_row++) {
    printf("[");
    for (count_col = 0; count_col < first_col; count_col++) {
      if (count_col != 0)
        printf(" ");
      printf("%*d", length1[count_col], first_matrix[count_row][count_col]);
    }
    printf("]\n");
  }
  printf("multiplied by\n");
  for (count_row = 0; count_row < second_row; count_row++) {
    printf("[");
    for (count_col = 0; count_col < second_col; count_col++) {
      if (count_col != 0)
        printf(" ");
      printf("%*d", length2[count_col], second_matrix[count_row][count_col]);
    }
    printf("]\n");
  }

  // Printing out the results
  printf("equals\n");
  for (count_row = 0; count_row < first_row; count_row++) {
    printf("[");
    for (count_col = 0; count_col < second_col; count_col++) {
      if (count_col != 0)
        printf(" ");
      printf("%*d", length3[count_col], result[count_row][count_col]);
    }
    printf("]\n");
  }
  return EXIT_SUCCESS;
}
