#include <stdio.h>

int main() {
    int s;
    scanf("%d",&s);
    int a = 6 * s * s;
    int v = s * s * s;
    
    printf(": Surface area: %d\nVolume: %d", a, v);
    
    return 0;
}
