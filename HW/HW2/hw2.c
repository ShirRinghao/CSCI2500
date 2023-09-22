/* hw2.c */
/* NAME: <Linghao Shi> */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function that finds the location of a specific char
int check_loc(char alpha[], const char letter) {
  int i = 0;
  while (alpha[i] != '\0') {
    if (alpha[i] == letter) {
      return i;
    }
    i++;
  }
  return 1;
}

int main(int argc, char *argv[]) {
  char line[256];

  printf("Please enter a valid C assignment statement:\n");
  if (fgets(line, 256, stdin) == NULL) {
    fprintf(stderr, "fgets() failed");
    return EXIT_FAILURE;
  }

  printf("The MIPS pseudocode is:\n");
  // Do your magic here
  // Parsing all input
  char equation[256];
  char alpha[256];
  int num_arr[256];
  int i = 0, j = 0, num, tmp, num_count = 0, alpha_count = 0;
  int length = strlen(line);
  // Does not correct end up with ';'
  if (line[length - 2] != ';') {
    fprintf(stderr, "Parsing error...\n");
    return EXIT_FAILURE;
  }
  // Using a while loop to parse all input
  while (line[i] != ';') {
    // If it is a number
    if (isdigit(line[i]) != 0) {
      tmp = line[i] - '0';
      // If the number has more than one digits
      while (!isspace(line[i + 1]) && line[i + 1] != ';') {
        num = line[i + 1] - '0';
        tmp = tmp * 10 + num;
        i++;
      }
      // save the number
      equation[j] = '0';
      num_arr[num_count] = tmp;
      num_count++;
    }
    // If this is a space
    else if (isspace(line[i]) != 0) {
      i++;
      continue;
    }
    // If this is a char
    else {
      if (isalpha(line[i]) != 0) {
        // If the char has not been previously stored
        if (check_loc(alpha, line[i]) == 1) {
          alpha[alpha_count] = line[i];
          alpha_count++;
        }
      }
      // save the char
      equation[j] = line[i];
    }
    j++;
    i++;
  }
  equation[j] = '\0';
  alpha[alpha_count + 1] = '\0';

  // Error checking
  i = 0;
  while (equation[i] != '\0') {
    // First letter start with a constant
    if (isdigit(equation[0]) != 0) {
      fprintf(stderr, "Parsing error...\n");
      return EXIT_FAILURE;
    }
    // If there are consecutive chars with out operations in the middle
    if (isalpha(equation[i]) != 0 && i > 0) {
      if (isalpha(equation[i - 1]) != 0 || isdigit(equation[i - 1]) != 0) {
        fprintf(stderr, "Parsing error...\n");
        return EXIT_FAILURE;
      }
    }
    // If there are two consecutive operations
    if (equation[i] == '+' || equation[i] == '-' || equation[i] == '=' ||
        equation[i] == ';') {
      if (equation[i - 1] == '+' || equation[i - 1] == '-' ||
          equation[i - 1] == '=' || equation[i - 1] == ';') {
        fprintf(stderr, "Parsing error...\n");
        return EXIT_FAILURE;
      }
    }
    i++;
  }

  // Outputing results
  i = 2;
  num_count = 0;
  int count_tmp = 0;

  while (equation[i] != '\0') {
    // When i = 2, adding two values
    if (i == 2) {
      // First element is a number
      if (equation[i] == '0') {
        printf("addi $t0,$zero,%d\n", num_arr[num_count]);
        num_count++;
        // Second element is also a number
        if (equation[i + 2] == '0') {
          // only need to add two values
          if (equation[i + 3] == '\0') {
            printf("addi $s0,");
          } else {
            printf("addi $t1,");
          }
          // subtracting
          if (equation[i + 1] == '-') {
            printf("$t0,-%d\n", num_arr[num_count]);
          } else {
            printf("$t0,%d\n", num_arr[num_count]);
          }
          num_count++;
        }
        // second value is a char
        else if (islower(equation[i + 2]) != 0) {
          // subtracting
          if (equation[i + 1] == '-') {
            printf("sub  ");
          } else {
            printf("add  ");
          }
          // Only adding two values
          if (equation[i + 3] == '\0') {
            printf("$s0,");
          } else {
            printf("$t1,");
          }
          printf("$t0,$s%d\n", check_loc(alpha, equation[i + 2]));
        }
        count_tmp += 2;
      }

      // First element is a char
      if (islower(equation[i]) != 0) {
        // Second value is a number
        if (equation[i + 2] == '0') {
          printf("addi ");
          if (equation[i + 3] == '\0') {
            printf("$s0,");
          } else {
            printf("$t0,");
          }
          if (equation[i + 1] == '-') {
            printf("$s%d,-%d\n", check_loc(alpha, equation[i]),
                   num_arr[num_count]);
          } else {
            printf("$s%d,%d\n", check_loc(alpha, equation[i]),
                   num_arr[num_count]);
          }
          num_count++;
          count_tmp++;
        }
        // Second value is also a char
        if (islower(equation[i + 2]) != 0) {
          if (equation[i + 1] == '-') {
            printf("sub  ");
          } else {
            printf("add  ");
          }
          if (equation[i + 3] == '\0') {
            printf("$s0,");
          } else {
            printf("$t0,");
          }
          printf("$s%d,$s%d\n", check_loc(alpha, equation[i]),
                 check_loc(alpha, equation[i + 2]));
          count_tmp++;
        }
      }
      i += 2;
    }

    // Check if we are at the end of the equation
    if (equation[i + 1] == '\0') {
      break;
    }

    // Adding only one value (normal case)
    // operations sign
    if (equation[i + 1] == '-' && equation[i + 2] != '0') {
      printf("sub  ");
    } else if (equation[i + 2] == '0') {
      printf("addi ");
    } else {
      printf("add  ");
    }

    // If next value is a number
    if (equation[i + 2] == '0') {
      // If next element is the last element in the equation
      if (equation[i + 3] == '\0') {
        printf("$s0,");
      } else {
        //$t9 is used
        if (count_tmp == 10) {
          printf("$t0,");
        } else {
          printf("$t%d,", count_tmp);
        }
      }
      // Subracting and adding
      if (equation[i + 1] == '-') {
        printf("$t%d,-%d\n", count_tmp - 1, num_arr[num_count]);
      } else {
        printf("$t%d,%d\n", count_tmp - 1, num_arr[num_count]);
      }
      // check if we need to recycle $t0
      if (count_tmp == 10) {
        count_tmp = 0;
      }
      count_tmp++;
      num_count++;
    }

    // Next element is a char
    if (islower(equation[i + 2]) != 0) {
      // Next element is the last element in the equation
      if (equation[i + 3] == '\0') {
        printf("$s0,");
      } else {
        //$t9 is used
        if (count_tmp == 10) {
          printf("$t0,");
        } else {
          printf("$t%d,", count_tmp);
        }
      }
      printf("$t%d,$s%d\n", count_tmp - 1, check_loc(alpha, equation[i + 2]));
      // check if we need to recycle $t0
      if (count_tmp == 10) {
        count_tmp = 0;
      }
      count_tmp++;
    }

    i += 2;
  }

  return EXIT_SUCCESS;
}
