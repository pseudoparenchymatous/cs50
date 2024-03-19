# TODO
from cs50 import get_int


def main():

    # Card details stored in a dictionary
    card = {}
    # Get the card number
    get_number(card)

    # Check the card length
    if valid(card):
        # Perform the algorithm
        test_card(card)
    # Invalid cards will fail the test
    else:
        print("INVALID")


def get_number(card):
    while (True):
        i = get_int("Number: ")
        if i >= 0:
            card["number"] = str(i)
            return


def valid(card):
    # Store card length into the dictionary
    card["length"] = len(card["number"])
    if card["length"] >= 13:
        return True
    else:
        return False


def test_card(card):
    # Store each digit of the card number into a list in the card dictionary
    card["digits"] = []
    for i in card["number"]:
        card["digits"] += i

    card["total"] = 0
    multp = False
    for i in reversed(card["digits"]):
        j = int(i)

        if multp == True:
            j = j * 2
            if j > 9:
                j = int(str(j)[0]) + int(str(j)[1])

            multp = False
        else:
            multp = True

        card["total"] += j

    # Check if the last digit of the total is a zero
    if card["total"] % 10 == 0:
        # Check the card length and its initial digits
        if card["length"] == 15:
            print("AMEX")
        elif card["length"] == 16:
            if card["number"][0] == "5" and (card["number"][1] >= "1" and card["number"][1] <= "5"):
                print("MASTERCARD")
            elif card["number"][0] == "4":
                print("VISA")
            else:
                print("INVALID")
        elif card["length"] == 13:
            if card["number"][0] == "4":
                print("VISA")
            else:
                print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
