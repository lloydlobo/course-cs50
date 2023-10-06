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
            RGBTRIPLE px = image[y][x]; // typedef uint8_t BYTE;
            BYTE avg_rgb = (px.rgbtRed + px.rgbtGreen + px.rgbtBlue) / 3;

            image[y][x].rgbtRed = avg_rgb;
            image[y][x].rgbtGreen = avg_rgb;
            image[y][x].rgbtBlue = avg_rgb;
        }
    }
    return;
}

/* reverse:     reverse array `arr` in place */
void reverse(char *arr, int n_arr)
{
    int temp, i, j;
    for (i = 0, j = n_arr; i < j; i++, j--) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/* swap_pixels:    swap two RGBTRIPLE values */
void swap_pixels(RGBTRIPLE *px1, RGBTRIPLE *px2)
{
    RGBTRIPLE temp = *px1;
    *px1 = *px2;
    *px2 = temp;
}

/* swap_row_pixels:      Function to swap left and right pixels in a row for
 * reflection */
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

/**
 * Copy pixel values from source to destination
 */
void copyImage(
    int height,
    int width,
    RGBTRIPLE source[height][width],
    RGBTRIPLE destination[height][width])
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            destination[y][x] = source[y][x];
        }
    }
}

/**
 * Usage: 3x3 Box
 * Scan each 3x3 Box, where center pixel is averaged with sum of surrounding
 * pixel value. Offset offsets[] = { { -1, -1 }, { 0, -1 }, { 1, -1 }, { -1, 0
 * }, /\*{ 0, 0 },*\/ { 1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } };
 */
typedef struct {
    int dx;
    int dy;
} Offset;

/**
 * Blur image
 * The new value of each pixel would be the average of the values of all
 * of the pixels that are within 1 row and column of the original pixel
 * (forming a 3x3 box). For a pixel along the edge or corner, we would
 * still look for all pixels within 1 row and column.
 */
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    Offset offsets[8] = /* clang-format off */ {
        { -1, -1 }, {  0, -1 }, {  1, -1 },
        { -1,  0 },/*{ 0, 0},*/ {  1,  0 },
        { -1,  1 }, {  0,  1 }, {  1,  1 } }; /* clang-format on */
    size_t count_offsets = sizeof(offsets) / sizeof(Offset);
    assert(
        count_offsets
        == 8); // 8+1; if origin(`{ 0, 0 }`) is enabled in offsets[]
    RGBTRIPLE buffer_image[height][width];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGBTRIPLE *pixel = &image[y][x]; // 0,0,0 if origin(`{ 0, 0 }`) is
                                             // enabled in offsets[]
            int sum_red = pixel->rgbtRed, sum_green = pixel->rgbtGreen,
                sum_blue = pixel->rgbtBlue;
            int count_visited
                = 1; // 0 if origin(`{ 0, 0 }`) is enabled in offsets[]
            for (int i = 0; i < count_offsets; i++) {
                int idx_nx = x + offsets[i].dx, idx_ny = y + offsets[i].dy;
                if (!(idx_nx >= 0 && idx_nx < width && idx_ny >= 0
                      && idx_ny < height))
                    continue;
                RGBTRIPLE rgbt = (image[idx_ny][idx_nx]);
                sum_red += rgbt.rgbtRed;
                sum_green += rgbt.rgbtGreen;
                sum_blue += rgbt.rgbtBlue;
                count_visited++;
            }
            RGBTRIPLE *buffer_pixel = &buffer_image[y][x];
            buffer_pixel->rgbtRed = round((float)sum_red / count_visited);
            buffer_pixel->rgbtGreen = round((float)sum_green / count_visited);
            buffer_pixel->rgbtBlue = round((float)sum_blue / count_visited);
        }
    }
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            image[y][x] = buffer_image[y][x];

    return;
}

/**
 * Mutate current pixel basedt on 3x3 neighbourhood around the current pixel.
 */
void apply_sobel_gradient_magnitude(
    int x,
    int y,
    const int width,
    const int height,
    RGBTRIPLE image[height][width])
{
    const int kern_gx[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
    const int kern_gy[3][3] = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };
    const double MAX_RGB = 255.0;
    const RGBTRIPLE RGBTRIPLE_BLACK = {
        .rgbtRed = 0x00, .rgbtBlue = 0x00, .rgbtGreen = 0x00
    }; // Black: 0x00 or 0x000000, White: 0xFF
    int gxr = 0, gyr = 0;
    int gxg = 0, gyg = 0;
    int gxb = 0, gyb = 0;

    for (int row = -1; row <= 1; row++) {
        for (int col = -1; col <= 1; col++) {
            int nx = x + row, ny = y + col;
            /* if border or corner, color it black and skip this iteration */
            if (!(nx >= 0 && nx < width && ny >= 0 && ny < height)) {
                image[y][x] = RGBTRIPLE_BLACK;
                continue;
            }
            RGBTRIPLE npix = image[ny][nx];
            gxr += npix.rgbtRed * kern_gx[col + 1][row + 1];
            gyr += npix.rgbtRed * kern_gy[col + 1][row + 1];
            gxg += npix.rgbtGreen * kern_gx[col + 1][row + 1];
            gyg += npix.rgbtGreen * kern_gy[col + 1][row + 1];
            gxb += npix.rgbtBlue * kern_gx[col + 1][row + 1];
            gyb += npix.rgbtBlue * kern_gy[col + 1][row + 1];
        }
    }
    double grad_g = sqrt((double)(gxg * gxg + gyg * gyg));
    double grad_r = sqrt((double)(gxr * gxr + gyr * gyr));
    double grad_b = sqrt((double)(gxb * gxb + gyb * gyb));
    image[y][x].rgbtRed = (int)(MAX_RGB - fmin(MAX_RGB, round(grad_g)));
    image[y][x].rgbtGreen = (int)(MAX_RGB - fmin(MAX_RGB, round(grad_r)));
    image[y][x].rgbtBlue = (int)(MAX_RGB - fmin(MAX_RGB, round(grad_b)));
}

/**
 * Detect edges
 */
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // blur(height, width, image);
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            apply_sobel_gradient_magnitude(x, y, width, height, image);

    return;
}
