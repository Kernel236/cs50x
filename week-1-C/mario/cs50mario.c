#include <cs50.h>
#include <stdio.h>

// Function that asks the user for the grid size
int get_size(void);

// Function that prints the grid
void print_grid(int size);

int main(void)
{
    // Gets the grid size from the user
    int n = get_size();
    // Prints an n x n grid
    print_grid(n);
}

// Asks the user to enter a size >= 1
int get_size(void)
{
    int n;
    do
    {
        n = get_int("Size: "); // Requests an integer from the user
    }
    while (n < 1); // Continues while n is less than 1
    return n;
}

/// Prints a grid of # of size x size
void print_grid(int size)
{
    if (size < 1)
    {
        return;
    }

    for (int i = 0; i < size; i++) // Loop over rows
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n"); // Newline after each row
    }
}

