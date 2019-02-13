#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define ALPHABETSIZE 26
#define LOWERSTART 'a'
#define UPPERSTART 'A'
#define MAXSIZE 5

int brute_force(string salt, string hash, string key);
void advance_counter(int index, string key);

int main(int argc, string argv[])
{
    printf("%s\n", crypt("YES", "50")); // anushree:50xcIMJ0y.RXo
    printf("%s\n", crypt("CA", "50")); // brian:50mjprEcqC/ts
    printf("%s\n", crypt("UPenn", "50")); // bjbrown:50GApilQSG3E2
    printf("%s\n", crypt("lloyd", "50")); // lloyd:50n0AAUD.pL8g
    printf("%s\n", crypt("maybe", "50")); // malan:50CcfIk1QrPr6
    printf("%s\n", crypt("TF", "50")); // maria:509nVI8B9VfuA
    printf("%s\n", crypt("nope", "50")); // natmelo:50JIIyhDORqMU
    printf("%s\n", crypt("ROFL", "50")); // rob:50JGnXUgaafgc
    printf("%s\n", crypt("NO", "51")); // stelios:51u8F0dkeDSbY
    printf("%s\n", crypt("LOL", "50")); // zamyla:50cI2vYkF0YU2

    if (argc != 2)
    {
        printf("Error: you suck balls\n");
        return 1;
    }

    char salt[3];
    for (int i = 0; i < 2; i++)
    {
        salt[i] = argv[1][i];
    }
    salt[2] = '\0';

    char key[MAXSIZE + 1];

    brute_force(salt, argv[1], key);
    printf("%s\n", key);

    return 0;
}

int brute_force(string salt, string hash, string key)
{
    for (int i = 1; i <= MAXSIZE; i++)
    {
        key[i] = '\0';
    }

    key[0] = UPPERSTART;

    while (true)
    {
        //check
        //printf("%s:%s\n", key, crypt(key, salt));
        if (strcmp(crypt(key, salt), hash) == 0)
        {
            return 0;
        }

        key[0] += 1;
        if (key[0] == UPPERSTART+ALPHABETSIZE)
        {
            key[0] = LOWERSTART;
        }
        if (key[0] == LOWERSTART+ALPHABETSIZE)
        {
            key[0] = UPPERSTART;
            advance_counter(0 + 1, key);
        }
    }
}

void advance_counter(int index, string key)
{
    if (key[index] == '\0')
    {
        key[index] = UPPERSTART - 1;
    }
    key[index] += 1;
    if (key[index] == UPPERSTART+ALPHABETSIZE)
    {
        key[index] = LOWERSTART;
    }
    if (key[index] == LOWERSTART+ALPHABETSIZE)
    {
        key[index] = UPPERSTART;
        advance_counter(index + 1, key);
    }
}