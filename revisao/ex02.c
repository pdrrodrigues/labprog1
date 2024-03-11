#include <stdio.h>

void evenNumbers(int i, int n) {
    if (i > n) {
        ;
    } else {
        printf("%d ", i);
        i += 2;
        evenNumbers(i, n);
    }
}

int main() {
    int n = 0;

    printf("Insira um numero n: ");
    scanf("%d", &n);

    int i = 0;
    evenNumbers(i, n);
}