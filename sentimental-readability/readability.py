# TODO
from cs50 import get_string


def main():

    # Text is stored in a dictionary with its letter, words, and sentences count
    # Text average letters and average sentences are also stored
    # Reading Index is the last value stored in the dictionary
    inputText = {}

    get_text(inputText)

    count_letters(inputText)
    count_words(inputText)
    count_sentences(inputText)

    averageLetters(inputText)
    averageSentences(inputText)

    readingIndex(inputText)

    print_readingLevel(inputText)


def get_text(dictionary):
    dictionary["text"] = get_string("Text: ")


def count_letters(text):
    text["letters"] = 0

    #
    for character in text["text"]:
        if (character >= "a" and character <= "z") or (character >= "A" and character <= "Z"):
            text["letters"] += 1


def count_words(text):
    text["words"] = 1

    for character in text["text"]:
        if character == " ":
            text["words"] += 1


def count_sentences(text):
    text["sentences"] = 0

    for character in text["text"]:
        if character == "." or character == "!" or character == "?":
            text["sentences"] += 1


def averageLetters(text):
    text["avg_letters"] = text["letters"] / float(text["words"]) * 100


def averageSentences(text):
    text["avg_sentences"] = text["sentences"] / float(text["words"]) * 100


def readingIndex(text):
    # Compute reading index with Coleman-Liau formula
    text["index"] = 0.0588 * text["avg_letters"] - 0.296 * text["avg_sentences"] - 15.8


def print_readingLevel(text):
    # Print reading level according to the index
    # Index below 1 is reading level before grade 1
    if text["index"] < 1:
        print("Before Grade 1")
    elif text["index"] > 15:
        print("Grade 16+")
    else:
        print(f"Grade {round(text['index'])}")


if __name__ == "__main__":
    main()