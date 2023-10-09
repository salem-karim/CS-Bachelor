#include <stdio.h>

int main() {
    int i = 0;
    int* p = &i;
    int* q = &i;
    printf("%p\n %p\n", p, q);
  return 0;
}