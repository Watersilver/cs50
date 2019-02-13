// Encrypts input with Caesars Cypher and a given key, then prints it.

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
    // End program if not given key, or if given too many stuff
    if (argc != 2)
    {
        // Insult user
        printf("Wrong number of command line arguments.\n");
        return 1;
    }

    // Convert the key to an int
    int k = atoi(argv[1]);

    string text = get_string("plaintext: ");

    // Encrypt plaintext char by char
    for (int i = 0, plen = strlen(text); i < plen; i++)
    {
        // Make sure to only encrypt letters
        if (isalpha(text[i]))
        {
            text[i] = caesar_formula(text[i], k, islower(text[i]) ? LOWERSTART : UPPERSTART);
        }
    }

    printf("ciphertext: %s\n", text);

    if (!(k % ALPHABETSIZE))
    {
        // Insult user
        printf("Nice key, dumbass.\n");
    }

    return 0;
}

//Implements Caesar's Cipher formula if the first letter is not counted as 0 but as 'displacement'
char caesar_formula(char letter, int key, char displacement)
{
    return displacement + (letter + key - displacement) % ALPHABETSIZE;
}