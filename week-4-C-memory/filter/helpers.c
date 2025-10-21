#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			 // weighted avarage that account for human eye sensitivity:
			 int mean = round(0.299 * image[i][j].rgbtRed + 0.587 * image[i][j].rgbtGreen + 0.114 * image[i][j].rgbtBlue);
			 image[i][j].rgbtBlue = mean;
			 image[i][j].rgbtGreen = mean;
			 image[i][j].rgbtRed = mean;
		}
	}
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width / 2; j++)
		{
			RGBTRIPLE tmp = image[i][j];
			image[i][j] = image[i][width -1 -j];
			image[i][width - 1 - j] = tmp;
		}
	}
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE tmp[height][width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int redSum = 0; int greenSum = 0; int blueSum = 0;
			int count = 0; 
			for (int di = -1; di <= 1; di++)
			{
				for (int dj = -1; dj <= 1; dj++)
				{
					int ni = i + di; 
					int nj = j + dj;

					if (ni >= 0 && ni < height && nj >= 0 && nj < width)
					{
					    redSum += image[ni][nj].rgbtRed;
                        greenSum += image[ni][nj].rgbtGreen;
                        blueSum += image[ni][nj].rgbtBlue;
                        count++;	
					}
				}
			}
			tmp[i][j].rgbtBlue = round(blueSum / (float)count);
			tmp[i][j].rgbtGreen = round(greenSum / (float)count);
			tmp[i][j].rgbtRed = round(redSum / (float)count);
		}
	}
	for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE tmp[height][width];
	int Gx[3][3] = {
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1}
	};
	int Gy[3][3] = {
		{-1, -2, -1},
		{ 0,  0,  0},
		{ 1,  2,  1}
	};
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int red; int green; int blue;
			int redGx = 0; int greenGx = 0; int blueGx = 0;
			int redGy = 0; int greenGy = 0; int blueGy = 0;
			for (int di = -1; di <= 1; di++)
			{
				for (int dj = -1; dj <= 1; dj++)
				{
					int ni = i + di; 
					int nj = j + dj;

					if (ni >= 0 && ni < height && nj >= 0 && nj < width)
					{
					    redGx += image[ni][nj].rgbtRed * Gx[di+1][dj+1];
                        greenGx += image[ni][nj].rgbtGreen * Gx[di+1][dj+1];
                        blueGx += image[ni][nj].rgbtBlue * Gx[di+1][dj+1];

						redGy += image[ni][nj].rgbtRed * Gy[di+1][dj+1];
                        greenGy += image[ni][nj].rgbtGreen * Gy[di+1][dj+1];
                        blueGy += image[ni][nj].rgbtBlue * Gy[di+1][dj+1];
					}
				}
			}
			red = round(sqrt(pow(redGx, 2) + pow(redGy, 2)));
			green = round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)));
			blue = round(sqrt(pow(blueGx, 2) + pow(blueGy, 2)));

			// Clamp values to 0-255 range
			tmp[i][j].rgbtRed = (red > 255) ? 255 : red;
			tmp[i][j].rgbtGreen = (green > 255) ? 255 : green;
			tmp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
		}
	}
	for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }	
    return;
}
