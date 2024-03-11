#include <stdio.h>

int main() {
    FILE *p;

    p = fopen("list.txt", "r");
    int num = 0;
    int even = 1;
    int odd = 0;

    while(fscanf(p, "%d", &num) > 0) {
        if (num % 2 == 0) {
            even *= num;
        } else {
            odd += num;
        }
    }

    printf("O produto dos numeros pares e: %d\n", even);
    printf("A soma dos numeros impares e: %d", odd);

    return 0;
}