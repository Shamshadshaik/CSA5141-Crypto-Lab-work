#include <stdio.h>
#include <string.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
char encryptChar(char p, int a, int b) {
    if (p >= 'A' && p <= 'Z') {
        return (char) ((((a * (p - 'A')) + b) % 26) + 'A');
    }
    if (p >= 'a' && p <= 'z') {
        return (char) ((((a * (p - 'a')) + b) % 26) + 'a');
    }
    return p; 
}
char decryptChar(char c, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Error: a and 26 are not coprime, decryption impossible.\n");
        return c;
    }
    if (c >= 'A' && c <= 'Z') {
        return (char) ((((a_inv * ((c - 'A' - b + 26)) % 26)) % 26) + 'A');
    }
    if (c >= 'a' && c <= 'z') {
        return (char) ((((a_inv * ((c - 'a' - b + 26)) % 26)) % 26) + 'a');
    }
    return c; 
}
int isCoprime(int a) {
    return gcd(a, 26) == 1;
}

int main() {
    int a, b;
    char plaintext[100];
    char ciphertext[100];
    char decryptedtext[100];

    printf("Enter value for a (must be coprime with 26): ");
    scanf("%d", &a);

    while (!isCoprime(a)) {
        printf("Value of a is not coprime with 26. Please enter a valid value: ");
        scanf("%d", &a);
    }

    printf("Enter value for b: ");
    scanf("%d", &b);

    printf("Enter plaintext: ");
    scanf("%s", plaintext);

    // Encrypt the plaintext
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = encryptChar(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the ciphertext

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedtext[i] = decryptChar(ciphertext[i], a, b);
    }
    decryptedtext[strlen(ciphertext)] = '\0'; 

    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
