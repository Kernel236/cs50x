#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    printf("Enter size of array\n");
    scanf("%d" , &n);
    int *A = (int*) malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
        A[i] = i+1; 
    }
    int *B = (int*)realloc(A, 2*n*sizeof(int));
    printf("Prev block address = %p, new address post expansion = %p\n",A,B);
    for (int i = 0; i < n; i++)
    {
        printf("%i ", B[i]);
    }
    free(B);
    printf("\n");
}   