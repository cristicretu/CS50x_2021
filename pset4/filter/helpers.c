#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // Take the average from BGR
            BYTE average;
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.000);

            // Adding the average to the 2D array
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0, new_width = width / 2; j < new_width; ++j)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Directions vectors
    const int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

    // Make a temp RGBTRIPLE pixel
    RGBTRIPLE temp[height][width];

    int BLUE;
    int GREEN;
    int RED;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {

            // Initial value is the center value
            BLUE = image[i][j].rgbtBlue;
            GREEN = image[i][j].rgbtGreen;
            RED = image[i][j].rgbtRed;


            // Go through each neighbor
            float good_neighbors = 1;
            for (int k = 0; k < 8; ++k)
            {
                int ni = i + dx[k];
                int nj = j + dy[k];

                // Check for in-bounds
                if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                {
                    good_neighbors++;
                    BLUE += image[ni][nj].rgbtBlue;
                    GREEN += image[ni][nj].rgbtGreen;
                    RED += image[ni][nj].rgbtRed;
                }
            }

            // Assign the value to the temp RGBTRIPLE
            temp[i][j].rgbtBlue = round(BLUE / good_neighbors);
            temp[i][j].rgbtGreen = round(GREEN / good_neighbors);
            temp[i][j].rgbtRed = round(RED / good_neighbors);
        }
    }

    // Give the temp value to the original RGBTRIPLE
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Directions vectors
    const int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    
    // Comutational matrix
    const int Gx[8] = {-1, 0, 1, 2, 1, 0, -1, -2};
    const int Gy[8] = {-1, -2, -1, 0, 1, 2, 1, 0};

    // Make a temp RGBTRIPLE pixel
    RGBTRIPLE temp[height][width];

    int BLUE, BLUE_GX, BLUE_GY;
    int GREEN, GREEN_GX, GREEN_GY;
    int RED, RED_GX, RED_GY;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {

            // Initial value is the center value
            BLUE_GX = 0, BLUE_GY = 0;
            GREEN_GX = 0, GREEN_GY = 0;
            RED_GX = 0, RED_GY = 0;


            // Go through each neighbor
            for (int k = 0; k < 8; ++k)
            {
                int ni = i + dx[k];
                int nj = j + dy[k];

                // Check for in-bounds
                if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                {
                    BLUE_GX += Gx[k] * image[ni][nj].rgbtBlue;
                    BLUE_GY += Gy[k] * image[ni][nj].rgbtBlue;
                    
                    GREEN_GX += Gx[k] * image[ni][nj].rgbtGreen;
                    GREEN_GY += Gy[k] * image[ni][nj].rgbtGreen;
                    
                    RED_GX += Gx[k] * image[ni][nj].rgbtRed;
                    RED_GY += Gy[k] * image[ni][nj].rgbtRed;
                }
            }

            BLUE = round(sqrt(BLUE_GX * BLUE_GX + BLUE_GY * BLUE_GY));
            GREEN = round(sqrt(GREEN_GX * GREEN_GX + GREEN_GY * GREEN_GY));
            RED = round(sqrt(RED_GX * RED_GX + RED_GY * RED_GY));

            if (BLUE > 255)
            {
                BLUE = 255;
            }
            if (GREEN > 255)
            {
                GREEN = 255;
            }
            if (RED > 255)
            {
                RED = 255;
            }

            // Assign the value to the temp RGBTRIPLE
            temp[i][j].rgbtBlue = BLUE;
            temp[i][j].rgbtGreen = GREEN;
            temp[i][j].rgbtRed = RED;
        }
    }

    // Give the temp value to the original RGBTRIPLE
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

