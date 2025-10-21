#include <cs50.h>
#include <stdio.h>
#include <string.h>

/*
I want demostrate that string is just an array of singol char stored with
a NUL byte at the end \0 which effectivly in ASCII it's represented by value 0 
*/

int main(void)
{
    printf(
           "***************************\n"
           "String is an array of char\n"
           "***************************\n"
        );

    string s = get_string("Insert a string: ");
    
    printf(
           "1 Line print out a string\n"
           "2 Line iterate on string and print out single char\n"
           "3 Line iterate on string and print out respective ASCII integer revealing the NUL byte\n"
           "\n"
        );
    /*
    Simply print a string
    */
   printf("%s\n", s);

    /*
    Since string is an array of char we can print out single char iterating on 
    strings' single value. Note that it can be printed also as integer
    Let's find and print the NUL byte
    */

    for (int i = 0; i < strlen(s); i++) 
   {
    printf("%c", s[i]);
   }

   printf("\n");

    for (int j = 0; j <= strlen(s); j++) 
   {
    printf("%i ", s[j]);
   }
   printf("\n");
   printf("\n");
   printf("*****************************************\n"
    "EXTEND THE CONCEPT TO AN ARRAY OF STRING \n"
    "Look at the code in string.c\n"
    "*****************************************\n"
    "\n");
   
   string words[2];

   words[0] = get_string("Insert a word: ");
   words[1] = get_string("Insert a second word: ");

   printf("%s %s\n", words[0], words[1]);
   
   for (int i = 0; i < 2; i++)
   {
    int len = strlen(words[i]);
    for (int l = 0; l < len; l++)
    {
        printf("%c", words[i][l]);
    }
    printf(" ");
   }

   printf("\n");
   int n = strlen(words[0]);
   int m = strlen(words[1]);
   printf("The total number of letters used is %i\n", m + n);

   printf("\n");
}