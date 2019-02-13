# Crack MAXSIZE case sensitive letter-only code using brute force.

import crypt
import sys

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz."
MAXSIZE = 5

key = []


def main(hashed_password):
    # Make sure the input's a hashed password
    if not len(hashed_password) == 13:
        print("That wasn't a hashed password")
        return 1

    for i in hashed_password:
        if (not i.isalnum()) and i != '.' and i != '/':
            print("That wasn't a hashed password")
            return 1

    # Retrieve salt
    salt = hashed_password[:2]

    # Print decrypted password
    print(brute_force(salt, hashed_password))

    return 0


# Cycle through all permutations until a password matches the one inputed
def brute_force(salt, hashed_password):
    # This will be used as a letter in the alphabet array
    key_index = '0' * MAXSIZE
    key_index = list(key_index)
    key_index = [int(i) for i in key_index]

    key.append(alphabet[key_index[0]])

    # Loop until the password is found or MAXSIZE is exceeded
    while True:
        # Check if the password's been found
        if hashed_password == crypt.crypt(''.join(key), salt):
            return ''.join(key)

        # Proceed to next permutation
        key_index[0] += 1
        key[0] = alphabet[key_index[0]]

        # After getting through all letters, go back to first and raise the next one by one
        if key[0] == '.':
            key_index[0] = 0
            key[0] = alphabet[key_index[0]]
            advance_next_letter(1, key, key_index)


# Advances the next position when the previous has gone through all letters
def advance_next_letter(index, key, key_index):
    # If list isn't big enough append, else replace
    if index > len(key) - 1:
        key.append(alphabet[key_index[index]])
    else:
        key[index] = alphabet[key_index[index]]

    key_index[index] += 1

    # Recursively advance next position of key
    if key[index] == '.':
        key_index[index] = 0
        key[index] = alphabet[key_index[index]]
        # Ensure we don't go beyond maxsize
        if index == MAXSIZE - 1:
            print("could not find password")
            exit(1)
        advance_next_letter(index + 1, key, key_index)


if __name__ == "__main__":
    if not len(sys.argv) == 2:
        print("Usage: python crack.py hash")
        exit(1)
    exit(main(sys.argv[1]))