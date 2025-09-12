//
// Created by Mateo on 9/10/2025.
//
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void div_convert ( uint32_t n , int base , char *out ) {
    char temp[65];
    int pos = 0;
    // Handle zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }
    while (n >0) {
        int remainder = n % base;

        if (remainder < 10)
            temp[pos++] = '0' + remainder;
        else
            temp[pos++] = 'A'+ (remainder-10);
        n =  n / base;
    }
    for (int i = 0; i < pos; ++i) {
        out[i] = temp[pos - 1 - i];
    }
    out[pos] = '\0';
}
void sub_convert(uint32_t n, int base, char *out) {
    char temp[65];
    int pos = 0;
    uint32_t sub = 1;
    if (n == 0) {
        strcpy(out, "0");
        return;
    }
    while (sub > 0) {
        int digit = 0;
        while (n >= sub) {
            n -= sub;
            digit++;
        }
        temp[pos++] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
        sub /= base;
    }
    temp[pos] = '\0';
    strcpy(out, temp);
}

void print_tables(uint32_t n) {
    char bin[33], oct [12], hex[9];

    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    div_convert(n, 16, hex);
    printf (" Original : Binary =%s Octal =%s Decimal =%u Hex =%s\n", bin, oct, n ,hex);

    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin);
    div_convert(shifted, 8, oct);
    div_convert(shifted, 16, hex);
    printf(" Left Shift by 3: Binary =%s Octal =%s Decimal =%u Hex =%s\n",
           bin, oct, shifted, hex);

    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin);
    div_convert(masked, 8, oct);
    div_convert(masked, 16, hex);
    printf(" AND with 0xFF: Binary =%s Octal =%s Decimal =%u Hex =%s\n",
           bin, oct, masked, hex);
}
int main() {
    FILE *file = fopen("a1_test_file.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }
    int testPassed=0;
    int testFailed=0;

    char line[256];
    char answer[65];
    int test_num = 1;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '#' || strlen(line) <= 1) {
            continue;
        }
        char cmd[32], expected[65];
        uint32_t n;
        int base;
        // div_convert
        if (sscanf(line, "div_convert %u %d %s", &n, &base, expected) == 3) {
            div_convert(n, base, answer);
            if (strcmp(answer, expected) == 0) {
                printf("Test %d: div_convert (%u , %d) -> Expected : \"%s\", Got : \"%s\" [ PASS ]\n",
                       test_num, n, base, expected, answer);
                testPassed++;
            } else {
                printf("Test %d: div_convert (%u , %d) -> Expected : \"%s\", Got : \"%s\" [ FAIL ]\n",
                       test_num, n, base, expected, answer);
                testFailed++;
            }
            test_num++;
        }

        // sub_convert
        else if (sscanf(line, "sub_convert %u %d %s", &n, &base, expected) == 3) {
            sub_convert(n, base, answer);
            if (strcmp(answer, expected) == 0) {
                printf("Test %d: sub_convert (%u , %d) -> Expected : \"%s\", Got : \"%s\" [ PASS ]\n",
                       test_num, n, base, expected, answer);
                testPassed++;

            } else {
                printf("Test %d: sub_convert (%u , %d) -> Expected : \"%s\", Got : \"%s\" [ FAIL ]\n",
                       test_num, n, base, expected, answer);
                testFailed++;
            }
            test_num++;
        }

    }
    printf("\nSummary: %d/%d tests passed\n", testPassed, testPassed + testFailed);
    fclose(file);
    return 0;
}
