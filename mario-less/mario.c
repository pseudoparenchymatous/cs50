#include <cs50.h>
#include <stdio.h>

//Prototypes of the functions
void print_spaces(int spaces);
void print_blocks(int blocks);

int main(void)
{
    //Prompts the user for the height of the pyramid
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    int spaces = height - 1;
    int blocks = 1;
    for (int i = 0; i < height; i++)
    {
        //Calls function to print spaces
        print_spaces(spaces);
        //Calls function to print blocks
        print_blocks(blocks);

        //Reduces spaces for the next line
        spaces--;
        //Adds more blocks for the next line
        blocks++;
        printf("\n");
    }
}

//Function prints a number of spaces according to the argument passed
void print_spaces(int spaces)
{
    for (int i = spaces; i > 0; i--)
    {
        printf(" ");
    }
}

//Function prints a number of blocks according to the argument passed
void print_blocks(int blocks)
{
    for (int i = 0; i < blocks; i++)
    {
        printf("#");
    }
}