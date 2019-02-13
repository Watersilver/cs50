// Crack 5 MAXSIZE case sensitive letter-only code using brute force.

#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define ALPHABETSIZE 26
#define ALPHABETDOUBLESIZE 52
#define LOWERSTART 'a'
#define UPPERSTART 'A'
#define MAXSIZE 5

int brute_force(string salt, string hash, string key);
void advance_next_letter(int index, string key, int keyindex[]);

char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.";

int main(int argc, string argv[])
{
    // Make sure there is one argument
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    // Make sure the input's a hashed password
    for (int i = 0; i < 13; i++)
    {
        if (!(((argv[1][i] >= LOWERSTART) && (argv[1][i] <= LOWERSTART + ALPHABETSIZE)) ||
              ((argv[1][i] >= UPPERSTART) && (argv[1][i] <= UPPERSTART + ALPHABETSIZE)) ||
              ((argv[1][i] >= '0') && (argv[1][i] <= '9')) || argv[1][i] == '.' || argv[1][i] == '/') ||
            strlen(argv[1]) != 13)
        {
            printf("That wasn't a hashed password\n");
            return 1;
        }
    }

    // Retrieve salt
    char salt[3];
    for (int i = 0; i < 2; i++)
    {
        salt[i] = argv[1][i];
    }
    salt[2] = '\0';

    // Store found password in key
    char key[MAXSIZE + 1];
    brute_force(salt, argv[1], key);
    printf("%s\n", key);

    return 0;
}

// Cycle through all permutations until a password matches given
int brute_force(string salt, string hash, string key)
{
    // nullify received string key
    for (int i = 1; i <= MAXSIZE; i++)
    {
        key[i] = '\0';
    }
    key[0] = alphabet[0];

    // This will be used as a letter in the alphabet array
    int keyindex[MAXSIZE];
    for (int i = 0; i < MAXSIZE; i++)
    {
        keyindex[i] = 0;
    }

    // Loop until the password is found, or the MAXSiZE is exceeded
    while (true)
    {
        // Check if the password's been found
        if (strcmp(crypt(key, salt), hash) == 0)
        {
            return 0;
        }

        // Proceed to next permutation
        keyindex[0] += 1;
        key[0] = alphabet[keyindex[0]];
        // After getting through all letters, go back to first and raise the next one by one
        if (key[0] == '.')
        {
            key[0] = alphabet[0];
            advance_next_letter(1, key, keyindex);
            keyindex[0] = 0;
        }
    }
}

// Advances the next position when the previous has gone through all letters
void advance_next_letter(int index, string key, int keyindex[])
{
    key[index] = alphabet[keyindex[index]];
    keyindex[index] += 1;
    if (key[index] == '.')
    {
        keyindex[index] = 0;
        key[index] = alphabet[keyindex[index]];
        // Make sure you don't go beyond MAXSIZE
        if (index + 1 == MAXSIZE)
        {
            printf("could not find password\n");
            exit(1);
        }
        advance_next_letter(index + 1, key, keyindex);
    }
}