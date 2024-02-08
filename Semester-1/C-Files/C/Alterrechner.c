//
//  main.c
//  Altersrechner
//
//  Created by Karim Salem on 29.10.22.
//

#include <stdio.h>
int main() {
int gj, za;
char input;

    do {
        printf("Wähle ein Jahr aus: ");
        scanf("%d", &za);
        printf("\nDein Geburtsjahr: ");
        scanf("%d", &gj);
        if (gj <= za) {
            printf("\nDein Alter im Jahre %d ist %d\n", za, za-gj);
        }
        else {
            printf("\nUngültige Eingabe");
        }
        printf("\nNoch einmal Versuchen(j/n): ");
        scanf("%s", &input);
        while(1) {
            if (input == 'j' || input == 'n') { break; }
            printf("\nUngültige Eingabe");
            printf("\nNoch einmal Versuchen(j/n): ");
            scanf("%s",&input);
        }
    } while(input=='j');
    return 0;
    }
