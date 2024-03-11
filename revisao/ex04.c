#include <stdio.h>

int main() {
    FILE *p;

    p = fopen("list2.txt", "r");
    
    char gender;
    int grade = 0;
    int countMen = 0;
    int countWomen = 0;
    int totalMen = 0;
    int totalWomen = 0;

    while (fscanf(p, "%c %d", &gender, &grade) > 0) {
        if (gender == 'M') {
            totalMen += grade;
            countMen++;
        } else {
            totalWomen += grade;
            countWomen++;
        }
    }

    float averageMen = (float) totalMen / countMen;
    float averageWomen = (float) totalWomen / countWomen;

    if (averageMen > averageWomen) {
        printf("M %f", averageMen);
    } else {
        printf("F %f", averageWomen);
    }

    return 0;
}