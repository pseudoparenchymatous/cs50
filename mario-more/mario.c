#include <cs50.h>
#include <stdio.h>

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
        //Prints the spaces for left pyramid
        print_spaces(spaces);
        //Prints the blocks for left pyramid
        print_blocks(blocks);

        printf("  "); //Prints the space between the pyramids

        //Prints the spaces for right pyramid
        print_blocks(blocks);

        spaces--;
        blocks++;
        printf("\n");
    }
}

void print_spaces(int spaces)
{
    for (int i = spaces; i > 0; i--)
    {
        printf(" ");
    }
}

void print_blocks(int blocks)
{
    for (int i = 0; i < blocks; i++)
    {
        printf("#");
    }
}