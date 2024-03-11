#include <stdio.h>

int fibonacci(int n) {
    int fibo1 = 0;
    int fibo2 = 1;

    if (n == 0) {
        return fibo1;
    } else if (n == 1) {
        return fibo2;
    } else {
        int temp = 0;

        for(int i = 2; i <= n; i++) {
            temp = fibo2 + fibo1;
            fibo1 = fibo2;
            fibo2 = temp;
        }

        return fibo2;
    }
}

int main() {
    int n = 0;

    printf("Insira um numero n para obter o n-termo da serie de fibonacci: ");
    scanf("%d", &n);
    int res = fibonacci(n);
    printf("%d", res);
}