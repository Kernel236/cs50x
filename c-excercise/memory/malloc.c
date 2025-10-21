#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{   
    if (argc < 2)
    {   
        printf("Restart program with your name as argument please!\n");
        return 1;
    }
    else 
    {
        printf("Hi %s, Welcome in your memory Hotel!\n"
            "Give an array of n number we will find an address to them and their copy too\n" "...\n", argv[1]);

        printf("\n");
        int n = get_int("How many number you do want insert? ");
        if (n <= 0 || n > 10000)
        {
            printf("Please enter a positive number greater than 0.\n");
            return 1;
        }
        int *x = malloc(n * sizeof(int));
        if (x == NULL)
        {
            printf("Memory allocation failed for x.\n");
            return 1;
        }
        int *y = malloc(n * sizeof(int));
        if (y == NULL)
        {
            printf("Memory allocation failed for y.\n");
            free(x);
            return 1;
        }
        for (int j = 0; j < n; j++)
        {
            *(y+j) = get_int("Insert number[#%i]:  ", j + 1);
        }
        printf("\n");
        for (int i = 0; i < n; i++)
        {
            *(x+i) = *(y+i);
            printf("---------------------------------------------------------\n");
            printf("COPY number %i complete!\n" "Your %i number [%i] is stored at --> %p\n" 
                "Copy of %i number [%i] is stored at --> %p\n",
                i +1, i + 1, y[i], &y[i], i + 1, x[i], &x[i]);
            printf("---------------------------------------------------------\n");
        }
        printf("\n""\n");
        printf("Full copy and room assignment succesful!\n"
            "Thank for choose our service\n");
        free(x);
        x = NULL;
        free(y);
        y = NULL;
    }
    return 0;
}  