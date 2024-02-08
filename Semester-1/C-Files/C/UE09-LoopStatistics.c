#include <stdio.h>

int main() {
    double number, min = 0, max = 0, average = 0;
    int cnt = 0;
    
    printf(": ");
    scanf(" %lf", &number);
    if(number > 0){
        min = number;
        max = number;
        cnt += 1;
        average += number;
    }
    
    while (number > 0)
    {
        printf(": ");
        scanf(" %lf", &number);
        if(number <= 0)
            break;
        cnt += 1;
        average += number;

        if(number < min && number > 0)
            min = number;

        else if (number > max)
            max = number;
        

    }
    if (cnt == 0)
        {
            printf("no number entered");
            return 0;
        }

    printf("cnt: %d", cnt);
    printf("\nmin: %.2lf", min);
    printf("\nmax: %.2lf", max);
    printf("\navg: %.2lf", average / cnt);

  return 0;
}