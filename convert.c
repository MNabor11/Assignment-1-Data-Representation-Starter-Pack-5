//
// Created by Mateo on 9/11/2025.
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
