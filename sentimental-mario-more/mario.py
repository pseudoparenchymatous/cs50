# TODO
from cs50 import get_int

# Prompt user for the height of the pyramids (1 - 8 inclusive only)
while(True):
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# Initialize the spaces before a block is printed
spaces = height - 1

# Go through every row of the pyramids
for row in range(height):
    # Print the appropriate spaces and decrement for the next row
    for space in range(spaces):
        print(" ", end="")
    spaces -= 1
    # Print the blocks for the first pyramid
    for i in range(row + 1):
        print("#", end="")
    # Print the two spaces between the pyramids
    print("  ", end="")
    # Print the second pyramid
    for i in range(row + 1):
        print("#", end="")
    # Print a new line
    print()