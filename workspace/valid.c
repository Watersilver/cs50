#include <stdio.h>
#include <cs50.h>

bool valid_triangle(float a, float b, float c);

int main(void)
{
    int a = get_int("give me a: ");
    int b = get_int("give me b: ");
    int c = get_int("give me c: ");

    printf("Is the triangle ABC valid? %s\n", valid_triangle(a, b, c) == true ? "true" : "false");
}

bool valid_triangle(float a, float b, float c)
{
    if (a <= 0 || b <= 0 || c <=0)
        return false;

    if (a+b>c && b+c>a && c+a>b)
        return true;
    else
        return false;
}