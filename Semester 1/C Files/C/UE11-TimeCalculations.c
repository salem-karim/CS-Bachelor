#include <stdio.h>
#include <stdlib.h>

/* put your code here */
int encode(int h, int m){
   int time = h * 100 + m;
   return time;
}

int read(){               // only difference is that it prints hours/minutes instead of h/m like in encode
   int h, m;
    printf("hours: ");
    scanf("%d", &h);
    printf("minutes: ");
    scanf("%d", &m);
   return encode(h, m);
}

int hours(int t){
   int h = t / 100;
   return h;
}

int minutes(int t){
   int m = t % 100;
   return m;
}

void print(int t){            // gets the encoded time from read/encode and prints it in the format hh:mm
   int h = t / 100;
   int m = t % 100;
   printf("%02d:%02d", h, m);
}

int add(int t1, int t2){
   int h1 = t1 / 100;
   int m1 = t1 % 100;
   int h2 = t2 / 100;
   int m2 = t2 % 100;
   int hours = h1 + h2;
   int minutes = m1 + m2;
   if(minutes >= 60){
      minutes -= 60;
      ++hours;
      if(hours >= 24)
        hours -= 24;
    }
    else if (hours == 24)
        hours = 0;
        
   return encode(hours, minutes);
}

int total_minutes(int t){
   int h = t / 100;
   int m = t % 100;
   return h * 60 + m;
}

/* CodeRunner has its own copy of use_this_main.c, 
   no need to integrate its contents into the answer */
#include "use_this_main.c"