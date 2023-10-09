#include <stdio.h>

int main() {
    int a,b,c,d,e;
    scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
   int array[] = {a,b,c,d,e};
    
    int totalSum = array[0] + array[1] + array[2] + array[3] + array[4];
    
    int minSum = 999999;
    int maxSum = 0;
    
    for (int i = 0; i < 5; i++) {
        int sum = totalSum - array[i];
        if (minSum > sum) { minSum = sum; }
        if (maxSum < sum) { maxSum = sum; }
    }
    printf(": minimum sum: %d\n",minSum);
    printf("maximum sum: %d\n",maxSum);

    
   return 0;
}
