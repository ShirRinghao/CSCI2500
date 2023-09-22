#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_loc(char saved[], const char letter, int count_saved) {
  int i = 0;
  while (i < count_saved) {
    if (saved[i] == letter) {
      return i;
    }
    i++;
  }
  return count_saved;
}

int getExponent(int value, int *powers) {
  int size = 0, tmp = 0;
  while (value > 0) {
    tmp = value % 2;
    powers[size] = tmp;
    value = value / 2;
    size++;
  }
  return size;
}

int PowerOf2(int value) {
  int power = 0;
  while (value != 1) {
    if (value % 2 != 0) {
      return 0;
    }
    value = value / 2;
    power++;
  }
  return power;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Invalid input\n");
    return EXIT_FAILURE;
  }

  char const *const filename = argv[1];
  FILE *myfile = fopen(filename, "r");

  if (!myfile) {
    fprintf(stderr, "Error: Cannot open file!\n");
    return EXIT_FAILURE;
  }

  char line[128];
  char equation[128];
  int count_tmp = 0, total_saved = 0, countL = 0;
  char saved[10];
  while (fgets(line, sizeof(line), myfile)) {
    printf("# %s", line);
    int num_arr[128];
    int num_count = 0;

    // parse the input
    int i = 0, j = 0;
    while (line[i] != '\0') {
      if (!isspace(line[i])) {
        if (isdigit(line[i]) != 0) {
          int tmp = line[i] - '0';
          int num = 0;
          while (!isspace(line[i + 1]) && line[i + 1] != ';') {
            num = line[i + 1] - '0';
            tmp = tmp * 10 + num;
            i++;
          }
          num_arr[num_count] = tmp;
          equation[j] = '0';
          num_count++;
        } else {
          equation[j] = line[i];
          if (isalpha(line[i]) != 0) {
            // If the char has not been previously stored
            if (check_loc(saved, line[i], total_saved) == total_saved) {
              saved[total_saved] = line[i];
              total_saved++;
            }
          }
        }
        j++;
      }
      i++;
    }

    num_count = 0;
    // output
    // Load function
    if (equation[2] == '0' || equation[2] == '-') {
      if (equation[3] == ';') {
        printf("li $s%d,%d\n", check_loc(saved, equation[0], total_saved),
               num_arr[0]);
      } else {
        printf("li $s%d,-%d\n", check_loc(saved, equation[0], total_saved),
               num_arr[0]);
      }
      continue;
    }
    i = 2;
    do {
      // add and subtract
      if (equation[i + 1] == '+' || equation[i + 1] == '-') {
        // adding two values
        if (i == 2 && equation[i + 2] == '0') {
          printf("addi ");
          if (equation[i + 3] == ';') {
            printf("$s%d,", check_loc(saved, equation[0], total_saved));
          } else {
            if (count_tmp == 10) {
              count_tmp = 0;
            }
            printf("$t%d,", count_tmp);
            count_tmp++;
          }
          if (equation[i + 1] == '-') {
            printf("$s%d,-%d\n", check_loc(saved, equation[i], total_saved),
                   num_arr[num_count]);
          } else {
            printf("$s%d,%d\n", check_loc(saved, equation[i], total_saved),
                   num_arr[num_count]);
          }
          num_count++;
          if (equation[i + 3] == ';') {
            break;
          }
          i += 2;
          continue;
        } else if (i == 2 && isalpha(equation[i + 2]) != 0) {
          if (equation[i + 1] == '-') {
            printf("sub ");
          } else {
            printf("add ");
          }
          if (equation[i + 3] == ';') {
            printf("$s%d,", check_loc(saved, equation[0], total_saved));
          } else {
            if (count_tmp == 10) {
              count_tmp = 0;
            }
            printf("$t%d,", count_tmp);
            count_tmp++;
          }
          printf("$s%d,$s%d\n", check_loc(saved, equation[i], total_saved),
                 check_loc(saved, equation[i + 2], total_saved));
          i += 2;
          continue;
        }

        // regular case
        if (equation[i + 1] == '-') {
          if (islower(equation[i + 2]) != 0) {
            printf("sub ");
          } else if (equation[i + 2] == '0') {
            printf("addi ");
          }
        }
        if (equation[i + 1] == '+') {
          if (equation[i + 2] == '0') {
            printf("addi ");
          } else {
            printf("add ");
          }
        }

        if (equation[i + 2] == '0') {
          if (equation[i + 3] == ';') {
            printf("$s%d,", check_loc(saved, equation[0], total_saved));
          } else {
            //$t9 is used
            if (count_tmp == 10) {
              printf("$t0,");
            } else {
              printf("$t%d,", count_tmp);
            }
          }
          if (equation[i + 1] == '-') {
            printf("$t%d,-%d\n", count_tmp - 1, num_arr[num_count]);
          } else {
            printf("$t%d,%d\n", count_tmp - 1, num_arr[num_count]);
          }
          // check if we need to recycle to $t0
          if (count_tmp == 10) {
            count_tmp = 0;
          }
          count_tmp++;
          num_count++;
        } else if (islower(equation[i + 2]) != 0) {
          if (equation[i + 3] == ';') {
            printf("$s%d,", check_loc(saved, equation[0], total_saved));
          } else {
            //$t9 is used
            if (count_tmp == 10) {
              printf("$t0,");
            } else {
              printf("$t%d,", count_tmp);
            }
          }
          printf("$t%d,$s%d\n", count_tmp - 1,
                 check_loc(saved, equation[i + 2], total_saved));
          // check if we need to recycle $t0
          if (count_tmp == 10) {
            count_tmp = 0;
          }
          count_tmp++;
        }
        if (equation[i + 3] == ';') {
          count_tmp--;
        }
        i += 2;
        continue;
      }

      // mod
      if (equation[i + 1] == '%') {
        // constant
        if (equation[i + 2] == '0' || equation[i + 3] == '0') {
          // negative number
          if (equation[i + 2] == '-') {
            printf("li $t%d,-%d\n", count_tmp, num_arr[num_count++]);
            i++;
          }
          // positive number
          else {
            printf("li $t%d,%d\n", count_tmp, num_arr[num_count++]);
          }
          if (i == 2) {
            printf("div $s%d,$t%d\n",
                   check_loc(saved, equation[i], total_saved), count_tmp);
          } else {
            // recycle
            if (count_tmp == 10 || count_tmp == 0) {
              printf("div $t9,$t0\n");
              count_tmp = 0;
            }
            // regular case
            else {
              printf("div $t%d,$t%d\n", count_tmp - 1, count_tmp);
            }
          }
          count_tmp++;
          if (count_tmp == 10) {
            count_tmp = 0;
          }
          if (equation[i + 3] == ';') {
            printf("mfhi $s%d\n", check_loc(saved, equation[0], total_saved));
          } else {
            printf("mfhi $t%d\n", check_loc(saved, equation[0], total_saved));
          }
        }
        // variable
        else if (isalpha(equation[i + 2]) != 0 && equation[i + 2] != '-') {
          if (i == 2) {
            printf("div $s%d,$s%d\n",
                   check_loc(saved, equation[i], total_saved),
                   check_loc(saved, equation[i + 2], total_saved));
          } else {
            printf("div $t%d,$s%d\n", count_tmp - 1,
                   check_loc(saved, equation[i + 2], total_saved));
          }
          if (count_tmp == 10) {
            count_tmp = 0;
          }
          if (equation[i + 3] == ';') {
            printf("mfhi $s%d\n", check_loc(saved, equation[0], total_saved));
          } else {
            printf("mfhi $t%d\n", count_tmp++);
          }
        }
        if (count_tmp == 10) {
          count_tmp = 0;
        }
        i += 2;
        continue;
      }

      // divison
      if (equation[i + 1] == '/') {
        if (isalpha(equation[i + 2]) != 0) {
          printf("div ");
          if (i == 2) {
            printf("$s%d,", check_loc(saved, equation[i], total_saved));
          } else {
            printf("$t%d,", count_tmp - 1);
          }
          printf("$s%d\n", check_loc(saved, equation[i + 2], total_saved));
          if (equation[i + 3] == ';') {
            printf("mflo $s%d\n", check_loc(saved, equation[0], total_saved));
          } else {
            if (count_tmp == 10) {
              count_tmp = 0;
              printf("mflo $t0\n");
            } else {
              printf("mflo $t%d\n", count_tmp);
            }
            count_tmp++;
          }
        } else if (equation[i + 2] == '0' || equation[i + 3] == '0') {
          // negative number
          if (equation[i + 3] == '0' && equation[i + 2] == '-') {
            // Negative 1
            if (num_arr[num_count] == 1) {
              // end of a line
              if (equation[i + 4] == ';') {
                printf("sub $s%d,", check_loc(saved, equation[0], total_saved));
                if (i == 2) {
                  printf("$zero,$s%d\n",
                         check_loc(saved, equation[i], total_saved));
                } else {
                  printf("$zero,$t%d\n", count_tmp - 1);
                }
              } else {
                if (count_tmp == 10) {
                  printf("sub $t0,");
                  count_tmp = 0;
                } else {
                  printf("sub $t%d,", count_tmp);
                }
                if (i == 2) {
                  printf("$zero,$s%d\n",
                         check_loc(saved, equation[0], total_saved));
                } else {
                  printf("$zero,$t%d\n", count_tmp - 1);
                }
                count_tmp++;
              }
              if (count_tmp == 10) {
                count_tmp = 0;
              }
              num_count++;
            }

            // other negative numbers
            else if (num_arr[num_count] > 0) {
              int power = PowerOf2(num_arr[num_count]);
              if (power != 0) {
                if (i == 2) {
                  printf("bltz $s%d,L%d\n",
                         check_loc(saved, equation[i], total_saved), countL);
                } else {
                  printf("bltz $t%d,L%d\n", count_tmp - 1, countL);
                }
                if (equation[i + 4] == ';') {
                  if (i == 2) {
                    printf("srl $s%d,$s%d,%d\n",
                           check_loc(saved, equation[0], total_saved),
                           check_loc(saved, equation[i], total_saved), power);
                    printf("sub $s%d,$zero,$s%d\nj L%d\n",
                           check_loc(saved, equation[0], total_saved),
                           check_loc(saved, equation[0], total_saved),
                           countL + 1);
                  } else {
                    printf("srl $t%d,$t%d,%d\n", count_tmp + 1, count_tmp,
                           power);
                    printf("sub $t%d,$zero,$t%d\nj L%d\n", count_tmp, count_tmp,
                           countL + 1);
                    count_tmp++;
                    if (count_tmp == 10) {
                      count_tmp = 0;
                    }
                  }
                } else {
                  if (i == 2) {
                    printf("srl $t%d,$s%d,%d\n", count_tmp,
                           check_loc(saved, equation[i], total_saved), power);
                    printf("sub $t%d,$zero,$t%d\nj L%d\n", count_tmp, count_tmp,
                           countL + 1);
                  } else {
                    printf("srl $t%d,$t%d,%d\n", count_tmp, count_tmp - 1,
                           power);
                    printf("sub $t%d,$zero,$t%d\nj L%d\n", count_tmp, count_tmp,
                           countL + 1);
                  }
                  count_tmp++;
                  if (count_tmp == 10) {
                    count_tmp = 0;
                  }
                }
                printf("L%d:\nli $t%d,-%d\n", countL, count_tmp,
                       num_arr[num_count]);
                if (i == 2) {
                  printf("div $s%d,$t%d\n",
                         check_loc(saved, equation[i], total_saved),
                         count_tmp++);
                } else {
                  printf("div $t%d,$t%d\n", count_tmp + 1, count_tmp);
                  count_tmp++;
                }
                if (equation[i + 4] == ';') {
                  printf("mflo $s%d\nL%d:\n",
                         check_loc(saved, equation[0], total_saved),
                         countL + 1);
                } else {
                  printf("mflo $t%d\nL%d:\n", count_tmp++, countL + 1);
                }
                countL += 2;
              } else {
                printf("li $t%d,-%d\n", count_tmp, num_arr[num_count]);
                if (i == 2) {
                  printf("div $s%d,$t%d\n",
                         check_loc(saved, equation[i], total_saved), count_tmp);
                } else {
                  printf("div $t%d,$t%d\n", count_tmp + 1, count_tmp);
                  count_tmp++;
                }
                if (equation[i + 4] == ';') {
                  printf("mflo $s%d\n",
                         check_loc(saved, equation[0], total_saved));
                } else {
                  count_tmp++;
                  if (count_tmp == 10) {
                    count_tmp = 0;
                  }
                  printf("mflo $t%d\n", count_tmp++);
                  if (count_tmp == 10) {
                    count_tmp = 0;
                  }
                }
              }
              num_count++;
            }
            i++;
          }
          // positive number
          else if (isdigit(equation[i + 2]) != 0) {
            // positive 1
            if (num_arr[num_count] == 1) {
              if (equation[i + 3] == ';') {
                if (i == 2) {
                  printf("move $s%d,$s%d\n",
                         check_loc(saved, equation[0], total_saved),
                         check_loc(saved, equation[i], total_saved));
                } else {
                  printf("move $s%d,$t%d\n",
                         check_loc(saved, equation[0], total_saved),
                         count_tmp - 1);
                }
              } else {
                if (i == 2) {
                  printf("move $t%d,$s%d\n", count_tmp++,
                         check_loc(saved, equation[i], total_saved));
                } else {
                  printf("move $t%d,$t%d\n", count_tmp + 1, count_tmp);
                  count_tmp++;
                }
              }
              num_count++;
            }

            // other positive numbers
            else if (num_arr[num_count] > 0) {
              int power = PowerOf2(num_arr[num_count]);
              // a power of 2
              if (power != 0) {
                if (i == 2) {
                  printf("bltz $s%d,L%d\n",
                         check_loc(saved, equation[i], total_saved), countL);
                } else {
                  printf("bltz $t%d,L%d\n", count_tmp - 1, countL);
                }
                if (equation[i + 3] == ';') {
                  if (i == 2) {
                    printf("srl $s%d,$s%d,%d\nj L%d\n",
                           check_loc(saved, equation[0], total_saved),
                           check_loc(saved, equation[i], total_saved), power,
                           countL + 1);
                  } else {
                    printf("srl $s%d,$t%d,%d\nj L%d\n",
                           check_loc(saved, equation[0], total_saved),
                           count_tmp - 1, power, countL + 1);
                  }
                } else {
                  if (i == 2) {
                    printf("srl $t%d,$s%d,%d\nj L%d\n", count_tmp,
                           check_loc(saved, equation[i], total_saved), power,
                           countL + 1);
                  } else {
                    printf("srl $t%d,$t%d,%d\nj L%d\n", count_tmp,
                           count_tmp - 1, power, countL + 1);
                  }
                  count_tmp++;
                  if (count_tmp == 10) {
                    count_tmp = 0;
                  }
                }
                printf("L%d:\nli $t%d,%d\n", countL, count_tmp,
                       num_arr[num_count]);
                if (i == 2) {
                  printf("div $s%d,$t%d\n",
                         check_loc(saved, equation[i], total_saved),
                         count_tmp++);
                } else {
                  printf("div $t%d,$t%d\n", count_tmp - 1, count_tmp);
                  count_tmp++;
                }
                if (equation[i + 3] == ';') {
                  printf("mflo $s%d\nL%d:\n",
                         check_loc(saved, equation[0], total_saved),
                         countL + 1);
                } else {
                  printf("mflo $t%d\nL%d:\n", count_tmp, countL + 1);
                }
                countL += 2;
                num_count++;
              }
              // not a power of 2
              else {
                printf("li $t%d,%d\n", count_tmp, num_arr[num_count]);
                if (i == 2) {
                  printf("div $s%d,$t%d\n",
                         check_loc(saved, equation[i], total_saved), count_tmp);
                } else {
                  printf("div $t%d,$t%d\n", count_tmp - 1, count_tmp);
                }
                if (equation[i + 3] == ';') {
                  printf("mflo $s%d\n",
                         check_loc(saved, equation[0], total_saved));
                } else {
                  count_tmp++;
                  if (count_tmp == 10) {
                    count_tmp = 0;
                  }
                  printf("mflo $t%d\n", count_tmp++);
                  if (count_tmp == 10) {
                    count_tmp = 0;
                  }
                  num_count++;
                }
              }
            }
          }
        }
        i += 2;
        continue;
      }

      // multiplication
      if (equation[i + 1] == '*') {
        if (i == 2) {
          // multiplication of two variables
          if (equation[i + 2] != '-' && isalpha(equation[i + 2]) != 0) {
            printf("mult $s%d,$s%d\n",
                   check_loc(saved, equation[i], total_saved),
                   check_loc(saved, equation[i + 2], total_saved));
            // only two terms
            if (equation[i + 3] == ';') {
              printf("mflo $s%d\n", check_loc(saved, equation[0], total_saved));
            } else {
              if (count_tmp == 10) {
                count_tmp = 0;
              }
              printf("mflo $t%d\n", count_tmp++);
            }
            i += 2;
            continue;
          }
          // variable to the power of...
          else {
            int *powers = malloc(32 * sizeof(int));
            if (equation[i + 2] == '0' &&
                (num_arr[0] == 0 || num_arr[0] == 1)) {
              // to the power of 0
              if (num_arr[0] == 0) {
                if (equation[i + 3] == ';') {
                  printf("li $s%d,0\n",
                         check_loc(saved, equation[0], total_saved));
                } else {
                  printf("li $t%d,0\n", count_tmp++);
                }
              } else if (num_arr[0] == 1) {
                printf("move $t%d,$s%d\n", count_tmp++,
                       check_loc(saved, equation[i], total_saved));
                if (equation[i + 3] == ';') {
                  printf("move $s%d,$t%d\n",
                         check_loc(saved, equation[0], total_saved),
                         count_tmp - 1);
                  if (count_tmp == 10) {
                    count_tmp = 0;
                  }
                  break;
                } else {
                  if (count_tmp == 10) {
                    count_tmp = 0;
                  }
                }
              }
            } else if (equation[i + 2] == '-' && num_arr[num_count] == 1) {
              // multiplying by -1
              printf("move $t%d,$s%d\n", count_tmp++,
                     check_loc(saved, equation[i], total_saved));
              if (equation[i + 4] == ';') {
                printf("sub $s%d,$zero,$t%d\n",
                       check_loc(saved, equation[0], total_saved),
                       count_tmp - 1);
                if (count_tmp == 10) {
                  count_tmp = 0;
                }
                break;
              } else {
                printf("sub $t%d,$zero,$t%d\n", count_tmp, count_tmp - 1);
                printf("move $t%d,$t%d\n", count_tmp, count_tmp - 1);
                if (count_tmp == 10) {
                  count_tmp = 0;
                }
                count_tmp++;
              }
              i++;
            }

            else if (num_arr[0] > 1) {
              int size = getExponent(num_arr[0], powers);
              int shift_count, loc = 0;
              for (shift_count = size - 1; shift_count >= 0;
                   shift_count--, loc++) {
                // at first index
                if (loc == 0) {
                  if (count_tmp == 10) {
                    printf("sll $t0,$s%d,%d\n",
                           check_loc(saved, equation[i], total_saved),
                           shift_count);
                  } else {
                    printf("sll $t%d,$s%d,%d\n", count_tmp,
                           check_loc(saved, equation[i], total_saved),
                           shift_count);
                  }
                  printf("move $t%d,$t%d\n", count_tmp + 1, count_tmp);
                }
                // at last index and if it is a 1
                else if (shift_count == 0 && powers[0] == 1) {
                  printf("add $t%d,$t%d,$s%d\n", count_tmp + 1, count_tmp + 1,
                         check_loc(saved, equation[i], total_saved));
                }
                // any other index we need to print
                else if (powers[shift_count] == 1) {
                  printf("sll $t%d,$s%d,%d\n", count_tmp,
                         check_loc(saved, equation[i], total_saved),
                         shift_count);
                  printf("add $t%d,$t%d,$t%d\n", count_tmp + 1, count_tmp + 1,
                         count_tmp);
                }
              }
              // multiplying by a negative number
              if (equation[i + 2] == '-' && num_arr[0] > 1) {
                if (equation[i + 4] == ';') {
                  printf("sub $s%d,$zero,$t%d\n",
                         check_loc(saved, equation[0], total_saved),
                         count_tmp + 1);
                } else {
                  printf("sub $t%d,$zero,$t%d\n", count_tmp + 2, count_tmp + 1);
                  count_tmp++;
                }
                count_tmp++;
                i++;
              }
              // mulitplying a positive number
              else if (equation[i + 2] == '0' && num_arr[0] > 1) {
                if (equation[i + 3] == ';') {
                  printf("move $s%d,$t%d\n",
                         check_loc(saved, equation[0], total_saved),
                         count_tmp + 1);
                } else {
                  printf("move $t%d,$t%d\n", count_tmp + 2, count_tmp + 1);
                  count_tmp++;
                }
                count_tmp++;
              }
              count_tmp++;
              if (count_tmp == 10) {
                count_tmp = 0;
              }
            }
            num_count++;
            i += 2;
            continue;
          }
        }

        // regular case, mulitplying to one term
        if (equation[i + 3] == '0' || equation[i + 2] == '0') {
          // dealing with 1
          if (num_arr[num_count] == 1) {
            // negative 1
            if (equation[i + 2] == '-') {
              printf("move $t%d,$t%d\n", count_tmp + 1, count_tmp);
              count_tmp++;
              if (equation[i + 4] == ';') {
                printf("sub $s%d,$zero,$t%d\n",
                       check_loc(saved, equation[0], total_saved),
                       count_tmp - 1);
                if (count_tmp == 10) {
                  count_tmp = 0;
                }
              } else {
                printf("sub $t%d,$zero,$t%d\n", count_tmp, count_tmp - 1);
                count_tmp++;
                if (count_tmp == 10) {
                  count_tmp = 0;
                }
              }
              i++;
            }
            // positive 1
            else if (equation[i + 2] == '0') {
              printf("move $t%d,$t%d\n", count_tmp, count_tmp - 1);
              count_tmp++;
              if (equation[i + 3] == ';') {
                printf("move $s%d,$t%d\n",
                       check_loc(saved, equation[0], total_saved),
                       count_tmp - 1);
                if (count_tmp == 10) {
                  count_tmp = 0;
                }
              } else {
                if (count_tmp == 10) {
                  count_tmp = 0;
                }
              }
            }
            num_count++;
          } else if (num_arr[num_count] == 0) {
            if (equation[i + 3] == ';') {
              printf("li $s%d,0\n", check_loc(saved, equation[0], total_saved));
              num_count++;
              break;
            } else {
              printf("li $t%d,0\n", count_tmp++);
            }
            // added
            num_count++;
          }
          // other numbers
          else if (num_arr[num_count] > 1) {
            int *powers = malloc(32 * sizeof(int));
            int size = getExponent(num_arr[num_count], powers);
            int loc = 0, shift_count;
            for (shift_count = size - 1; shift_count >= 0;
                 shift_count--, loc++) {
              // at first index
              if (loc == 0) {
                if (count_tmp == 10) {
                  printf("sll $t0,$t9,%d\n", shift_count);
                } else {
                  printf("sll $t%d,$t%d,%d\n", count_tmp, count_tmp - 1,
                         shift_count);
                }
                if (count_tmp == 9) {
                  printf("move $t0,$t9\n");
                  count_tmp = 0;
                } else {
                  printf("move $t%d,$t%d\n", count_tmp + 1, count_tmp);
                }
                continue;
              }
              // at last index and if it is a 1
              else if (shift_count == 0 && powers[0] == 1) {
                if (count_tmp == 8) {
                  printf("add $t0,$t0,$t8\n");
                  count_tmp = 0;
                } else if (count_tmp == 9) {
                  printf("add $t1,$t1,$t9\n");
                  count_tmp = 1;
                } else if (count_tmp == 0) {
                  printf("add $t1,$t1,$t9\n");
                } else {
                  printf("add $t%d,$t%d,$t%d\n", count_tmp + 1, count_tmp + 1,
                         count_tmp - 1);
                }
              }
              // any other index we need to print
              else if (powers[shift_count] == 1) {
                printf("sll $t%d,$t%d,%d\n", count_tmp, count_tmp - 1,
                       shift_count);
                printf("add $t%d,$t%d,$t%d\n", count_tmp + 1, count_tmp + 1,
                       count_tmp);
              }
            }
            count_tmp++;
            // multiplying by a negative number
            if (equation[i + 2] == '-') {
              if (equation[i + 4] == ';') {
                printf("sub $s%d,$zero,$t%d\n",
                       check_loc(saved, equation[0], total_saved),
                       count_tmp - 1);
                if (count_tmp == 10) {
                  count_tmp = 0;
                }
                break;
              } else {
                if (count_tmp == 10) {
                  printf("sub $t1,$zero,$t0\n");
                  count_tmp = 1;
                } else if (count_tmp == 9) {
                  printf("sub $t0,$zero,$t9\n");
                  count_tmp = 0;
                } else {
                  printf("sub $t%d,$zero,$t%d\n", count_tmp + 1, count_tmp);
                }
                count_tmp++;
              }
              i++;
            }
            // mulitplying a positive number
            else if (equation[i + 2] == '0') {
              if (equation[i + 3] == ';') {
                if (count_tmp == 10) {
                  count_tmp = 0;
                }
                printf("move $s%d,$t%d\n",
                       check_loc(saved, equation[0], total_saved),
                       count_tmp - 1);
                break;
              } else {
                if (count_tmp == 10) {
                  count_tmp = 0;
                  printf("move $t0,$t9\n");
                } else {
                  printf("move $t%d,$t%d\n", count_tmp + 1, count_tmp);
                  count_tmp++;
                }
              }
            }
            if (count_tmp == 10) {
              count_tmp = 0;
            }
            count_tmp++;
            num_count++;
          }
        } else if (isalpha(equation[i + 2]) != 0) {
          printf("mult $t%d,$s%d\n", count_tmp - 1,
                 check_loc(saved, equation[i + 2], total_saved));
          if (equation[i + 3] == ';') {
            printf("mflo $s%d\n", check_loc(saved, equation[0], total_saved));
          } else {
            if (count_tmp == 10) {
              count_tmp = 0;
            }
            printf("mflo $t%d\n", count_tmp++);
          }
        }
        i += 2;
        continue;
      }
    } while (equation[i + 1] != ';' && equation[i + 1] != '\0');
  }
  return EXIT_SUCCESS;
}
