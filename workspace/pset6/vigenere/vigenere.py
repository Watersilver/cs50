# Encrypts input with Vigenere's Cypher and a given keyword, then prints it.

from cs50 import get_string
import sys

ALPHABETSIZE = 26


def main():
    # End program if not given keyword, or if given too many stuff
    if not len(sys.argv) == 2:
        print("Wrong input. Please input the name plus one argument only.")
        return 1

    # End program if input is not alphabetic
    if not sys.argv[1].isalpha():
        print("Wrong input. Please letters only.")
        return 1

    # Convert the keyword to an int list
    k = []
    for i in sys.argv[1]:
        k.append(ord(i.lower()) - ord('a'))

    # Get text to be encrypted from user
    text = get_string("plaintext: ")

    # This'll be the index of the key
    j = 0
    # This'll be the ciphertext
    ctext = []

    # Encrypt text
    for i in text:
        # Make sure to only encrypt letters
        if i.isalpha():
            i = caesar_formula(ord(i), k[j % len(k)], ord('a' if i.islower() else 'A'))
            j += 1

        ctext.append(i)

    # Print encrypted text
    ctext = "".join(ctext)
    print(f"ciphertext: {ctext}")

    return 0


def caesar_formula(letter, key, offset):
    return chr(offset + (letter + key - offset) % ALPHABETSIZE)


if __name__ == "__main__":
    exit(main())