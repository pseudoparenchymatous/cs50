#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

#define BIG 512;

int main(void)
{
    int x = 42;
    int *i = &x;
    printf("x is %i\n", x);
    printf("&x is %p\n", &x);
    printf("i is %p\n", i);
    printf("*i is %i\n", *i);
    printf("&i is %p\n", &i);
    int *ii = i;
    printf("ii is %i\n", *ii);

}