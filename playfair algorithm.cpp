#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generatePlayfairMatrix(char key[], char matrix[5][5]) {
    char alphabet[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Ignoring 'J' in the alphabet
    int keylen = strlen(key);
    int alphalen = strlen(alphabet);
    int i, j, k;
    int keypos[26] = {0};

    for (i = 0; i < keylen; i++) {
        if (key[i] == 'J') {
            keypos['I' - 'A'] = 1;
        } else {
            keypos[toupper(key[i]) - 'A'] = 1;
        }
    }

    k = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            while (keypos[alphabet[k] - 'A'] == 1) {
                k++;
            }
            matrix[i][j] = alphabet[k];
            keypos[alphabet[k] - 'A'] = 1;
            k++;
        }
    }
}
 
void playfairEncrypt(char matrix[5][5], char plaintext[]) {
    
}

int main() {
    char key[] = "KEYWORD";
    char plaintext[] = "HELLO";
    char matrix[5][5];

    generatePlayfairMatrix(key, matrix);

    printf("Playfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Plaintext: %s\n", plaintext);
    playfairEncrypt(matrix, plaintext);

    return 0;
}
