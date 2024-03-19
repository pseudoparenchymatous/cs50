# TODO
from cs50 import get_float


def main():

    # Get owed dollars
    dollars = get_dollars()

    # Compute how much quarters to give
    quarters = get_quarters(dollars)
    dollars = dollars - quarters * 25

    # Compute how much dimes to give
    dimes = get_dimes(dollars)
    dollars = dollars - dimes * 10

    # Compute how much nickels to give
    nickels = get_nickels(dollars)
    dollars = dollars - nickels * 5

    # Compute how much pennies to give
    pennies = get_pennies(dollars)
    dollars = dollars - pennies * 1

    # Add all coins
    coins = quarters + dimes + nickels + pennies

    print(f"{coins}")


def get_dollars():
    while (True):
        x = get_float("Change owed: ")
        if x >= 0:
            return int(x * 100)


def get_quarters(dollars):
    return int(dollars / 25)


def get_dimes(dollars):
    return int(dollars / 10)


def get_nickels(dollars):
    return int(dollars / 5)


def get_pennies(dollars):
    return int(dollars / 1)


main()
