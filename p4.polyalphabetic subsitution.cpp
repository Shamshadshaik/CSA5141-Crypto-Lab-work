#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char *plaintext, char *key, char *ciphertext) {
    int text_len = strlen(plaintext);
    int key_len = strlen(key);
    int i, j;
    for(i = 0, j = 0; i < text_len; i++) {
        char current_char = plaintext[i];
        if (isalpha(current_char)) {

            char base = isupper(current_char) ? 'A' : 'a';
            
            int key_shift = toupper(key[j % key_len]) - 'A';
           
            ciphertext[i] = (current_char - base + key_shift) % 26 + base;
            j++; 
        } else {
            ciphertext[i] = current_char;
        }
    }
    ciphertext[text_len] = '\0'; 
}

int main() {
    char plaintext[256];
    char key[256];
    char ciphertext[256];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
