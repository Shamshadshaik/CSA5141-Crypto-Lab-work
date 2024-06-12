
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

void handleErrors() {
    fprintf(stderr, "An error occurred\n");
    exit(1);
}

int main() {
    // Key and IV
    unsigned char key[AES_BLOCK_SIZE]; // AES_BLOCK_SIZE is 16 bytes
    unsigned char iv[AES_BLOCK_SIZE];
    
    // Generate random key and IV
    if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) {
        handleErrors();
    }

    // AES key structure
    AES_KEY encryptKey, decryptKey;

    // Set encryption and decryption keys
    if (AES_set_encrypt_key(key, 128, &encryptKey) < 0 || AES_set_decrypt_key(key, 128, &decryptKey) < 0) {
        handleErrors();
    }

    // Input data
    unsigned char plaintext[BUFSIZE] = "This is a test message for CBC mode encryption with AES.";
    unsigned char ciphertext[BUFSIZE];
    unsigned char decryptedtext[BUFSIZE];

    // Padding
    int plaintext_len = strlen((char*)plaintext);
    int pad_len = AES_BLOCK_SIZE - (plaintext_len % AES_BLOCK_SIZE);
    for (int i = 0; i < pad_len; i++) {
        plaintext[plaintext_len + i] = pad_len;
    }
    plaintext_len += pad_len;

    // Encrypt
    int num = 0;
    AES_cfb128_encrypt(plaintext, ciphertext, plaintext_len, &encryptKey, iv, &num, AES_ENCRYPT);

    // Reset IV for decryption
    unsigned char iv_dec[AES_BLOCK_SIZE];
    memcpy(iv_dec, iv, AES_BLOCK_SIZE);

    // Decrypt
    num = 0;
    AES_cfb128_encrypt(ciphertext, decryptedtext, plaintext_len, &decryptKey, iv_dec, &num, AES_DECRYPT);

    // Remove padding
    pad_len = decryptedtext[plaintext_len - 1];
    decryptedtext[plaintext_len - pad_len] = '\0';

    // Print results
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < plaintext_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

