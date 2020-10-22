#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each column of the pixel
    for (int i = 0; i < height; i++)
    {
        // Iterate through rows of the pixels
        for (int j = 0; j < width; j++)
        {
            // Extract each color value
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // Calculate the average
            int avg = round(((float)red + (float)green + (float)blue) / 3.00);

            // Assign average values to turn each pixel to grayscale
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int sepiaRed = round((.393 * (float)red) + (.769 * (float)green) + (.189 * (float)blue));
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }


            int sepiaGreen = round((.349 * (float)red) + (.686 * (float)green) + (.168 * (float)blue));
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }


            int sepiaBlue = round((.272 * (float)red) + (.534 * (float)green) + (.131 * (float)blue));
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Swapping last item with the first item.
    // need a temporary variable. imagine you have 2 drinks that you want to swap cups, you need a third cup.


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Create a temporary RGBTRIPLE type to store the first value in the 2D array
            RGBTRIPLE tmp = image[i][j];
            // Assign the first value to the last value in the array. remember zero index in the array
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tmp;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // We are going to need to make a copy to preserve all of the original values to calculate the averages
    RGBTRIPLE tmp[height][width]; // create a temporary 2D array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    // Iterate over all rows of image going down
    for (int i = 0; i < height; i++)
    {
        // Iterate over every item in the array going from left to right
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float counter = 0.0;

            // Iterate over rows items neighboring the current iterable within the current row
            for (int k = -1; k <= 1; k++)
            {
                // Iterate over columns around the iterable within current column
                for (int l = -1; l <= 1; l++)
                {
                    // If current row plus the next row are within bounds listed, then sum
                    // If current column plus next column are within bounds listed, then sum
                    if (i + k != height && i + k != -1 && j + l != width && j + l != -1)
                    {
                        // Then pull the tmp RGB values from temp and sum the RGB values
                        sumRed += tmp[i + k][j + l].rgbtRed;
                        sumGreen += tmp[i + k][j + l].rgbtGreen;
                        sumBlue += tmp[i + k][j + l].rgbtBlue;
                        // increment counter by one for one pixel in the sum
                        counter++;
                    }
                }
            }
            // Update and blur the original image RGB values
            image[i][j].rgbtRed = round(sumRed / counter);
            image[i][j].rgbtGreen = round(sumGreen / counter);
            image[i][j].rgbtBlue = round(sumBlue / counter);
        }
    }
    return;
}
