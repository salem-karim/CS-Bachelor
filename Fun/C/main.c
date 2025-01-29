#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Hello, World!\n");
  for (int i = 0; i < argc; i++) {
    printf("This is the %d. Argument: %32s\n", i + 1, argv[i]);
  }
  return 0;
}
