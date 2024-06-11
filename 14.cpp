#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to convert a character to its corresponding number (A=0, ..., Z=25)
int char_to_num(char c) {
    return toupper(c) - 'A';
}

// Function to convert a number to its corresponding character (0=A, ..., 25=Z)
char num_to_char(int n) {
    return n + 'A';
}

// Function to encrypt the plaintext using the key stream
void encrypt(char* plaintext, int* key, int len, char* ciphertext) {
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int p = char_to_num(plaintext[i]);
            int c = (p + key[i]) % 26;
            ciphertext[i] = num_to_char(c);
        } else {
            ciphertext[i] = plaintext[i]; // Keep spaces and other characters as they are
        }
    }
    ciphertext[len] = '\0';
}

// Function to decrypt the ciphertext to find the corresponding key
void find_key(char* ciphertext, char* desired_plaintext, int* key, int len) {
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i]) && isalpha(desired_plaintext[i])) {
            int c = char_to_num(ciphertext[i]);
            int p = char_to_num(desired_plaintext[i]);
            key[i] = (c - p + 26) % 26;
        } else {
            key[i] = 0; // For non-alphabetic characters, keep key as 0
        }
    }
}

int main() {
    // Input plaintext and key stream
    char plaintext[] = "send more money";
    int key[] = {9, 0, 17, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int len = strlen(plaintext);
    
    // Convert spaces and non-alphabetic characters in plaintext to uppercase
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            plaintext[i] = toupper(plaintext[i]);
        }
    }

    // Encrypt the plaintext
    char ciphertext[len + 1];
    encrypt(plaintext, key, len, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Desired plaintext for decryption
    char desired_plaintext[] = "cash not needed";
    int key_for_decryption[len];

    // Find the key that decrypts the ciphertext to the desired plaintext
    find_key(ciphertext, desired_plaintext, key_for_decryption, len);

    // Print the found key
    printf("Key for decryption: ");
    for (int i = 0; i < len; i++) {
        if (isalpha(desired_plaintext[i])) {
            printf("%d ", key_for_decryption[i]);
        }
    }
    printf("\n");

    return 0;
}
