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
int main(){
printf("Hello World");
    char input[65];
    uint32_t n = 156;
    int base = 8;
    div_convert(n,base,input);
    printf("%s",input);
return 0;
}
