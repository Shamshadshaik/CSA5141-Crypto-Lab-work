#include <stdio.h>
#include <math.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    unsigned long long total_keys = factorial(25);
    unsigned long long row_permutations = factorial(5);
    unsigned long long unique_keys = total_keys / (row_permutations * row_permutations);

    printf("Total possible keys: 2^%.2lf\n", log2((double)total_keys));
    printf("Effectively unique keys: 2^%.2lf\n", log2((double)unique_keys));

    return 0;
}

