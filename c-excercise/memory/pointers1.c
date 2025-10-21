/*
 * This program prompts the user to input a string and then iterates through each character,
 * printing the memory address of each character in the string, including the terminating NULL byte ('\0').
 *
 * Key Features:
 * - Uses CS50's get_string to safely read a string from the user.
 * - For each character, prints:
 *     - The character itself.
 *     - Its ASCII value.
 *     - Its memory address.
 * - When the loop reaches the NULL terminator, prints its address separately.
 *
 * Useful for:
 * - Understanding how strings are stored in memory in C.
 * - Visualizing the location of each character and the NULL terminator.
 */
#include <cs50.h>
#include <stdio.h>
#include <string.h> 

int main(void)
{
    char *s = get_string("Save a string: ");
    if (s == NULL)
    {
        printf("No string was entered.\n");
        return 1;
    }
    for (int i = 0, len = strlen(s); i <= len; i++)
    {
        if (i == len)
        {
            printf("....\n");
            printf("The address of the NULL byte [\\0] is %p\n", &s[i]);
        }
        else
        {
            printf("The address of %c [ASCII = %i] is %p\n", *(s+i), *(s+i), &s[i]);
        }
    }
    return 0;
}