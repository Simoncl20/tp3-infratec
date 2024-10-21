#include <stdio.h>
#include <stdlib.h>

void intercambiarBits(unsigned char *vector, int x, int y) {
    int byte_x = x / 8;
    int bit_x = 7 - (x % 8);
    int byte_y = y / 8;
    int bit_y = 7 - (y % 8);

    unsigned char bit1 = (vector[byte_x] >> bit_x) & 1;
    unsigned char bit2 = (vector[byte_y] >> bit_y) & 1;

    if (bit1 != bit2) {
        vector[byte_x] ^= (1 << bit_x);
        vector[byte_y] ^= (1 << bit_y);
    }
}

void invertirSecuencia(unsigned char *vector, int x, int y) {
    while (x < y) {
        intercambiarBits(vector, x, y);
        x++;
        y--;
    }
}

int main() {
    int n;
    printf("Enter the number of elements (n): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of elements.\n");
        return 1;
    }

    unsigned char *vector = (unsigned char *)calloc(n, sizeof(unsigned char));
    if (vector == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the %d elements (0 to 255):\n", n);
    for (int i = 0; i < n; i++) {
        int temp;
        scanf("%d", &temp);
        if (temp < 0 || temp > 255) {
            printf("Invalid input. Please enter a value between 0 and 255.\n");
            i--;
            continue;
        }
        vector[i] = (unsigned char)temp;
    }

    int k;
    printf("Enter the number of bits to rotate (k): ");
    scanf("%d", &k);

    int m = n * 8;

    if (k < 0) {
        printf("Invalid rotation count.\n");
        free(vector);
        return 1;
    }
    k = k % m;

    invertirSecuencia(vector, 0, m - 1);

    if (m - k > 0) {
        invertirSecuencia(vector, 0, m - k - 1);
    }

    if (k > 0) {
        invertirSecuencia(vector, m - k, m - 1);
    }

    printf("Resulting vector in hexadecimal:\n");
    for (int i = 0; i < n; i++) {
        printf("%02X", vector[i]);
    }
    printf("\n");

    free(vector);

    return 0;
}
