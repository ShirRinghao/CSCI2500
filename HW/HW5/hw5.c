#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print() {
  printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
  return;
}

int check(int nop[5][2], int i) {
  int j = 0;
  for (; j < 4; j++) {
    if (nop[j][0] == i && nop[j][1] == 2) {
      return 2;
    }
  }
  return 0;
}

void set_stage(char *stages[5][9], int i, int nop[5][2], char instruc[5][128],
               int nop_add) {
  int j = i + 2;
  for (; j < i + 5; j++) {
    stages[i][j] = "*";
  }
  if (nop[nop_add][1] == 2) {
    stages[i + 1][i] = "IF";
    stages[i + 1][i + 1] = "ID";
    stages[i + 1][i + 2] = "ID";
    stages[i + 1][i + 3] = "*";
    stages[i + 1][i + 4] = "*";
    stages[i + 1][i + 5] = "*";
    int k = i + 6;
    for (; k < 8; k++) {
      stages[i + 1][k] = ".";
    }
    i += 2;
    k = i;
    for (; i < 5; i++) {
      for (j = i - 2; j < 8; j++) {
        stages[i][j - 2] = stages[i][j];
      }
    }
    i = k;
    for (; i < 5; i++) {
      for (j = i - 2; j < 8; j++) {
        if (strcmp(stages[i - 1][j - 1], "*") &&
            !strcmp(stages[i - 1][j], "*")) {
          stages[i][j] = stages[i - 1][j - 1];
        } else if (!strcmp(stages[i - 1][j - 1], stages[i - 1][j]) &&
                   strcmp(stages[i - 1][j - 1], "*")) {
          stages[i][j] = stages[i][j - 1];
        } else if (!strcmp(stages[i - 1][j - 1], "*") &&
                   !strcmp(stages[i - 1][j], "*")) {
          if (!strcmp(stages[i][j - 1], "EX")) {
            stages[i][j] = "MEM";
          } else if (!strcmp(stages[i][j - 1], "MEM")) {
            stages[i][j] = "WB";
          } else if (!strcmp(stages[i][j - 1], "ID")) {
            stages[i][j] = "EX";
          } else if (!strcmp(stages[i][j - 1], "IF")) {
            stages[i][j] = "ID";
          }
        } else {
          if (!strcmp(stages[i][j - 1], "EX")) {
            stages[i][j] = "MEM";
          } else if (!strcmp(stages[i][j - 1], "MEM")) {
            stages[i][j] = "WB";
          } else if (!strcmp(stages[i][j - 1], "ID")) {
            stages[i][j] = "EX";
          } else if (!strcmp(stages[i][j - 1], "IF")) {
            stages[i][j] = "ID";
          }
        }
      }
    }
    // i += 2;
    // int count = i;
    // for (; i < 5; i++) {
    //   for (j = i - 2; j < 8; j++) {
    //     if (!strcmp(stages[i - 1][j - 2], "*") &&
    //         !strcmp(stages[i - 1][j - 1], "*")) {
    //       stages[i][j - 2] = stages[i][j - 3];
    //     } else if (!strcmp(stages[i - 1][j - 2], "*") &&
    //                strcmp(stages[i - 1][j - 1], "*")) {
    //       stages[i][j - 2] = "EX";
    //       stages[i][j - 1] = "MEM";
    //       stages[i][j] = "WB";
    //       // } else if (!strcmp(stages[i - 2][count], "*") &&
    //       //            strcmp(stages[i - 2][count - 1], "*")) {
    //       //   stages[i - 1][count] = stages[i - 2][count - 1];
    //     } else {
    //       stages[i][j - 2] = stages[i][j];
    //     }
    //   }
    // }
    // for (; count < 9; count++) {
    //   if (!strcmp(stages[i - 2][count - 1], stages[i - 2][count])) {
    //     stages[i - 1][count] = stages[i - 1][count - 1];
    //   } else {
    //     if (!strcmp(stages[i - 2][count], "EX")) {
    //       stages[i - 1][count] = "ID";
    //     } else if (!strcmp(stages[i - 2][count], "MEM")) {
    //       stages[i - 1][count] = "EX";
    //     } else if (!strcmp(stages[i - 2][count], "WB")) {
    //       stages[i - 1][count] = "MEM";
    //     }
    //   }
    // }
    // stages[i - 1][count - 1] = "WB";
  } else if (nop[nop_add][1] == 1) {
    i++;
    for (; i < 5; i++) {
      for (j = 1; j < 9; j++) {
        if (!strcmp(stages[i - 1][j], "*") &&
            strcmp(stages[i - 1][j - 1], "*")) {
          int tmp = 8;
          for (; tmp > j; tmp--) {
            stages[i][tmp] = stages[i][tmp - 1];
          }
          j = tmp;
          stages[i][j] = stages[i][j - 1];
        } else {
          stages[i][j] = stages[i][j + 1];
        }
      }
    }
  }
  i = 4;
  for (j = 0; j < 9; j++) {
    if (!strcmp(stages[i][j], "MEM")) {
      stages[i][j + 1] = "WB";
    }
    if (!strcmp(stages[i - 1][j], "WB")) {
      for (int count = j + 2; count < 9; count++) {
        stages[i][count] = ".";
      }
      break;
    }
  }
}

void move_instruction(char *stages[5][9], int loc, int add,
                      char instruc[5][128]) {
  int i, j = 0;
  char temp[5][128];
  for (i = loc; i < 5; i++, j++) {
    int k = 0;
    while (instruc[i][k] != '\0') {
      temp[j][k] = instruc[i][k];
      k++;
    }
    temp[j][k] = '\0';
  }
  instruc[loc][0] = 'n';
  instruc[loc][1] = 'o';
  instruc[loc][2] = 'p';
  instruc[loc][3] = '\t';
  instruc[loc][4] = '\0';
  if (add == 2) {
    instruc[loc + 1][0] = 'n';
    instruc[loc + 1][1] = 'o';
    instruc[loc + 1][2] = 'p';
    instruc[loc + 1][3] = '\t';
    instruc[loc + 1][4] = '\0';
  }
  j = 0;
  for (i = loc + add; i < 5; i++, j++) {
    int k = 0;
    while (temp[j][k] != '\0') {
      instruc[i][k] = temp[j][k];
      k++;
    }
  }
  return;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Invalid usage\n");
    return EXIT_FAILURE;
  }

  char const *const file = argv[1];
  FILE *myfile;
  myfile = fopen(file, "r");

  if (!myfile) {
    fprintf(stderr, "Error: Cannot open file!\n");
    return EXIT_FAILURE;
  }

  char line[128];
  char instruc[5][128];
  char reg[5][3];
  char *stages[5][9];
  int i, j, flag = 0, reg_count = 0, nop_count = 0, nop_add = 0, nop[5][2];
  // initialize all stages
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 9; j++) {
      if ((i == 0 && j == 0) || (i == 1 && j == 1) || (i == 2 && j == 2) ||
          (i == 3 && j == 3) || (i == 4 && j == 4)) {
        stages[i][j] = "IF";
      } else if ((i == 0 && j == 1) || (i == 1 && j == 2) ||
                 (i == 2 && j == 3) || (i == 3 && j == 4) ||
                 (i == 4 && j == 5)) {
        stages[i][j] = "ID";
      } else if ((i == 0 && j == 2) || (i == 1 && j == 3) ||
                 (i == 2 && j == 4) || (i == 3 && j == 5) ||
                 (i == 4 && j == 6)) {
        stages[i][j] = "EX";
      } else if ((i == 0 && j == 3) || (i == 1 && j == 4) ||
                 (i == 2 && j == 5) || (i == 3 && j == 6) ||
                 (i == 4 && j == 7)) {
        stages[i][j] = "MEM";
      } else if ((i == 0 && j == 4) || (i == 1 && j == 5) ||
                 (i == 2 && j == 6) || (i == 3 && j == 7) ||
                 (i == 4 && j == 8)) {
        stages[i][j] = "WB";
      } else {
        stages[i][j] = ".";
      }
    }
  }

  i = 0, j = 0;
  int cycle_count = 4, instruc_count = 0;
  // parse the input
  while (fgets(line, sizeof(line), myfile)) {
    instruc_count++;
    j = 0, flag = 0;
    int iftrue = 0;
    // check the first register
    while (line[j] != '\n') {
      instruc[i][j] = line[j];
      // regiter that needs to be stored
      if (line[j] == '$' && flag == 0) {
        reg[reg_count][0] = line[j + 1];
        reg[reg_count][1] = line[j + 2];
        reg[reg_count][2] = '\0';
        reg_count++;
        iftrue = 1;
      }
      // register that needs to be check for nop instruction
      if (line[j] == '$' && flag == 1 && i != 0 && instruc_count < 5) {
        int k, temp = 0;
        for (k = 0; k < reg_count; k++) {
          if (line[j + 1] == reg[k][0] && line[j + 2] == reg[k][1]) {
            temp = i - k;
            break;
          }
        }
        if (temp == 2) {
          // location where we add nop
          nop[nop_count][0] = i;
          // number of nop needs to be added
          nop[nop_count][1] = 1;
          instruc_count++, cycle_count++, nop_count++;
        }
        if (temp == 1) {
          // location where we add nop
          nop[nop_count][0] = i;
          // number of nop needs to be added
          nop[nop_count][1] = 2;
          instruc_count += 2;
          cycle_count += 2;
          nop_count += 2;
        }
      }
      j++;
      if (iftrue == 1) {
        flag = 1;
      }
    }
    instruc[i][j] = '\0';
    i++, cycle_count++;
  }
  int count = 1;
  nop_count = 1;
  // need to be careful here
  instruc[i][0] = '\0';
  i = 0;
  while (i < instruc_count) {
    if (i == nop[nop_add][0]) {
      move_instruction(stages, i, nop[nop_add][1], instruc);
      set_stage(stages, i, nop, instruc, nop_add);
      nop_add++;
    }
    i++;
  }
  // output each steps
  printf("START OF SIMULATION\n\n");
  while (count <= cycle_count) {
    print();
    int k = 0;
    for (i = 0; i < 5; i++, k++) {
      // skip nop if we don't need to print it
      if (instruc[i][0] == 'n') {
        if (count < (i + 3)) {
          continue;
        }
      }
      if (k < instruc_count) {
        // if there is 2 nop in a row
        if (instruc[i][0] == 'n' && (j + nop_count) < count) {
          if (check(nop, i) == 2) {
            printf("%s", instruc[i]);
            for (j = 0; j < 9; j++) {
              if (j < count) {
                printf("\t%s", stages[i][j]);
              } else {
                printf("\t.");
              }
            }
            printf("\n");
            i++;
          }
        }
        // normal case
        printf("%s", instruc[i]);
        for (j = 0; j < 9; j++) {
          if (j < count) {
            printf("\t%s", stages[i][j]);
          } else {
            printf("\t.");
          }
        }
        printf("\n");
      }
    }
    printf("\n");
    i++;
    count++;
  }
  // printf("printing reg:\n");
  // for (i = 0; i < 5; i++) {
  //   printf("%s\n", reg[i]);
  // }
  // printf("printing real stage:\n");
  // for (i = 0; i < 5; i++) {
  //   for (j = 0; j < 9; j++) {
  //     printf("%s\t", stages[i][j]);
  //   }
  //   printf("\n");
  // }
  printf("END OF SIMULATION\n");
  return EXIT_SUCCESS;
}
