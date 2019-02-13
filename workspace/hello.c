#include <string.h>
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string s = get_string("SAY IT: ");
    printf("hello, world!\n%s\n", s);
    char c = 'A';
    printf("%c %i\n", c, c);
    printf("%s\n", strtok(s, "#"));

    int *ertyness;
    printf("%lu\n", sizeof(ertyness));
    int erty2[55];
    ertyness = erty2;
    printf("%lu\n", sizeof(ertyness));
    int i = 54;
    ertyness[i] = 2;
    printf("%i\n", ertyness[i]);
}