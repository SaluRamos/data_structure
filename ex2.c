#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n){
    if(n < 2){
        return n;
    }
    else{
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main(void){
    int n = 0;
    printf("Digite um numero: ");
    scanf("%d", &n);
    printf("resultado = %d", fibonacci(n));
    return 1;
}