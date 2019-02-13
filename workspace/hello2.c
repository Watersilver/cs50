#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x;

    printf("Enter your name: ");
    string name = get_string();
    printf("hello, %s!\n", name);

    x = (1>2) ? 100 : 33;

    switch(true)
    {
        case 1 == 1: printf("yay %i\n", x); break;
    }
}