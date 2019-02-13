# Draws hash steps from left to right. Last step is double as wide as others

from cs50 import get_int

# Gets height by user
height = -1
while height < 0 or height > 23:
    height = get_int("Height: ")

# Prints half pyramid
# Iterate rows
for i in range(height):
    # Iterate collumns
    for j in range(height + 1):
        print(" " if j < height - 1 - i else "#", end="")
    print()