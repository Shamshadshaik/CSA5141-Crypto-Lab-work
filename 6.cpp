#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}


void decryptAffine(char* ciphertext, int a, int b) {
    int a_inv = modInverse(a, 26); 
    if (a_inv == -1) {
        printf("No modular inverse found for a=%d\n", a);
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int y = ciphertext[i] - 'A';
            int x = (a_inv * (y - b + 26)) % 26;
            printf("%c", x + 'A');
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[] = "YOUR_CIPHERTEXT_HERE";

    
    int x1 = 4; 
    int x2 = 19; 
    int y1 = 1;
    int y2 = 20; 

    
    int a = (y1 - y2) * modInverse((x1 - x2 + 26) % 26, 26) % 26;
    if (a < 0) a += 26;
    int b = (y1 - a * x1) % 26;
    if (b < 0) b += 26;

    printf("Derived keys: a = %d, b = %d\n", a, b);

    printf("Decrypted message: ");
    decryptAffine(ciphertext, a, b);

    return 0;
}
