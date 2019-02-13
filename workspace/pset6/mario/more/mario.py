# Draws has pyramid with 2 space gap in the middle.

from cs50 import get_int

# Get height input from user
height = -1
while height < 0 or height > 23:
    height = get_int("Height: ")

# Print pyramid
# Iterate over rows
for i in range(height):

    # Iterate over left half-pyramid columns
    for j in range(height):
        # Print appropriate symbol
        print(" " if j < height - i - 1 else "#", end="")

    # Print gap
    print("  ", end="")

    # Iterate over right half-pyramid columns (only if they're hashes)
    for j in range(i + 1):
        print("#", end="")

    # Print newline to move to next row
    print()