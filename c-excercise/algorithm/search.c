#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(void) 
{
// Note: The array is unsorted, which is fine for linear search.
// If you switch to binary search, you must sort the array first.
int n[] = {
    50, 35, 268, 354, 90, 65, 9, 17, 45, 12, 88, 23, 67, 101, 333, 444, 255, 266, 277, 288, 299,
    3, 6, 8, 13, 21, 34, 55, 89, 144, 233, 377, 42, 73, 19, 27, 31, 58, 62, 75, 82, 97, 104, 120,
    200, 250, 300, 350, 400, 450, 500, 150, 160, 170, 180, 190, 210, 220, 230, 240, 260, 270, 280,
    290, 310, 320, 330, 340, 360, 370, 380, 390, 410, 420, 430, 440, 460, 470, 480, 490, 2, 4, 16,
    32, 64, 128, 256, 384, 496, 412, 418
};
   
    // Linear search algorithm: iterate through the array to find a target value
    int target = get_int("Find a number in the list: ");
    int array_length = sizeof(n) / sizeof(n[0]);
    bool found = false;
    for (int i = 0; i < array_length; i++)
    {
        if (n[i] == target)
        {
            found = true;
            printf("Found %d at index %d\n", target, i);
            break;
            return 0;
        }
    }
    if (!found)
    {
        printf("%d not found in the array.\n", target);
        return 1;
    }
}
