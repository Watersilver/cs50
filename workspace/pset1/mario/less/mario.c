// Draws hash steps from left to right. Last step is double as wide as others

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

    // Print half-pyramid
    char c;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= height; j++)
        {
            c = (j < height - 1 - i) ? ' ' : '#';
            printf("%c", c);
        }
        printf("\n");
    }
}