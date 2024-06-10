#include <stdio.h>
#include <ctype.h>
void caesarCipher(char* text, int k) {
    char c;
    int i = 0;
    while (text[i] != '\0') {
        c = text[i];

        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            text[i] = (c - base + k) % 26 + base;
        }
        i++;
    }
}
int main() {
    char text[100];
    int k;
    printf("Enter the text to be encrypted: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the shift value (1-25): ");
    scanf("%d", &k);
    if (k < 1 || k > 25) {
        printf("Invalid shift value. Please enter a value between 1 and 25.\n");
        return 1;
    }
    caesarCipher(text, k);
    printf("Encrypted text: %s\n", text);
    return 0;
}
