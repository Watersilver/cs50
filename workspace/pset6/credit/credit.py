# Chacks validity of credit card number

from cs50 import get_int


def main():

    # Get card number from user
    card_number = 0
    while card_number <= 0:
        card_number = get_int("Number: ")

    # Turn card into list of digits
    card_array = list(map(int, str(card_number)))

    # Count card digits
    digits = len(card_array)

    # Check if card looks valid, and if
    # yes what type it is expected to be
    # if no print invalid and return
    card_type = 0  # invalid
    if digits == 13:
        card_type = 1  # Visa

    elif digits == 15:
        card_type = 2  # ArmericanExpress

    elif digits == 16:
        card_type = 4  # Visa or MasterCard

    else:
        card_type = 0
        return print_card(card_type)

    # Check if first digits correspond to
    # the expected card. Else, it's invalid.
    # Also determine whether it's Visa or Mastercard
    first_two_digit_sum = card_array[0] * 10 + card_array[1]
    if card_type == 1:
        if card_array[0] != 4:
            card_type = 0
            return print_card(card_type)

    elif card_type == 2:
        if first_two_digit_sum != 34 and first_two_digit_sum != 37:
            card_type = 0
            return print_card(card_type)

    elif card_type == 4:
        if card_array[0] == 4:
            card_type = 1

        elif first_two_digit_sum > 50 and first_two_digit_sum < 56:
            card_type = 3

        else:
            card_type = 0
            return print_card(card_type)

    # Check if syntactically valid with Luhn’s algorithm
    # First Multiply every other digit by 2, starting with the
    # second-to-last digit and add the products' digits
    digits_sum = 0
    card_array.reverse()
    for i in range(1, len(card_array), 2):
        card_array[i] *= 2
        digits_sum += card_array[i] % 10 + card_array[i] // 10

    # Add the sum to the sum of the digits that weren't multiplied by 2
    for i in range(0, len(card_array), 2):
        digits_sum += card_array[i]

    # If the total's last digit is 0 it's valid
    if digits_sum % 10 == 0:
        print_card(card_type)

    else:
        card_type = 0
        print_card(card_type)


# Take card_type and print corresponding string
def print_card(card_type):
    if card_type == 0:
        print_string = "INVALID"

    elif card_type == 1:
        print_string = "VISA"

    elif card_type == 2:
        print_string = "AMEX"

    elif card_type == 3:
        print_string = "MASTERCARD"

    else:
        print_string = "INVALID"

    print(print_string)
    return 0


if __name__ == "__main__":
    main()