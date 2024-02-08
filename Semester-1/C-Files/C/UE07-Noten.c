#include <stdio.h>
#include <string.h>

int main() {
    char grades [4];
    printf("Noten: ");
    scanf(" %s", &grades[0]);
    if (strlen(grades) > 3 || strlen(grades) < 3)
        printf("Erwarte genau 3 Noten!");
    else if (grades[0] == '1' && grades[1] == '1' && grades[2] == '1')
        printf("Ausgezeichneter Erfolg!\n");
    else if ((grades[0] == '1' || grades[1] == '1' || grades[2] == '2') && (grades[0] == '1' || grades[1] == '2' || grades[2] == '1') && (grades[0] == '2' || grades[1] == '1' || grades[2] == '1'))
        printf("Guter Erfolg!\n");
    else if (grades[0] == '5' || grades[1] == '5' || grades[2] == '5')
        printf("Nicht bestanden!\n");
    else if (grades[0] > '5' || grades[0] < '1')
        printf("Erste Note muss zwischen 1 und 5 liegen!\n");
    else if (grades[1] > '5' || grades[1] < '1')
        printf("Zweite Note muss zwischen 1 und 5 liegen!\n");
    else if (grades[2] > '5' || grades[2] < '1')
        printf("Dritte Note muss zwischen 1 und 5 liegen!\n");
    else
        printf("Bestanden.\n");
    return 0;
}