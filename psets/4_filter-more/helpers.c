#include "helpers.h"
#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%2d ", array[i]);
    }
    printf("\n");
}

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
void copyImage(int height, int width, RGBTRIPLE source[height][width], RGBTRIPLE destination[height][width])
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Copy pixel values from source to destination
            destination[y][x] = source[y][x];
        }
    }
}

// Offset
//
// Usage: 3x3 Box
// Scan each 3x3 Box, where center pixel is averaged with sum of surrounding pixel value.
//
// Offset offsets[] = {
//     { -1, -1 }, { 0, -1 }, { 1, -1 },
//     { -1, 0 }, /*{ 0, 0 },*/ { 1, 0 },
//     { -1, 1 }, { 0, 1 }, { 1, 1 }
// };
typedef struct {
    int dx;
    int dy;
} Offset;

/*
 * Blur image
 *
 * The new value of each pixel would be the average of the values of all
 * of the pixels that are within 1 row and column of the original pixel
 * (forming a 3x3 box). For a pixel along the edge or corner, we would
 * still look for all pixels within 1 row and column.
 */
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    Offset offsets[]
        = { { -1, -1 },
            { 0, -1 },
            { 1, -1 },
            { -1, 0 },
            // { 0, 0 },
            { 1, 0 },
            { -1, 1 },
            { 0, 1 },
            { 1, 1 } };
    size_t count_offsets = sizeof(offsets) / sizeof(Offset);
    assert(count_offsets == 8); // 8+1; if origin(`{ 0, 0 }`) is enabled in offsets[]

    RGBTRIPLE buffer_image[height][width];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGBTRIPLE* pixel = &image[y][x];
            int sum_red = pixel->rgbtRed, sum_green = pixel->rgbtGreen,
                sum_blue = pixel->rgbtBlue; // 0,0,0 if origin(`{ 0, 0 }`) is enabled in offsets[]
            int count_visited = 1; // 0 if origin(`{ 0, 0 }`) is enabled in offsets[]

            for (int i = 0; i < count_offsets; i++) {
                int idx_nx = x + offsets[i].dx, idx_ny = y + offsets[i].dy;

                if (!(idx_nx >= 0 && idx_nx < width && idx_ny >= 0 && idx_ny < height)) {
                    continue;
                }

                RGBTRIPLE rgbt = (image[idx_ny][idx_nx]);
                sum_red += rgbt.rgbtRed;
                sum_green += rgbt.rgbtGreen;
                sum_blue += rgbt.rgbtBlue;
                count_visited++;
            }

            RGBTRIPLE* buffer_pixel = &buffer_image[y][x];
            buffer_pixel->rgbtRed = round((float)sum_red / count_visited);
            buffer_pixel->rgbtGreen = round((float)sum_green / count_visited);
            buffer_pixel->rgbtBlue = round((float)sum_blue / count_visited);
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image[y][x] = buffer_image[y][x];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
    int Gy[3][3] = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };
    // Gradient Magnitude (G):
    // G = sqrt(Gx^2 + Gy^2)

    return;
}
/* Edges
In artificial intelligence algorithms for image processing, it is often useful to detect edges in an image: lines in the
image that create a boundary between one object and another. One way to achieve this effect is by applying the Sobel
operator to the image.

Like image blurring, edge detection also works by taking each pixel, and modifying it based on the 3x3 grid of pixels
that surrounds that pixel. But instead of just taking the average of the nine pixels, the Sobel operator computes the
new value of each pixel by taking a weighted sum of the values for the surrounding pixels. And since edges between
objects could take place in both a vertical and a horizontal direction, you’ll actually compute two weighted sums: one
for detecting edges in the x direction, and one for detecting edges in the y direction. In particular, you’ll use the
following two “kernels”:

Sobel kernels

How to interpret these kernels? In short, for each of the three color values for each pixel, we’ll compute two values Gx
and Gy. To compute Gx for the red channel value of a pixel, for instance, we’ll take the original red values for the
nine pixels that form a 3x3 box around the pixel, multiply them each by the corresponding value in the Gx kernel, and
take the sum of the resulting values.

Why these particular values for the kernel? In the Gx direction, for instance, we’re multiplying the pixels to the right
of the target pixel by a positive number, and multiplying the pixels to the left of the target pixel by a negative
number. When we take the sum, if the pixels on the right are a similar color to the pixels on the left, the result will
be close to 0 (the numbers cancel out). But if the pixels on the right are very different from the pixels on the left,
then the resulting value will be very positive or very negative, indicating a change in color that likely is the result
of a boundary between objects. And a similar argument holds true for calculating edges in the y direction.

Using these kernels, we can generate a Gx and Gy value for each of the red, green, and blue channels for a pixel. But
each channel can only take on one value, not two: so we need some way to combine Gx and Gy into a single value. The
Sobel filter algorithm combines Gx and Gy into a final value by calculating the square root of Gx^2 + Gy^2. And since
channel values can only take on integer values from 0 to 255, be sure the resulting value is rounded to the nearest
integer and capped at 255!

And what about handling pixels at the edge, or in the corner of the image? There are many ways to handle pixels at the
edge, but for the purposes of this problem, we’ll ask you to treat the image as if there was a 1 pixel solid black
border around the edge of the image: therefore, trying to access a pixel past the edge of the image should be treated as
a solid black pixel (values of 0 for each of red, green, and blue). This will effectively ignore those pixels from our
calculations of Gx and Gy.
*/
