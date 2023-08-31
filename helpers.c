#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
   for(int i = 0; i < height; i++)
   {
        for(int j = 0; j < width; j++)
        {
            float total = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            int average = (round)(total / 3);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
   }

}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
   {
        for(int j = 0; j < width; j++)
        {
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = (round)(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = (round)(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = (round)(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
             if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
             if(sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

                image[i][j].rgbtRed = sepiaRed;
                image[i][j].rgbtGreen = sepiaGreen;
                image[i][j].rgbtBlue = sepiaBlue;
        }
   }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
   {
        for(int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
   }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
     RGBTRIPLE temp[height][width];
     for(int i = 0; i < height; i++)
     {
        for(int j = 0; j < width; j++)
        {
            float totalRed, totalGreen, totalBlue;
            totalRed = totalGreen = totalBlue = 0;
            float counter = 0.00;

            for(int x = -1; x < 2; x++)
            {
               for(int y = -1; y < 2; y++)
               {
                    int nbrX = i + x;
                    int nbrY = j + y;

                    if(nbrX < 0 || nbrX > (height - 1) || nbrY < 0 || nbrY > (width -1))
                    {
                        continue;
                    }

                    totalRed += image[nbrX][nbrY].rgbtRed;
                    totalGreen += image[nbrX][nbrY].rgbtGreen;
                    totalBlue += image[nbrX][nbrY].rgbtBlue;

                    counter++;
               }

               temp[i][j].rgbtRed = round(totalRed / counter);
               temp[i][j].rgbtGreen = round(totalGreen / counter);
               temp[i][j].rgbtBlue = round(totalBlue / counter);

            }
        }
     }

     for (int i = 0; i < height; i++)
     {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
     }
}
