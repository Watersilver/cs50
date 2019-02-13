// Encrypts input with Vigenere's Cypher and a given keyword, then prints it.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABETSIZE 26
#define LOWERSTART 'a'
#define UPPERSTART 'A'

char caesar_formula(char letter, int key, char displacement);

int main(int argc, string argv[])
{
    // End program if not given keyword, or if given too many stuff, or given non letters
    if (argc != 2)
    {
        // Insult user
        printf("Error: Wrong input. Please input the name plus one argument only.\n");
        return 1;
    }
    // keyword length
    int klen = strlen(argv[1]);

    // Convert the keyword to an int array, check if correct input
    int k[strlen(argv[1])];
    for (int i = 0; i < klen; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Error: Wrong input. Please letters only.\n");
            return 1;
        }

        if (islower(argv[1][i]))
        {
            k[i] = argv[1][i] - LOWERSTART;
        }
        else
        {
            k[i] = argv[1][i] - UPPERSTART;
        }
    }

    string text = get_string("plaintext: ");

    // Encrypt plaintext char by char
    for (int i = 0, plen = strlen(text), j = 0; i < plen; i++)
    {
        // Make sure to only encrypt letters
        if (isalpha(text[i]))
        {
            text[i] = caesar_formula(text[i], k[(j) % klen], islower(text[i]) ? LOWERSTART : UPPERSTART);
            j++;
        }
    }

    printf("ciphertext: %s\n", text);

    return 0;
}

//Implements Caesar's Cipher formula if the first letter is not counted as 0 but as 'displacement'
char caesar_formula(char letter, int key, char displacement)
{
    return displacement + (letter + key - displacement) % ALPHABETSIZE;
}