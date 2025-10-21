#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool validate_key(string key);
string getCipher(string plain, string key);

int main (int argc, string argv[])
{
    // get the key 26 char
    // control number of argument from command line
    if (argc != 2)
    {
        printf("Please enter a valid KEY as argument\n");
        return 1;
    }
    // control length of the key 26 char
    int size_key = strlen(argv[1]);
    if (size_key != 26)
    {
        printf("Please enter a valid KEY as argument\n"
            "-Containing 26 characters\n");
            return 1;  
    }
    for (int i = 0; i < size_key; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Please enter a valid KEY as argument\n"
                "-Containing any character that is not an alphabetic character\n"
                "-Containing each letter exactly once\n");
                return 1;  
        }
    }

    bool is_valid = validate_key(argv[1]);
    if (is_valid != true)
    {
        printf("Please enter a valid KEY: DOUBLE char FOUND!\n"
    "-It must containin each letter exactly once\n");
        return 1;
    }
    //get input plain text
    string plaintext = get_string("plaintext: ");
    string chipertext;
    chipertext = getCipher(plaintext, argv[1]);
    printf("ciphertext: %s\n", chipertext);
    free(chipertext);
    return 0;
}

bool validate_key(string key)
{
    bool seen[26] = {false};
    int index = 0;
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (islower(key[i]))
        {
            index = key[i] - 'a';
        }
        else
        {
            index = key[i] - 'A';
        }
        
        if (seen[index] == true)
        {
            return false;  
        }
        seen[index] = true;
    }
    return true;
}

string getCipher(string plain, string key)
{
    int index = 0;
    int n = strlen(plain);
    
    string ciphered = malloc((n + 1) * sizeof(char));
    
    for (int i = 0; i < n; i++)
    {
        if (isalpha(plain[i]))
        {
            if (islower(plain[i]))
            {
                index = plain[i] - 'a';
                ciphered[i] = tolower(key[index]);
            }
            else
            {
                index = plain[i] - 'A';
                ciphered[i] = toupper(key[index]);
            }
        }
        else
        {
            ciphered[i] = plain[i];
        }
    }
    
    ciphered[n] = '\0';
    return ciphered;
}