#include "helpers.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // typedef uint8_t BYTE;
            BYTE avg_rgb = (image[y][x].rgbtRed + image[y][x].rgbtGreen + image[y][x].rgbtBlue) / 3;

            // Assign the average value to all components
            image[y][x].rgbtRed = avg_rgb;
            image[y][x].rgbtGreen = avg_rgb;
            image[y][x].rgbtBlue = avg_rgb;
        }
    }
    return;
}

/* reverse:     reverse array `arr` in place */
void reverse(char* arr, int n_arr)
{
    int temp, i, j;
    for (i = 0, j = n_arr; i < j; i++, j--) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/* swap_pixels:    swap two RGBTRIPLE values */
void swap_pixels(RGBTRIPLE* px1, RGBTRIPLE* px2)
{
    RGBTRIPLE temp = *px1;
    *px1 = *px2;
    *px2 = temp;
}

/* swap_row_pixels:      Function to swap left and right pixels in a row for reflection */
void swap_row_pixels(RGBTRIPLE row[], int width)
{
    for (int x = 0; x < width / 2; x++) {
        RGBTRIPLE temp = row[x];
        row[x] = row[width - x - 1];
        row[width - x - 1] = temp;
    }
}

// Reflect image horizontally as mirror image
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++) {
        // >> most declarative, bug prone.
        swap_row_pixels(image[y], width);

        // OR >> for utility abstraction
        // for (int x = 0; x < width / 2; x++) {
        //     swap_pixels(&image[y][x], &image[y][width - x - 1]);
        //
        //     // OR >> most readable
        //     // RGBTRIPLE temp = image[y][x];
        //     // image[y][x] = image[y][width - x - 1];
        //     // image[y][width - x - 1] = temp;
        // }
    }
}

// Blur image
/*
There are a number of ways to create the effect of blurring or softening an image. For this problem, we’ll use the “box
blur,” which works by taking each pixel and, for each color value, giving it a new value by averaging the color values
of neighboring pixels.

01 02 03 04
05 06 07 08
09 10 11 12
13 14 15 16

Scan each 3x3 Box, where center pixel is averaged with sum of surrounding pixel value.
TODO: Create a temp buffer to collect values, before mutating image?

BYTE x = image[y][x]
if not edge_pixel(x,y):
    x += image[y-2][x+1]
    x += image[y-1][x-1]
    x += image[y+1][x+1]
    x += image[y+1][x-1]
    x += image[y][x+1]
    x += image[y][x-1]
    x /= 8 // Average
else:
    todo()

The new value of each pixel would be the average of the values of all of the pixels that are within 1 row and column of
the original pixel (forming a 3x3 box). For example, each of the color values for pixel 6 would be obtained by averaging
the original color values of pixels 1, 2, 3, 5, 6, 7, 9, 10, and 11 (note that pixel 6 itself is included in the
average). Likewise, the color values for pixel 11 would be be obtained by averaging the color values of pixels 6, 7, 8,
10, 11, 12, 14, 15 and 16.

For a pixel along the edge or corner, like pixel 15, we would still look for all pixels within 1 row and column: in this
case, pixels 10, 11, 12, 14, 15, and 16. */
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // typedef uint8_t BYTE;
            BYTE avg_rgb = (image[y][x].rgbtRed + image[y][x].rgbtGreen + image[y][x].rgbtBlue) / 3;

            // Assign the average value to all components
            image[y][x].rgbtRed = avg_rgb;
            image[y][x].rgbtGreen = avg_rgb;
            image[y][x].rgbtBlue = avg_rgb;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
