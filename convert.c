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
void oct_to_bin(const char *oct, char *out ) {
    char *p = out;
    while (*oct) {
        switch (*oct) {
            case '0': strcpy(p, "000"); break;
            case '1': strcpy(p, "001"); break;
            case '2': strcpy(p, "010"); break;
            case '3': strcpy(p, "011"); break;
            case '4': strcpy(p, "100"); break;
            case '5': strcpy(p, "101"); break;
            case '6': strcpy(p, "110"); break;
            case '7': strcpy(p, "111"); break;
            default: strcpy(p, "ben"); break;
        }
        p += 3;
        oct++;
    }
    *p = '\0';
}
void oct_to_hex(const char *oct, char *out) {
    char bin[100] = "";
    oct_to_bin(oct, bin);
    int len = strlen(bin);
    int pad = (4 - (len % 4)) % 4;
    char padded[100] = "";
    for (int i = 0; i < pad; i++) strcat(padded, "0");
    strcat(padded, bin);
    int hex_index = 0;
    for (int i = 0; padded[i]; i += 4) {
        int val = 0;
        for (int j = 0; j < 4; j++) {
            val = val * 2 + (padded[i + j] - '0');
        }
        if (val < 10)
            out[hex_index++] = '0' + val;
        else
            out[hex_index++] = 'A' + val - 10;
    }
    out[hex_index] = '\0';
}
void hex_to_bin(const char *hex, char *out) {
    while (*hex) {
        char c = toupper(*hex); // Normalize to uppercase

        switch (c) {
            case '0': strcpy(out, "0000"); break;
            case '1': strcpy(out, "0001"); break;
            case '2': strcpy(out, "0010"); break;
            case '3': strcpy(out, "0011"); break;
            case '4': strcpy(out, "0100"); break;
            case '5': strcpy(out, "0101"); break;
            case '6': strcpy(out, "0110"); break;
            case '7': strcpy(out, "0111"); break;
            case '8': strcpy(out, "1000"); break;
            case '9': strcpy(out, "1001"); break;
            case 'A': strcpy(out, "1010"); break;
            case 'B': strcpy(out, "1011"); break;
            case 'C': strcpy(out, "1100"); break;
            case 'D': strcpy(out, "1101"); break;
            case 'E': strcpy(out, "1110"); break;
            case 'F': strcpy(out, "1111"); break;
            default:  strcpy(out, "ben"); break;
        }

        out += 4;
        hex++;
    }
    *out = '\0';
}
void to_sign_magnitude(int32_t n, char *out) {
    uint32_t result;
    if (n >= 0) {
        result = (uint32_t)n;
    } else {
        result = (1U << 31) | ((uint32_t)(-n));
    }
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (result & (1U << i)) ? '1' : '0';
    }
    out[32] = '\0';
}
void to_ones_complement(int32_t n, char *out) {
    uint32_t result;
    if (n >= 0) {
        result = (uint32_t)n;
    } else {
        result = ~((uint32_t)(-n));
    }
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (result & (1U << i)) ? '1' : '0';
    }
    out[32] = '\0';
}
void to_twos_complement(int32_t n, char *out) {
    uint32_t result = (uint32_t)n;
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (result & (1U << i)) ? '1' : '0';
    }
    out[32] = '\0';
}