#include<stdio.h>

int main (void)
{
    // Introductory message to provide context when the program starts
    printf("Demonstration of pointers and pointer to pointer in C\n\n");

    int x = 5;         // Declaration of an integer variable x and initialization to 5
    int *p;            // Declaration of a pointer to int p
    p = &x;            // p points to the address of x
    int **q;           // Declaration of a pointer to pointer to int q
    q = &p;            // q points to the address of p

    // Print the value of x and its address
    printf("Value of x: %d, Address of x: %p\n", x, (void*)&x);

    // Print the value of p (should be the address of x) and the value pointed by p (should be x)
    printf("Value of p (address of x): %p, Value pointed by *p: %d\n", (void*)p, *p);

    // Print the address of p
    printf("Address of p: %p\n", (void*)&p);

    // Print the value of q (should be the address of p) and the value pointed by q (should be the address of x)
    printf("Value of q (address of p): %p, Value pointed by *q (value of p, address of x): %p\n", (void*)q, (void*)*q);

    // Print the value pointed by *q (should be x) and the address to which *q points (should be the address of x)
    printf("Value pointed by **q (value of x): %d, Address pointed by *q (address of x): %p\n", *(*q), (void*)&*(*q));

    return 0;
}