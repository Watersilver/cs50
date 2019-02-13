// Greedy algorithm

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main()
{
    // Get how much change is owed
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    // Convert change to cents
    change *= 100;
    int change_in_cents = roundf(change);

    // Determine minimum number of coins
    int min_coins = 0;
    int coin_value;
    for (int coin_index = 0; coin_index < 4; coin_index++)
    {
        // Choose coin value from available coins in descending order
        switch (coin_index)
        {
            case 0:
                coin_value = 25;
                break;

            case 1:
                coin_value = 10;
                break;

            case 2:
                coin_value = 5;
                break;

            case 3:
                coin_value = 1;
                break;
        }

        // Use as many coins of value: coin_value as possible
        while (change_in_cents >= coin_value)
        {
            change_in_cents -= coin_value;
            min_coins += 1;
        }
    }
    printf("%i\n", min_coins);
}