#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_LENGTH 26

void generateCipherSequence(char *keyword, char *cipher) {
    bool used[ALPHABET_LENGTH] = {false};
    int cipherIndex = 0;

    
    int len = strlen(keyword);
    for (int i = 0; i < len; i++) {
        keyword[i] = (keyword[i]);
    }

    for (int i = 0; i < len; i++) {
        if (!used[keyword[i] - 'A']) {
            cipher[cipherIndex++] = keyword[i];
            used[keyword[i] - 'A'] = true;
        }
    }

  
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[cipherIndex++] = ch;
        }
    }

    cipher[cipherIndex] = '\0';
}

void encrypt(char *plaintext, char *cipher, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = cipher[plaintext[i] - 'a'];
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = cipher[plaintext[i] - 'A'];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char cipher[ALPHABET_LENGTH + 1];
    char plaintext[256];
    char ciphertext[256];

    generateCipherSequence(keyword, cipher);

    printf("Plain alphabet:  abcdefghijklmnopqrstuvwxyz\n");
    printf("Cipher alphabet: %s\n", cipher);

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    encrypt(plaintext, cipher, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

