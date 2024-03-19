#include "helpers.h"
#include <math.h>

// Prototypes of my own functions
void swap(RGBTRIPLE *x, RGBTRIPLE *y);
void check_sepia(int *x);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Go to evey pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE *red = &image[i][j].rgbtRed;
            BYTE *green = &image[i][j].rgbtGreen;
            BYTE *blue = &image[i][j].rgbtBlue;

            // Sum the ammount of red, green and blue of the pixel
            int sum = *red + *green + *blue;
            // Divide the sum by 3 to get the average and round to the nearest integer
            int gray = round((sum / 3.0));

            // Assign the average to values of red, green and blue
            *red = gray;
            *green = gray;
            *blue = gray;
        }
    }
}

// Convert image to sepia
// sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
// sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
// sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Go to every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE *originalRed = &image[i][j].rgbtRed;
            BYTE *originalGreen = &image[i][j].rgbtGreen;
            BYTE *originalBlue = &image[i][j].rgbtBlue;

            // Do the sepia formula for red, green and blue
            int sepiaRed = round(0.393 * (*originalRed) + 0.769 * (*originalGreen) + 0.189 * (*originalBlue));
            int sepiaGreen = round(0.349 * (*originalRed) + 0.686 * (*originalGreen) + 0.168 * (*originalBlue));
            int sepiaBlue = round(0.272 * (*originalRed) + 0.534 * (*originalGreen) + 0.131 * (*originalBlue));

            // Check if the number is within the bounds of 0 and 255 inclusive
            check_sepia(&sepiaRed);
            check_sepia(&sepiaGreen);
            check_sepia(&sepiaBlue);

            // Assign the original values to the new sepia values
            *originalRed = sepiaRed;
            *originalGreen = sepiaGreen;
            *originalBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Get half the pixel of the image
    int half = width / 2;
    for (int i = 0; i < height; i++)
    {
        // Go to every pixel of the left half of the image and swap them to the right half
        for (int j = 0, k = width - 1; j < half; j++, k--)
        {
            swap(&image[i][j], &image[i][k]);
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make copy of the image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Go to every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float n = 0.0;
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            // Sum the colors values of the neighboring pixels of the current pixel
            for (int ii = i - 1; ii < i + 2; ii++)
            {
                for (int jj = j - 1; jj < j + 2; jj++)
                {
                    if (ii >= 0 && ii < height && jj >= 0 && jj < width)
                    {
                        redSum += copy[ii][jj].rgbtRed;
                        greenSum += copy[ii][jj].rgbtGreen;
                        blueSum += copy[ii][jj].rgbtBlue;
                        n++;
                    }
                }
            }

            // Get the average of the sums
            redSum = round(redSum / n);
            greenSum = round(greenSum / n);
            blueSum = round(blueSum / n);

            // Assign the averages to the current pixel
            image[i][j].rgbtRed = redSum;
            image[i][j].rgbtGreen = greenSum;
            image[i][j].rgbtBlue = blueSum;
        }
    }
}

void swap(RGBTRIPLE *x, RGBTRIPLE *y)
{
    RGBTRIPLE temp = *x;
    *x = *y;
    *y = temp;
}

void check_sepia(int *x)
{
    if (*x >= 255)
    {
        *x = 255;
    }
    else if (*x <= 0)
    {
        *x = 0;
    }
}