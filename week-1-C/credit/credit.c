#include <cs50.h>
#include <stdio.h>


int main(void)
{
    long credit_number = get_long("Enter you credit card number [NO hyphen]: "); 
    printf("Your number is: %lu \n", credit_number);

    int sum1 = 0;
    int sum2 = 0;
    int pos = 1;
    int first;
    while (credit_number > 0){
        int digit = credit_number % 10;
        first = digit;
        if (pos % 2 == 0){
            digit *= 2;
            if (digit > 9)
            {
                digit -= 9;
            }
            sum1 += digit;
        } else {
            sum2 += digit;
        }
        pos += 1;
        credit_number = credit_number / 10;
    }
    int results = sum1 + sum2;

    printf("Luhn checksum result = %i\n", results);

    if (results % 10 != 0){
        printf("INVALID\n");
    } else {
        if (first == 3){
            printf("AMEX\n");
        }
        if (first == 4){
            printf("VISA\n");
        }
        if (first == 5){
            printf("MASTERCARD\n");
        }
    }
    return 0;
}