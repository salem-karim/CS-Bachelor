#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num;
    int weekday;
    printf("number of days in month: ");
    scanf(" %2d", &num);
    printf("starting day of week (1=Monday, 7=Sunday): "),
    scanf(" %1d", &weekday);

    switch (weekday)
    {
    case 2:
        printf("   ");
        break;
    case 3:
        printf("      ");
        break;
    case 4:
        printf("         ");
        break;
    case 5:
        printf("            ");
        break;
    case 6:
        printf("               ");
        break;
    case 7:
        printf("\n");
        break;
    default:
        break;
    }

    for(int outp = 1; outp <= num; ++outp)
    {
        printf(" %d", outp);
        if(outp % 7 == 0)
            printf("\n");
    }


    return 0;
}
