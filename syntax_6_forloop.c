#include <stdio.h>

int fib(int n){
    int a = 0;
    int b = 1;
    for(int i = 0; i < n; i++){
        int sum = a + b;
        b = a;
        a = sum;
    }
    return a;
}

int main(){    
    for(int n = 0; n < 10; n++){
        printf("fib(%d) = %d\n", n, fib(n));
    }
}
