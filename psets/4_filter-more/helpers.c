#include "helpers.h"
#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
//
void print_array(int array[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%2d ", array[i]);
    }
    printf("\n");
}
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
// -1+1 +0+1 +1+1
// -1+0 +0+0 +1+0
// -1-1 +1+0 +1-1
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int offset_x[] = { -1, 0, 1, -1, 1, -1, 1, 1 };
    int offset_y[] = { 1, 1, 1, 0, 0, -1, -1, -1 };

    size_t count_offset = sizeof(offset_x) / sizeof(int);
    assert(count_offset == sizeof(offset_y) / sizeof(int));

    print_array(offset_x, count_offset);
    print_array(offset_y, count_offset);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGBTRIPLE* pixel = &image[y][x];
            int sum_red = pixel->rgbtRed, sum_green = pixel->rgbtGreen, sum_blue = pixel->rgbtBlue;

            for (int i = 0; i < count_offset; i++) {
                int idx_nx = x + offset_x[i];
                int idx_ny = y + offset_y[i];

                if (idx_nx >= 0 && idx_nx < width && idx_ny >= 0 && idx_ny < height) {
                    RGBTRIPLE rgbt = (image[idx_ny][idx_nx]);
                    sum_red += rgbt.rgbtRed;
                    sum_green += rgbt.rgbtGreen;
                    sum_blue += rgbt.rgbtBlue;
                }
            }

            int count_all = count_offset + 1; // +1 -> current pixel
            pixel->rgbtRed = sum_red / count_all;
            pixel->rgbtGreen = sum_green / count_all;
            pixel->rgbtBlue = sum_blue / count_all;
        }
    }

    return;
}

/* 11:35am zsh $ valgrind ./filter -b images/courtyard.bmp out/courtyard_blur.bmp
==458644== Memcheck, a memory error detector
==458644== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==458644== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==458644== Command: ./filter -b images/courtyard.bmp out/courtyard_blur.bmp
==458644==
-1  0  1 -1  1 -1  1  1
 1  1  1  0  0 -1 -1 -1
==458644==
==458644== HEAP SUMMARY:
==458644==     in use at exit: 0 bytes in 0 blocks
==458644==   total heap usage: 6 allocs, 6 frees, 730,160 bytes allocated
==458644==
==458644== All heap blocks were freed -- no leaks are possible
==458644==
==458644== For lists of detected and suppressed errors, rerun with: -s
==458644== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0) */

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
