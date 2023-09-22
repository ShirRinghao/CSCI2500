
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROBLEM1
//#define PROBLEM2
//#define PROBLEM3
//#define PROBLEM4
//#define PROBLEM5

void compute(int endpoint) {
  int nums2[6][6];
  int nums[6][6];

  void *rsp, *rbp;
  __asm__ __volatile__ ("movq %%rsp,%0"
  : "=r" (rsp)
  : /* No input */);
  __asm__ __volatile__ ("movq %%rbp,%0"
  : "=r" (rbp)
  : /* No input */);  

  printf("rsp = %p, rbp = %p, stack size = %lu\n", rsp, rbp, rbp - rsp);

  void * frame_addr = __builtin_frame_address(0);
  printf("Stack frame starts at address %p\n\n", frame_addr);
  printf("1. nums2 starts at address %p, frame offset %ld, "
    "ends at address %p, frame offset %ld\n", &nums2, (void *)&nums2 - frame_addr,
    &nums2 + 1, (void *)(&nums2 + 1) - frame_addr);
  printf("2. nums starts at address %p, frame offset %ld, "
    "ends at address %p, frame offset %ld\n", &nums, (void *)&nums - frame_addr,
    &nums + 1, (void *)(&nums + 1) - frame_addr);
  printf("3. return address (%%rbp + 8) is %02x%02x%02x%02x%02x%02x%02x%02x (appears reverse on a little-endian system)\n\n",
    ((unsigned char *)(rbp + 8))[0], ((unsigned char *)(rbp + 8))[1], ((unsigned char *)(rbp + 8))[2], ((unsigned char *)(rbp + 8))[3], 
    ((unsigned char *)(rbp + 8))[4], ((unsigned char *)(rbp + 8))[5], ((unsigned char *)(rbp + 8))[6], ((unsigned char *)(rbp + 8))[7]);


  printf("1. &nums is %p, sizeof %lu, &nums + 1 is %p, sizeof %lu\n",
    &nums, sizeof(&nums), &nums + 1, sizeof(&nums + 1));
  printf("2. nums is %p, sizeof %lu, nums + 1 is %p, sizeof %lu\n",
    nums, sizeof(nums), nums + 1, sizeof(nums + 1));
  printf("3. nums[0] is %p, sizeof %lu, nums[0] + 1 is %p, sizeof %lu\n",
    nums[0], sizeof(nums[0]), nums[0] + 1, sizeof(nums[0] + 1));
  printf("4. &nums[0] is %p, sizeof %lu, &nums[0] + 1 is %p, sizeof %lu\n",
    &nums[0], sizeof(&nums[0]), &nums[0] + 1, sizeof(&nums[0] + 1));
  /* It is an int, not a pointer */
  /* printf("5. nums[0][0] is %p, sizeof %lu\n", nums[0][0], sizeof(nums[0][0])); */
  printf("6. &nums[0][0] is %p, sizeof %lu, &nums[0][0] + 1 is %p, sizeof %lu\n\n",
    &nums[0][0], sizeof(&nums[0][0]) , &nums[0][0] + 1, sizeof(&nums[0][0] + 1));
}

void get_bio( char *f_name, int *grad_year, float *GPA ) {
  printf("Enter your first name: ");
  scanf("%s", f_name);
  printf("Enter your graduation year: ");
  scanf("%d", grad_year);
  printf("Enter your current GPA: ");
  scanf("%f", GPA);
}

char * vowels( char * s )
{
  int i, j, k, count;
  char * result;
  char * v = "aeiouAEIOU";
  count = 0;

  for ( i = 0 ; i < strlen( s ) ; i++ )
    for ( j = 0 ; j < strlen( v ) ; j++ )
      if ( s[i] == v[j] )
        count++;

  result = malloc( count + 1);
  for ( i = 0, k = 0 ; i < strlen( s ) ; i++ )
    for ( j = 0 ; j < strlen( v ) ; j++ )
      if ( s[i] == v[j] )
        result[k++] = s[i];
  result[k] = '\0';
  return result;
}

int main(int argc, char *argv[])
{
#ifdef PROBLEM1
  /* Answer: The runtime stack */

  compute(5);
  ret: ;
  printf("Next instruction after a call to compute() is at address %p\n", &&ret);
#endif

#ifdef PROBLEM2
  /* Answers:
     Part a:
       void get_bio( char *f_name, int *grad_year, float *GPA )
     Part b:
       printf("Enter your first name: ");
       scanf("%s", f_name);
       printf("Enter your graduation year: ");
       scanf("%d", grad_year);
       printf("Enter your current GPA: ");
       scanf("%f", GPA);
     Part c:
       name, &year, &gpa
  */

  char *name = (char *)malloc(100 * sizeof(char));
  int year;
  float gpa;
  get_bio(name, &year, &gpa);
  printf("Name: %s\n", name);
  printf("Graduation year: %d\n", year);
  printf("GPA: %f\n", gpa);

#endif

#ifdef PROBLEM3
  /* Answer:
    double ** arr;
    arr = (double **) malloc(n * sizeof(double *));
    int i;
    for (i = 0; i < n; ++i) {
      arr[i] = (double *) malloc(m * sizeof(double));
    }
  */

  unsigned int n, m;
  n = 6; m = 4;

  double ** arr;
  arr = (double **) malloc(n * sizeof(double *));
  int i;
  for (i = 0; i < n; ++i) {
    arr[i] = (double *) malloc(m * sizeof(double));
  }

  int j;

  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; j++) {
      arr[i][j] = i + j;
    }
  }

  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; j++) {
      printf("%f ", arr[i][j]);
    }
    printf("\n");
  }

  for (i = 0; i < n; ++i) {
    free(arr[i]);
  }
  free(arr);

#endif

#ifdef PROBLEM4
  /* Answers
     Part a:
       echo $?
     Part b:
       0: successful execution of the program
       1: unsuccessful execution of the program
  */

#define SHELLSCRIPT "\
#/bin/bash \n\
touch tmptmp \n\
echo $? \n\
cat tmptmptmp \n\
echo $? \n\
"
  printf("Executing the following script:\n%s\n", SHELLSCRIPT);
  printf("Output:\n");
  system(SHELLSCRIPT);

#endif

#ifdef PROBLEM5
  /* Answer:
     BUG #1: variable count is uninitialized
     FIX #1: should be count = 0

     BUG #2: if ( s[i] == v[i] ) is incorrect
     FIX #2: should be: if ( s[i] == v[j] )
                                       ^

     BUG #3: malloc() call does not allocate enough memory
     FIX #3: should be malloc( count + 1 );
            or malloc( ( count + 1 ) * sizeof( char ) );

     BUG #4: result[k] = "\0"; is incorrect;
     FIX #4: should be result[k] = '\0';     
  */

  char * test_str = "SnApChAt RuLeS!!!";
  char * result = vowels( test_str );
  printf("%s => %s\n", test_str, result);
  free(result);
  return EXIT_SUCCESS;

#endif

  return EXIT_SUCCESS;
}
