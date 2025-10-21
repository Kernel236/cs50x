#include <stdio.h>
#include <cs50.h>

int main(void) {
    int x = get_int("Choose a x: ");
    int y = get_int("Choose a y: ");

    if (x < y) {
        printf("%d is less than %d\n", x, y);
    } 
    else if (x > y) {
        printf("%d is greater than %d\n", x, y);
    } 
    else {
        printf("%d is equal %d\n", x, y);
    }
}