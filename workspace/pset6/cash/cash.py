# Greedy algorithm

from cs50 import get_float


# Get change input
change = -1
while change < 0:
    change = get_float("Change owed: ")

# Convert change to cents
change *= 100
change = round(change)

# Set minimum number of coins
min_coins = 0

# Determine how many coins of each coin_type we'll use starting from biggest
coin_types = [25, 10, 5, 1]
for coin_value in coin_types:
    while change >= coin_value:
        change -= coin_value
        min_coins += 1

print(f"{min_coins}")