#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Prompts the user to input their name
    string name = get_string("What's your name? ");

    //Greets the user according to their name
    printf("Hello, %s\n", name);
}