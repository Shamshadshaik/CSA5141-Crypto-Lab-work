#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function to compute gcd
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to compute modular inverse using Extended Euclidean Algorithm
unsigned long long mod_inverse(unsigned long long e, unsigned long long phi) {
    unsigned long long t = 0, new_t = 1;
    unsigned long long r = phi, new_r = e;

    while (new_r != 0) {
        unsigned long long quotient = r / new_r;
        unsigned long long temp = t;
        t = new_t;
        new_t = temp - quotient * new_t;
        temp = r;
        r = new_r;
        new_r = temp - quotient * new_r;
    }

    if (r > 1) return -1; // No inverse
    if (t < 0) t += phi;
    return t;
}

// Function to perform modular exponentiation
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to generate RSA keys
void generate_keys(unsigned long long *n, unsigned long long *e, unsigned long long *d) {
    unsigned long long p = 61; // Example prime
    unsigned long long q = 53; // Example prime
    *n = p * q;
    unsigned long long phi = (p - 1) * (q - 1);

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    *e = 17;
    while (gcd(*e, phi) != 1) {
        (*e)++;
    }

    // Compute d, the modular inverse of e mod phi
    *d = mod_inverse(*e, phi);
}

// Function to encrypt a message
unsigned long long rsa_encrypt(unsigned long long msg, unsigned long long e, unsigned long long n) {
    return mod_exp(msg, e, n);
}

// Function to decrypt a message
unsigned long long rsa_decrypt(unsigned long long cipher, unsigned long long d, unsigned long long n) {
    return mod_exp(cipher, d, n);
}

int main() {
    unsigned long long n, e, d;
    generate_keys(&n, &e, &d);

    printf("Public Key: (e = %llu, n = %llu)\n", e, n);
    printf("Private Key: (d = %llu, n = %llu)\n", d, n);

    unsigned long long msg = 42; // Example message
    unsigned long long encrypted = rsa_encrypt(msg, e, n);
    unsigned long long decrypted = rsa_decrypt(encrypted, d, n);

    printf("Original message: %llu\n", msg);
    printf("Encrypted message: %llu\n", encrypted);
    printf("Decrypted message: %llu\n", decrypted);

    // If private key is leaked, generate new keys with new n
    printf("\nPrivate key leaked! Generating new keys...\n");
    generate_keys(&n, &e, &d);

    printf("New Public Key: (e = %llu, n = %llu)\n", e, n);
    printf("New Private Key: (d = %llu, n = %llu)\n", d, n);

    encrypted = rsa_encrypt(msg, e, n);
    decrypted = rsa_decrypt(encrypted, d, n);

    printf("Original message: %llu\n", msg);
    printf("Encrypted message: %llu\n", encrypted);
    printf("Decrypted message: %llu\n", decrypted);

    return 0;
}

