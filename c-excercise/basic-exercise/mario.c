#include <stdio.h>
#include <cs50.h>

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

// Prints a grid of # of size x size
void print_grid(int size) 
{
    if (size < 1)
    {
        return;
    }
    
    print_grid(size -1);
    for (int i = 0; i < size; i++) // Loop over rows
    {
       printf("#"); // Print a # character
    }
    printf("\n"); // Newline after each row
}