#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void findSubString(char *str, char *subStr) {
  bool isFound = false;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == subStr[0]) {
      int j = 0;
      while (j < strlen(subStr)) {
        if (str[i + j] != subStr[j]) {
          break;
        }
        j++;
      }
      if (j == strlen(subStr)) {
        isFound = true;
        break;
      }
    }
  }
  if (isFound) {
    printf("Substring found\n");
  } else {
    printf("Substring not found\n");
  }
}

int main(int argc, char *argv[]) {
  findSubString(argv[1], argv[2]);
  return 0;
}
