#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Print error if more than or less than one command-line argument
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // Store the filename from the command-line argument in a variable
    string raw_filename = argv[1];
    // Open the file
    FILE *raw_file = fopen(raw_filename, "r");
    // Print error and terminate program if cannot open file
    if (raw_file == NULL)
    {
        printf("Cannot open raw file %s.\n", raw_filename);
        return 1;
    }
    char jpeg_filename[8];
    int file_count = 0;
    // Prepare variable FILE to store a jpeg file later
    FILE *jpeg_file = NULL;

    // Allocate memory for the 512B-sized block to be read and store
    BYTE *block = malloc(sizeof(BYTE) * BLOCK_SIZE);
    // Keep looping until the end of file (i.e. no more blocks to read)
    while (fread(block, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // Check the first four bytes in the block
        bool first_byte = (block[0] == 0xff);
        bool second_byte = (block[1] == 0xd8);
        bool third_byte = (block[2] == 0xff);
        bool fourth_byte = block[3] >= 0xe0 && block[3] <= 0xef;
        if (first_byte && second_byte && third_byte && fourth_byte)
        {
            // Close current file opened before creating a new one
            if (jpeg_file)
            {
                fclose(jpeg_file);
            }
            // Create filename for the jpeg and store in a variable
            sprintf(jpeg_filename, "%03i.jpg", file_count);
            // Increment file count for the next file to save
            file_count++;
            // Create the actual file from the filename
            jpeg_file = fopen(jpeg_filename, "w");
            // Print error and terminate program if cannot create file
            if (jpeg_file == NULL)
            {
                printf("Cannot create a file\n");
                // Close the raw file and free allocated memory before terminating program
                free(block);
                fclose(raw_file);
                return 1;
            }
        }
        // Write to current opened jpeg file
        if (jpeg_file)
        {
            fwrite(block, sizeof(BYTE), BLOCK_SIZE, jpeg_file);
        }
    }
    // Free the allocated memory
    free(block);
    // Close the files
    fclose(raw_file);
    fclose(jpeg_file);

    return 0;
}