#include<stdio.h>

int main(void)
{
    int a = 1025;
    int *p;
    p = &a;
    printf("size of integer is %lu bytes\n", sizeof(int));
    printf("Address = %p, value = %i\n", p, *p);
    char *p0;
    p0 = (char*)p; // TYPECASTING 
    printf("size of char is %lu bytes\n", sizeof(char));
    printf("Address = %p, value = %d\n", p0, *p0);
}