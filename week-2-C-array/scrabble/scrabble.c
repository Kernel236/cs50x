#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Scrabble letter values
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int get_score(string word);

int main (void)
{
    // Get input from both players
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");
    
    // Calculate scores for both players
    int score1 = get_score(p1);
    int score2 = get_score(p2);
    
    // Print winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    
    return 0;
}

int get_score(string word)
{
    int score = 0;
    
    // Loop through each character in the word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Convert to uppercase to handle both cases
        char c = toupper(word[i]);
        
        // Check if it's a letter
        if (c >= 'A' && c <= 'Z')
        {
            // Calculate array index
            int index = c - 'A';
            score += POINTS[index];
        }
    }
    return score;
}