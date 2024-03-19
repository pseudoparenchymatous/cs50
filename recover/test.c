#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
typedef char* string;

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    string file_name = argv[1];
    FILE *raw_file = fopen(file_name, "r");
    if (raw_file == NULL)
    {
        printf("ERROR\n");
        return 1;
    }
    BYTE *block = malloc(sizeof(BYTE) * BLOCK_SIZE);
    unsigned jpeg_counter = 0;
    while (fread(block, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        bool first_byte = (block[0] == 0xff);
        bool second_byte = (block[1] == 0xd8);
        bool third_byte = (block[2] == 0xff);
        bool fourth_byte = block[3] >= 0xe0 && block[3] <= 0xef;
        if (first_byte && second_byte && third_byte && fourth_byte)
            jpeg_counter++;
    }
    printf("There are %i jpegs in the raw file\n", jpeg_counter);

    // for (int i = 0; i < BIG; i++)
    // {
    //     if (buffer[i] == 0xff)
    //     {
    //         printf("YES\n");
    //     }
    //     else
    //     {
    //         printf("NO\n");
    //     }
    // }
    free(block);
    fclose(raw_file);
}
