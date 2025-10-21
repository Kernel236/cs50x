#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text, float n_word);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text, words);

    float L = letters * 100.0 / words;
    float S = sentences * 100.0 / words;

    // Compute the Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    // Print the grade level
    if (grade < 1)
    {
       printf("Before Grade 1\n"); 
    } 
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    } 
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    int n = strlen(text);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            sum += 1;
        }
    }
    return sum;
}

int count_words(string text)
{
    // Return the number of words in text
    int n = strlen(text);
    bool in_word = false;
    int word = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            if (in_word == false)
            {
            word++;
            in_word = true;
            }
        } 
        else
        {
            in_word = false;
        }
    }
    return word;
    
}

int count_sentences(string text, float n_word)
{
    int n = strlen(text);
    int n_sent = 0;
    bool in_word = false;
    int word = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            if (in_word == false)
            {
            word++;
            in_word = true;
            }
        } 
        else
        {
            in_word = false;
        }
        if ((text[i] == '.' || text[i] == '!' || text[i] == '?') && word > 1)
        {
                n_sent += 1;
                word = 0;
        }
    }
    return n_sent;
}

