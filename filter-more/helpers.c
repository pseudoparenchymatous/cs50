#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <cs50.h>

int isBeyond(int x);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Go to every pixel
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            BYTE *red = &image[row][col].rgbtRed;
            BYTE *green = &image[row][col].rgbtGreen;
            BYTE *blue = &image[row][col].rgbtBlue;

            // The shade of gray for the pixel is the average of its color values
            int gray = round((*red + *green + *blue) / 3.0);

            // Assign the pixel's color values to the shade of gray
            *red = gray;
            *green = gray;
            *blue = gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Reflection is swapping the right half and left half pixels of the image
    int half = width / 2;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0, right = width - 1; col < half; col++, right--)
        {
            // Swap the right half pixel to its left half equivalent
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][right];
            image[row][right] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            copy[row][col] = image[row][col];
        }
    }

    // Go to every pixel
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            float counter = 0.0;
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            // Go to every neighboring pixels
            for (int i = row - 1; i < row + 2; i++)
            {
                for (int j = col - 1; j < col + 2; j++)
                {
                    if (i >= 0 && i < height && j >= 0 && j < width)
                    {
                        // Get the sum of all the neighboring pixels
                        redSum += copy[i][j].rgbtRed;
                        greenSum += copy[i][j].rgbtGreen;
                        blueSum += copy[i][j].rgbtBlue;
                        counter++;
                    }
                }
            }

            // The average of the sum is the new value of the color values
            image[row][col].rgbtRed = round(redSum / counter);
            image[row][col].rgbtGreen = round(greenSum / counter);
            image[row][col].rgbtBlue = round(blueSum / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            copy[row][col] = image[row][col];
        }
    }

    // The current pixel and its neighbors will be multiplied by these values according to their position
    int kernelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Go to every pixel
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int redX = 0;
            int redY = 0;
            int greenX = 0;
            int greenY = 0;
            int blueX = 0;
            int blueY = 0;
            // Go to the neighboring pixels
            for (int i = 0, y = row - 1; i < 3; i++, y++)
            {
                for (int j = 0, x = col - 1; j < 3; j++, x++)
                {
                    bool beyond_edge = (y < 0 || y >= height || x < 0 || x >= width);
                    if (!beyond_edge)
                    {
                        // Multiply the color values of the current pixel to the kernel values
                        // Every product of the multiplication will be stored in a variable for later computing
                        redX += copy[y][x].rgbtRed * kernelX[i][j];
                        greenX += copy[y][x].rgbtGreen * kernelX[i][j];
                        blueX += copy[y][x].rgbtBlue * kernelX[i][j];

                        redY += copy[y][x].rgbtRed * kernelY[i][j];
                        greenY += copy[y][x].rgbtGreen * kernelY[i][j];
                        blueY += copy[y][x].rgbtBlue * kernelY[i][j];
                    }
                    // Do nothing if the current pixel is beyond the edge of the image
                }
            }
            // Get the square root of the sum of Gy squared and Gx squared and store as the final color
            int finalRed = round(sqrt(redX * redX + redY * redY));
            int finalGreen = round(sqrt(greenX * greenX + greenY * greenY));
            int finalBlue = round(sqrt(blueX * blueX + blueY * blueY));
            // If the final color value is not beyond the boundary assign it to the current pixel's value
            // Otherwise, cap it at 0 minimum or 255 maximum
            image[row][col].rgbtRed = isBeyond(finalRed);
            image[row][col].rgbtGreen = isBeyond(finalGreen);
            image[row][col].rgbtBlue = isBeyond(finalBlue);
        }
    }

    return;
}
int isBeyond(int x)
{
    if (x > 255)
    {
        return 255;
    }
    else if (x < 0)
    {
        return 0;
    }
    else
    {
        return x;
    }
}