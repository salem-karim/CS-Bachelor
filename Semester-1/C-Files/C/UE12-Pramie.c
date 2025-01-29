#define anz 10
#include <stdio.h>

double praemien(double betraege[], int anzahl, double grenze, double praemie){
    double gesamte_praemie = 0;
    for(int i = 0; i < anzahl; ++i){
        if(betraege[i] >= grenze){
            betraege[i] += praemie;
            gesamte_praemie += praemie;
        }    
    }
    return gesamte_praemie;
}

int eingabe(double betraege[], int max){
    int i = 0;
    while(i < max){
        printf("Zahl %d: ", i+1);
        scanf(" %lf", &betraege[i]);
        if(betraege[i] < 0)
            break;
        ++i;
    }
    return i;
}

double sum(double betraege[], int anzahl){
    int i = 0;
    double summe = 0;
    while(i < anzahl){
        summe += betraege[i];
        ++i;
    }
    return summe;
}

int main(){
    double arr[anz] = {0};
    double grenze, praemie, gesamt;
    int n;

    n = eingabe(arr, anz);
    printf("Untergrenze: ");
    scanf("%lf", &grenze);
    printf("Praemie: ");
    scanf("%lf", &praemie);

    printf("Summe vor Praemien: %.2f\n", sum(arr, n));
    gesamt = praemien(arr, n, grenze, praemie);
    printf("Praemien gesamt: %.2f\n", gesamt);
    printf("Summe nach Praemien: %.2f\n", sum(arr, n));

    return 0;
}
