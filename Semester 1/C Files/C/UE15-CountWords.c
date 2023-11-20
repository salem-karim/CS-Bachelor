#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** scanWords() {
    char** words = (char**)calloc(1, sizeof(char*));
    char** tmp;
    int i = 0;
    while (1) {
        char buf[81];
        scanf("%80s", buf);
        if (buf[0] == '-') break;
        if (NULL == (tmp = (char**)realloc(words, sizeof(char*) * (i + 2)))) {
            printf("out of memory");
            break;
        }
        words = tmp;
        words[i] = (char*)calloc(strlen(buf) + 1, sizeof(char));
        strcpy(words[i], buf);
        i++;
    }
    words[i] = (char*)calloc(1, sizeof(char));
    return words;
}

int countWords(char* text, char* word) {
    int counter = 0;
    int textlength = strlen(text);
    int wordlength = strlen(word);
    for (int i = 0; i <= textlength - wordlength; ++i) {
        if(text[i] == word[0]){
            int matches = 1;
            for (int j = 0; j < wordlength; ++j) {
                if (text[i + j] != word[j]) {
                    matches = 0;
                    break;

                }
            }
            if(matches){
                counter++;
                i += wordlength - 1;
            }
        }
    }
    return counter;
}

void freeAll(char* text, char** strngs) {
    free(text);
    int i = 0;
    while(strlen(strngs[i]) != 0){
        free(strngs[i]);
        i++;
    }
    free(strngs[i]);
    free(strngs);
}

int main(){

    printf("text: ");
    char *txt = (char*) calloc(1001, sizeof(char));
    fgets(txt, 1001, stdin);
    printf("words: ");
    char** words = scanWords();
    for (int i = 0; strlen(words[i]) != 0 ; ++i) {
        if (strcmp(words[i], "") == 0)
            break;
        printf("\n%s: %d", words[i], countWords(txt, words[i]));
    }
    freeAll(txt, words);
    return 0;
}