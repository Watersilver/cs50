#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Gimme natural number: ");
    }
    while (n <= 0);
    printf("%i\n", collatz(n));
}

int collatz(int n)
{
    if (n == 1)
    {
        return 0;
    }
    else if (n % 2)
    {
        return 1 + collatz(3 * n + 1);
    }
    else
    {
        return 1 + collatz(n * 0.5);
    }
}