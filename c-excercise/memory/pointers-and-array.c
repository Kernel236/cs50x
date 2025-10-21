#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    int A[] = {2, 4, 5, 8, 1};

    printf("// Stampa l'indirizzo di memoria salvato nella variabile A (equivalente a &A[0])\n");
    printf("%p\n", (void*)A);

    printf("// Stampa l'indirizzo di memoria del primo elemento dell'array (&A[0])\n");
    printf("%p\n", (void*)&A[0]);

    printf("// Stampa il valore del primo elemento dell'array (2)\n");
    printf("%d\n", A[0]);

    printf("// Stampa il valore puntato da A, cioè il primo elemento dell'array (2)\n");
    printf("%i\n", *A);

    printf("// Stampa l'indirizzo di memoria dell'intero array (uguale a A e &A[0] per array locali)\n");
    printf("%p\n", (void*)&A);

    return 0;
}