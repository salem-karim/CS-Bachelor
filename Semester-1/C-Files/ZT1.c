#include <stdio.h>

void zwischenstand(double ZT, double AT, double UE, double maxpunkte) {

  printf("\nZT Punkte: %.02f", ZT);
  printf("\nAT Punkte: %.02f", AT);
  printf("\nUE Punkte: %.02f", UE);
  printf("\nErreichbare Gesamtpunkte: %.02f", maxpunkte);
}

double prozent(double gesamt, double maxpunkte) {

  if (maxpunkte == 0) {
    return 0;
  }

  else {

    return gesamt / maxpunkte * 100;
  }
}

int *Sort(int *array) {
  for
    return array;
}

void endergebnis(double ZT, double AT, double UE, double maxpunkte) {

  printf("\nGesamtpunkte absolut: %.02lf", ZT + AT + UE);

  printf("\nGesamtpunkte %%: %.02lf %%", prozent(ZT + AT + UE, maxpunkte));
}

int main() {

  double ZT = 0;
  double AT = 0;
  double UE = 0;
  char typ = 0;
  double punkte = 0;
  double maxpunkte = 0;
  int ATcounter = 0; // um Doppelzaehlung bei maxpunkte von AT zu verhindern für
                     // den Fall, dass erste AT-Punkteeingabe 0 ist.

  zwischenstand(ZT, AT, UE, maxpunkte);
  while (typ != '=') {

    printf("\nTyp: ");
    scanf(" %c", &typ);

    if (typ == 'z' || typ == 'a' || typ == 'u') {
      printf("\nPunkte:");
      scanf("%lf", &punkte);
    }

    if (typ == 'z') {

      if (punkte < 0 || punkte > 10) {
        printf("\nungueltiger Bereich: min 0.00, max 10.00");
      }

      else {
        ZT += punkte;
        maxpunkte += 10;
      }
      zwischenstand(ZT, AT, UE, maxpunkte);
    }

    if (typ == 'a') {

      if ((punkte < 0 || punkte > 70)) {
        printf("\nungueltiger Bereich: min 0.00, max 70.00");
      }
      // für den Fall, dass die erste AT Eingabe 0 ist
      else if (ATcounter == 0) {
        AT = punkte;
        maxpunkte += 70;
        ATcounter++;
      }

      else {
        AT = punkte;
      }
      zwischenstand(ZT, AT, UE, maxpunkte);
    }

    if (typ == 'u') {

      if ((punkte < 0 || punkte > 0.5)) {
        printf("\nungueltiger Bereich: min 0.00, max 0.50");
      }

      else if (UE + punkte <= 10) {
        UE += punkte;
      }

      else if (UE + punkte > 10) {
        UE = 10;
      }
      zwischenstand(ZT, AT, UE, maxpunkte);
    }
  }

  // Wenn Gesamtpunkte 0 (ohne UE)
  if (prozent(ZT + AT, maxpunkte) == 0) {
    printf("\nGesamtpunkte absolut: %.02lf", ZT + AT);
    printf("\nGesamtpunkte %%: 0.00 %%");
    printf("\nNote: 0");
  }
  // Wenn Gesamtprozent (ohne UE) < 55
  else if (prozent(ZT + AT, maxpunkte) < 55) {
    endergebnis(ZT, AT, 0, maxpunkte);
    printf("\nNote: 5");
  }
  // Gesamtprozent (ohne UE) > 55 (UE fließt in Gesamtnoteberechnung mit ein)
  else if (prozent(ZT + AT + UE, maxpunkte) < 67) {
    endergebnis(ZT, AT, UE, maxpunkte);
    printf("\nNote: 4");
  }

  else if (prozent(ZT + AT + UE, maxpunkte) >= 67 &&
           (prozent(ZT + AT + UE, maxpunkte) < 78)) {
    endergebnis(ZT, AT, UE, maxpunkte);
    printf("\nNote: 3");
  }

  else if (prozent(ZT + AT + UE, maxpunkte) >= 78 &&
           (prozent(ZT + AT + UE, maxpunkte) < 89)) {
    endergebnis(ZT, AT, UE, maxpunkte);
    printf("\nNote: 2");
  }

  else if (prozent(ZT + AT + UE, maxpunkte) >= 89) {
    endergebnis(ZT, AT, UE, maxpunkte);
    printf("\nNote: 1");
  }

  return 0;
}
