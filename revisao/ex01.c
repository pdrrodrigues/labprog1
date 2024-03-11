#include <stdio.h>

int main() {
    int n = 0;

    printf("Insira um numero n: ");
    scanf("%d", &n);

    for(int i = 0; i <= n; i += 2) {
        printf("%d ", i);
    }
}