//
//  main.c
//  Zwischentest 1
//
//  Created by Karim Salem on 08.10.22.
//

#include <stdio.h>
int main(){
    double p,pz=0,pa=0,pu=0,epg=0,pg;
    char type;
    while (1) {
        printf("\nZT Punkte: %.2lf\nAT Punkte: %.2lf\nUE Punkte: %.2lf\nErreichbare Gesamtpunkte: %.2lf\n",pz,pa,pu,epg);
        printf("Typ: ");
        scanf(" %c",&type);
        if(type=='=')
            break;
        printf("\nPunkte: ");
        scanf(" %lf",&p);
        switch (type) {
            case 'z':
                if(p<0.00||p>10.00){
                    printf("\nungueltiger Bereich: min 0.00, max 10.00\n");
                }
                pz=pz+p;
                        epg=epg+10;
                break;
            case 'a':
                if(p<0.00||p>70.00){
                    printf("\nungueltiger Bereich: min 0.00, max 70.00\n");
                }
                pa=pa+p;
                        epg=epg+70;
                break;
            case 'u':
                if(p<0.00||p>0.50){
                    printf("\nungueltiger Bereich: min 0.00, max 0.50\n");
                }
                pu=pu+p;
                break;
            case '=':
                break;
            default:
                break;
        }
    }
    int grade = 0;
    pg=pz+pa;
    if(pz+pa>=0.55*epg)
        pg=pg+pu;
    if (pg<=epg&&pg>=0.89*epg)
        grade=1;
    else if (pg<0.89*epg&&pg>=0.78*epg)
        grade=2;
    else if (pg<0.78*epg&&pg>=0.67*epg)
        grade=3;
    else if (pg<0.67*epg&&pg>=0.55*epg)
        grade=4;
    else if (pg<0.55*epg)
        grade=5;
    printf("\nGesamtpunkte absolut: %.2lf\nGesamtpunkte %%: %.2lf %%\nNote: %d\n",pg,(pg/epg)*100,grade);
    return 0;
}

