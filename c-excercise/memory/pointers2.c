#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main(void)
{
    int a = 10;
    int *p = &a;

    printf("Variable a || value=%i || address @[%p]\n", a, &a);
    printf("-----------------------------------------------------\n");
    printf("Pointer to %p ------> value there=%i\nPointer personal address @[%p]\n", p, *p, &p);
    printf("Pointer + 1 advances by sizeof(int) bytes in memory (i.e., to the next int location)\np+1 -> @[%p]\nValue there= %i\n", p+1, *(p+1));

    return 0;
} 