#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    double x = get_double("Enter a number: ");
    double y = get_double("Enter a second number: ");
    string operation = get_string("Choose one operation [+, -, *, /]: ");

    double z = 0.0;

    if (strcmp(operation, "/") == 0)
    {
        z = x / y;
    }
    else if (strcmp(operation, "*") == 0)
    {
        z = x * y;
    }
    else if (strcmp(operation, "+") == 0)
    {
        z = x + y;
    }
    else if (strcmp(operation, "-") == 0)
    {
        z = x - y;
    } 
    else
    {
        printf("Invalid Operation, Please choose a valid operation sign\n");
        return 1;
    }    

    printf("%.5f\n", z);
}