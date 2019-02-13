// Checks validity of credit card number

#include <stdio.h>
#include <cs50.h>

int print_card(int type);

int main(void)
{
    // Get card number from user
    long long card_number;
    do
    {
        card_number = get_long_long("Number: ");
    }
    while (card_number <= 0);

    // Count card digits
    int digits = 0;
    for (long long i = card_number; i > 0; i /= 10)
    {
        digits += 1;
    }

    // Check if card looks valid, and if
    // yes what type it is expected to be
    // if no print invalid and return
    int card_type = 0; //invalid
    switch (digits)
    {
        case 13:
            card_type = 1; //Visa
            break;

        case 15:
            card_type = 2; //AmericanExpress
            break;

        case 16:
            card_type = 4; //Visa or MasterCard
            break;

        default:
            card_type = 0;
            return print_card(card_type);
    }

    // Store card digits individually
    int card_array[digits];
    for (int i = 0; i < digits; i++)
    {
        card_array[i] = card_number % 10;
        card_number /= 10;
    }

    // Check if first digits (last in array!!) correspond
    // to the expected card. Else, it's invalid.
    // Also determine whether it's Visa or Mastercard.
    int sum = card_array[digits - 1] * 10 + card_array[digits - 2];
    switch (card_type)
    {
        case 1:
            if (card_array[digits - 1] != 4)
            {
                card_type = 0;
                return print_card(card_type);
            }
            break;

        case 2:
            if (sum != 34 && sum != 37)
            {
                card_type = 0;
                return print_card(card_type);
            }
            break;

        case 4:
            if (card_array[digits - 1] == 4)
            {
                card_type = 1;
            }
            else if (sum == 51 || sum == 52 || sum == 53 || sum == 54 || sum == 55)
            {
                card_type = 3;
            }
            else
            {
                card_type = 0;
                return print_card(card_type);
            }
            break;
    }

    // Check if syntactically valid with Luhn’s algorithm
    // First Multiply every other digit by 2, starting with the
    // second-to-last (second in array) digit and add the products' digits
    int digits_sum = 0;
    for (int i = 1; i < digits; i += 2)
    {
        card_array[i] *= 2;
        digits_sum += card_array[i] % 10 + card_array[i] / 10;
    }
    // Add the sum to the sum of the digits that weren’t multiplied by 2
    for (int i = 0; i < digits; i += 2)
    {
        digits_sum += card_array[i];
    }
    // If the total’s last digit is 0 it's valid
    if (digits_sum % 10 == 0)
    {
        print_card(card_type);
    }
    else
    {
        card_type = 0;
        print_card(card_type);
    }
}

// Take type and print corresponding string
int print_card(int type)
{
    string print_string;
    switch (type)
    {
        case 0:
            print_string = "INVALID";
            break;

        case 1:
            print_string = "VISA";
            break;

        case 2:
            print_string = "AMEX";
            break;

        case 3:
            print_string = "MASTERCARD";
            break;

        default:
            print_string = "INVALID";
            break;
    }

    printf("%s\n", print_string);
    return 0;
}