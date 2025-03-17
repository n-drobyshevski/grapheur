#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CMD_BUFFER_SIZE 256
#else
#define CMD_BUFFER_SIZE 1024
#endif

typedef struct {
  const char *input;
  int expected_valid; // 1 for valid, 0 for invalid expression.
} TestCase;

int main() {
  TestCase tests[] = {{"1+2", 1},
                      {"(3+5)*2", 1},
                      {"42", 1},
                      {"1+2*3", 1},
                      {"(1+(2*(3+4)))/5", 1},
                      {"1+", 0},
                      {"1+2)", 0},
                      {"(1+2", 0}};
  int num_tests = sizeof(tests) / sizeof(tests[0]);
  int passed = 0;

  for (int i = 0; i < num_tests; i++) {
    char command[CMD_BUFFER_SIZE];
    snprintf(command, CMD_BUFFER_SIZE, "syntax.exe \"%s\"", tests[i].input);
    printf("Running test %d: %s\n", i + 1, tests[i].input);

    int ret = system(command);
    int valid = (ret == 0);

    if (valid == tests[i].expected_valid) {
      printf("Test %d passed.\n", i + 1);
      passed++;
    } else {
      printf("Test %d FAILED.\n", i + 1);
    }
    printf("\n");
  }

  printf("%d/%d tests passed.\n", passed, num_tests);
  return (passed == num_tests) ? EXIT_SUCCESS : EXIT_FAILURE;
}