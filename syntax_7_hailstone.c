#include <stdio.h>

void hailstone(int n){
    printf("%-4d", n);
    while(n != 1){
        if(n % 2 == 0){
            n = n/2;
        } else {
            n = 3*n + 1;
        }
        printf("%-4d", n);
    }
    printf("\n");
}

int main(){    
    for(int n = 1; n < 10; n++){
        hailstone(n);
    }
}
