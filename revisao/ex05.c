#include <stdio.h>

int fibonacci(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

int main() {
    int n = 0;

    printf("Insira um numero n para obter o n-termo da serie de fibonacci: ");
    scanf("%d", &n);
    int res = fibonacci(n);
    printf("%d", res);
}