#include <stdio.h>

// Invalid Input Error
void invInErr(double min, double max) {
  printf("\nungueltiger Bereich: min %.2lf, max %.2lf", min, max);
}

int main() {
  double zt = 0;       // Zwischentest points
  double at = 0;       // Abschlusstest points
  double ue = 0;       // Uebungsbeispiel points
  double maxTotal = 0; // Maximum total points
  int firstAt = 1;     // Boolean for first valid Abschlusstest points input
  char sel = ' ';      // Menu selection char
  double in = 0;       // Points input

  do {
    // Print current points, wait for menu selection
    printf("\nZT Punkte: %.2lf"
           "\nAT Punkte: %.2lf"
           "\nUE Punkte: %.2lf"
           "\nErreichbare Gesamtpunkte: %.2lf\nTyp: ",
           zt, at, ue, maxTotal);
    scanf(" %c", &sel);

    // '=' ends program
    if (sel == '=')
      break;

    // Points input
    printf("\nPunkte: ");
    scanf("%lf", &in);

    // Zwischentest points
    if (sel == 'z') {
      if (in >= 0 && in <= 10) {
        zt += in;
        maxTotal += 10;
      } else
        invInErr(0, 10);
      // Abschlusstest points
    } else if (sel == 'a') {
      if (in >= 0 && in <= 70) {
        at = in;
        if (firstAt) {
          maxTotal += 70;
          // Set to false after first valid Abschlusstest points input
          firstAt = 0;
        }
      } else
        invInErr(0, 70);
      // Uebungsbeispiel points
    } else if (sel == 'u') {
      if (in >= 0 && in <= 0.5) {
        // Cap Uebungspunkte at 10
        ue = (ue + in <= 10) ? ue + in : 10;
      } else
        invInErr(0, 0.5);
    }
  } while (1);

  int grade = 5;
  double total = zt + at;
  // Set percentage to 0 if maximum total is 0, otherwise calculate it
  double perc = (maxTotal == 0) ? 0 : total / maxTotal * 100;

  if (perc == 0) {
    grade = 0;
  } else if (perc >= 55) {
    total += ue;
    // Recalculate percentage with Uebungspunkte
    perc = total / maxTotal * 100;

    if (perc < 67) {
      grade = 4;
    } else if (perc < 78) {
      grade = 3;
    } else if (perc < 89) {
      grade = 2;
    } else {
      grade = 1;
    }
  }

  printf("\nGesamtpunkte absolut: %.2lf"
         "\nGesamtpunkte %%: %.2lf %%"
         "\nNote: %d",
         total, perc, grade);

  return 0;
}
