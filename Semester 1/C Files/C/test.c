#include <stdio.h>

int main() {
    int i = 0;
    int* p = &i;
    int* q = &i;
    printf("%d\n %p\n", i, q);
  return 0;
}