# Encrypts input with Caesars Cypher and a given key, then prints it.

import sys
from cs50 import get_string


alphabet_size = 26


def main():
    # End program if not given key, or if given too many stuff
    if not len(sys.argv) == 2:
        print("Wrong number of command line arguments")
        return 1

    # Convert the key to an int
    k = int(sys.argv[1])

    # Ask for text to be encrypted
    text = get_string("plaintext: ")

    # Encrypt plaintext char by char
    ciphertext = []
    for i in text:
        # Only encrypt letters
        if i.isalpha():
            offset = ord('a') if i.islower() else ord('A')
            ciphertext.append(chr(offset + (ord(i) + k - offset) % alphabet_size))
        else:
            ciphertext.append(i)

    ciphertext = ''.join(ciphertext)
    print(f"ciphertext: {ciphertext}")

    return 0


if __name__ == "__main__":
    exit(main())