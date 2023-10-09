#include <stdio.h>
#include <stdlib.h>

int main()
{
    char type;
    double guthaben = 100;
    double betrag;
    double kost_counter = 0;
    double kosts = 0;
    double einnahme_counter = 0;
    double steuern = 0;
    double einnahmen = 0;
    while(1)
    {
        printf("\nGuthaben: %.2lf Euro", guthaben);
        printf("\nTyp:");
        scanf(" %c", &type);

        if(type == 's')
        {
            printf("\nBetrag in Euro:");
            scanf(" %lf", &betrag);
            if (betrag < 0) {
                printf("\nDer Betrag kann nicht negativ sein.");
                continue;
            }
            else
            guthaben += + betrag;
            einnahmen += betrag;
            ++einnahme_counter;
        }
        else if(type == 'k')
        {
            printf("\nBetrag in Euro:");
            scanf(" %lf", &betrag);
            if(betrag < 0){
                printf("\nDer Betrag kann nicht negativ sein.");
                continue;
            }
            else if(betrag > guthaben)
            {
                printf("\nDiese Kosten koennen nicht bezahlt werden.");
                continue;
            }
            guthaben = guthaben - betrag;
            ++kost_counter;
            kosts += betrag;
        }
        else if(type == 'e')
        {
            printf("\nBetrag in Euro:");
            scanf(" %lf", &betrag);
            if (betrag < 0) {
                printf("\nDer Betrag kann nicht negativ sein.");
                continue;
            }
            else
            ++einnahme_counter;
        }
            /*case 'e':von 267€ 30 *0.1 + 150 * 0.2 + 67 * 0.4 für einahmen von zb. 173€ sind 20 * 1, betrag = betrag * 1;
                double steurn = betrag ; printf("\nGezahlte Steuern: %.2f Euro", ); printf("\nGuthaben: %.2f Euro", guthaben + betrag); break;*/
        else if (type == '=')
            break;
        else
            continue;
    }
    printf("\nRestguthaben: %.2lf Euro", guthaben);
    if(einnahme_counter == 0)
        printf("\n0 Einnahmen mit durchschnittlichem Wert 0.00 Euro");
    else
        printf("\n%.0lf Einnahmen mit durchschnittlichem Wert %.2lf Euro", einnahme_counter, einnahmen / einnahme_counter);
    if(kost_counter == 0)
        printf("\n0 Ausgaben mit durchschnittlichem Wert 0.00 Euro");
    else
        printf("\n%.0lf Ausgaben mit durchschnittlichem Wert %.2lf Euro", kost_counter, kosts / kost_counter);
    printf("\nGezahlte Steuern: %.2lf Euro", steuern);
    return 0;
}
