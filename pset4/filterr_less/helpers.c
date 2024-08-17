#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            int average =
                round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            int sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen +
                                 .189 * image[h][w].rgbtBlue);
            int sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen +
                                   .168 * image[h][w].rgbtBlue);
            int sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen +
                                  .131 * image[h][w].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            RGBTRIPLE temp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;

            float counter = 0;

            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (h + i < 0 || h + i >= height)
                    {
                        continue;
                    }
                    if (w + j < 0 || w + j >= width)
                    {
                        continue;
                    }
                    // Add to sum
                    sumRed += temp[h + i][w + j].rgbtRed;
                    sumGreen += temp[h + i][w + j].rgbtGreen;
                    sumBlue += temp[h + i][w + j].rgbtBlue;

                    counter++;
                }
            }

            // Add the blur effect to the original image
            image[h][w].rgbtRed = round(sumRed / counter);
            image[h][w].rgbtGreen = round(sumGreen / counter);
            image[h][w].rgbtBlue = round(sumBlue / counter);
        }
    }
}

