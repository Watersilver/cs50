//Draws hash pyramid with 2 space gap in the middle.

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get height by user
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 0 || height > 23);

    // Print pyramid
    char c;
    for (int i = 0; i < height; i++)
    {
        // Left half-pyramid
        for (int j = 0; j < height; j++)
        {
            c = (j < height - i - 1) ? ' ' : '#';
            printf("%c", c);
        }
        // Gap
        printf("  ");
        // Right half-pyramid
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}