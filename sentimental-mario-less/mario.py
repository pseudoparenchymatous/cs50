# TODO
from cs50 import get_int

# Prompt user for the height of the pyramid (1 - 8 inclusive)
while (True):
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# Initialize spaces
spaces = height - 1
# Print every row
for high in range(height):
    # Print spaces and increment spaces every row
    for space in range(spaces):
        print(" ", end="")
    spaces -= 1
    # Print the blocks
    for length in range(high + 1):
        print("#", end="")
    print()