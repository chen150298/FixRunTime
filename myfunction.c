// Chen Larry

#include <stdlib.h>

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;

#define calcPlace(i, j, m)  (((i) * (m)) + (j))
#define min(X, Y)           ((X) < (Y) ? (X) : (Y))
#define max(X, Y)           ((X) > (Y) ? (X) : (Y))
#define multBy9(X)          (((X) << 3) + (X))
#define multByMinus1(X)     ((X)*(-1))
#define divideBy9(X)        ((X)/9)
#define divideBy7(X)        ((X)/7)

/** some optimizations i used:
 * 1. used memcpy instead of copy pixels
 * 2. find the 9 pixels around in O(1)
 * 3. access to 2 pixels at a time
 * 4. use 1 loop for all functions
 */

inline void blur(Image *image) {
    // pixels array
    int size = m * n * sizeof(pixel);
    pixel *pixels = malloc(size);
    // image data
    pixel *image_data = (pixel *) image->data;
    // copy image_data to pixels
    memcpy(pixels, image_data, size);

    int i, j, temp = 0, red, green, blue;
    pixel current_pixel;
    int m_minus_1 = m - 1, n_minus_1 = n - 1, n_minus_2 = n - 2;
    pixel *pixel1 ,*pixel2, *pixel3, *pixel4, *pixel5, *pixel6, *pixel7, *pixel8, *pixel9;

    // check if image size is even, if yes- access 2 pixels at a time.
    if (m % 2 == 0) {
        // columns
        for (i = 1; i < m_minus_1; ++i) {
            // find 9 addresses pixels around
            pixel1 = &pixels[temp];
            pixel2 = pixel1 + 1;
            pixel3 = pixel2 + 1;
            pixel4 = pixel1 + n;
            pixel5 = pixel4 + 1;
            pixel6 = pixel5 + 1;
            pixel7 = pixel4 + n;
            pixel8 = pixel7 + 1;
            pixel9 = pixel8 + 1;
            // rows
            for (j = 1; j < n_minus_2; j += 2) {

                /** first pixel */

                // sum all 9 pixels
                red = pixel1->red + pixel2->red + pixel3->red + pixel4->red + pixel5->red +
                      pixel6->red + pixel7->red + pixel8->red + pixel9->red;
                green = pixel1->green + pixel2->green + pixel3->green + pixel4->green + pixel5->green +
                        pixel6->green + pixel7->green + pixel8->green + pixel9->green;
                blue = pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue + pixel5->blue +
                       pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue;

                // assign_sum_to_pixel function

                // divide by kernel's weight
                red = divideBy9(red);
                green = divideBy9(green);
                blue = divideBy9(blue);
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(blue, 0), 255));

                image_data[calcPlace(i, j, m)] = current_pixel;

                // next pixels
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;

                /** second pixel */

                // sum all 9 pixels
                red = pixel1->red + pixel2->red + pixel3->red + pixel4->red + pixel5->red +
                      pixel6->red + pixel7->red + pixel8->red + pixel9->red;
                green = pixel1->green + pixel2->green + pixel3->green + pixel4->green + pixel5->green +
                        pixel6->green + pixel7->green + pixel8->green + pixel9->green;
                blue = pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue + pixel5->blue +
                       pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue;

                // assign_sum_to_pixel function

                // divide by kernel's weight
                red = divideBy9(red);
                green = divideBy9(green);
                blue = divideBy9(blue);
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(blue, 0), 255));

                image_data[calcPlace(i, j + 1, m)] = current_pixel;

                // next pixels
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;
            }
            temp += n;
        }
    } else {
        // columns
        for (i = 1; i < m_minus_1; ++i) {
            // find 9 addresses pixels around
            pixel1 = &pixels[temp];
            pixel2 = pixel1 + 1;
            pixel3 = pixel2 + 1;
            pixel4 = pixel1 + n;
            pixel5 = pixel4 + 1;
            pixel6 = pixel5 + 1;
            pixel7 = pixel4 + n;
            pixel8 = pixel7 + 1;
            pixel9 = pixel8 + 1;
            // rows
            for (j = 1; j < n_minus_1; ++j) {

                // sum all 9 pixels
                red = pixel1->red + pixel2->red + pixel3->red + pixel4->red + pixel5->red +
                      pixel6->red + pixel7->red + pixel8->red + pixel9->red;
                green = pixel1->green + pixel2->green + pixel3->green + pixel4->green + pixel5->green +
                        pixel6->green + pixel7->green + pixel8->green + pixel9->green;
                blue = pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue + pixel5->blue +
                       pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue;

                // assign_sum_to_pixel function

                // divide by kernel's weight
                red = divideBy9(red);
                green = divideBy9(green);
                blue = divideBy9(blue);
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(blue, 0), 255));

                image_data[calcPlace(i, j, m)] = current_pixel;

                // next pixels
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;
            }
            temp += n;
        }
    }
    free(pixels);
}

inline void sharpen(Image *image) {
    // pixels array
    int size = m * n * sizeof(pixel);
    pixel *pixels = malloc(size);
    // image data
    pixel *image_data = (pixel *) image->data;
    // copy image_data to pixels
    memcpy(pixels, image_data, size);

    int i, j, temp = 0, red, green, blue;
    pixel current_pixel;
    int m_minus_1 = m - 1, n_minus_1 = n - 1, n_minus_2 = n - 2;
    pixel *pixel1 ,*pixel2, *pixel3, *pixel4, *pixel5, *pixel6, *pixel7, *pixel8, *pixel9;

    if (m % 2 == 0) {
        // columns
        for (i = 1; i < m_minus_1; ++i) {
            // find 9 addresses pixels around
            pixel1 = &pixels[temp];
            pixel2 = pixel1 + 1;
            pixel3 = pixel2 + 1;
            pixel4 = pixel1 + n;
            pixel5 = pixel4 + 1;
            pixel6 = pixel5 + 1;
            pixel7 = pixel4 + n;
            pixel8 = pixel7 + 1;
            pixel9 = pixel8 + 1;
            // rows
            for (j = 1; j < n_minus_2; j += 2) {

                /** first pixel*/

                // sum all 9 pixels as sharp kernel
                red = multBy9(pixel5->red) + multByMinus1(pixel1->red + pixel2->red + pixel3->red + pixel4->red +
                                                          pixel6->red + pixel7->red + pixel8->red + pixel9->red);
                green = multBy9(pixel5->green) +
                        multByMinus1(pixel1->green + pixel2->green + pixel3->green + pixel4->green +
                                     pixel6->green + pixel7->green + pixel8->green + pixel9->green);
                blue = multBy9(pixel5->blue) + multByMinus1(pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue +
                                                            pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue);

                // assign_sum_to_pixel function

                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(blue, 0), 255));

                image_data[calcPlace(i, j, m)] = current_pixel;

                // next pixels
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;

                /** second pixel*/

                // sum all 9 pixels as sharp kernel
                red = multBy9(pixel5->red) + multByMinus1(pixel1->red + pixel2->red + pixel3->red + pixel4->red +
                                                          pixel6->red + pixel7->red + pixel8->red + pixel9->red);
                green = multBy9(pixel5->green) +
                        multByMinus1(pixel1->green + pixel2->green + pixel3->green + pixel4->green +
                                     pixel6->green + pixel7->green + pixel8->green + pixel9->green);
                blue = multBy9(pixel5->blue) + multByMinus1(pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue +
                                                            pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue);

                // assign_sum_to_pixel function

                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(blue, 0), 255));

                image_data[calcPlace(i, j + 1, m)] = current_pixel;

                // next pixels
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;
            }
            temp += n;
        }

    } else {
        // columns
        for (i = 1; i < m_minus_1; ++i) {
            // find 9 addresses pixels around
            pixel1 = &pixels[temp];
            pixel2 = pixel1 + 1;
            pixel3 = pixel2 + 1;
            pixel4 = pixel1 + n;
            pixel5 = pixel4 + 1;
            pixel6 = pixel5 + 1;
            pixel7 = pixel4 + n;
            pixel8 = pixel7 + 1;
            pixel9 = pixel8 + 1;
            // rows
            for (j = 1; j < n_minus_1; ++j) {

                // sum all 9 pixels as sharp kernel
                red = multBy9(pixel5->red) + multByMinus1(pixel1->red + pixel2->red + pixel3->red + pixel4->red +
                                                          pixel6->red + pixel7->red + pixel8->red + pixel9->red);
                green = multBy9(pixel5->green) +
                        multByMinus1(pixel1->green + pixel2->green + pixel3->green + pixel4->green +
                                     pixel6->green + pixel7->green + pixel8->green + pixel9->green);
                blue = multBy9(pixel5->blue) + multByMinus1(pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue +
                                                            pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue);

                // assign_sum_to_pixel function

                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(blue, 0), 255));

                image_data[calcPlace(i, j, m)] = current_pixel;

                // next pixels
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;
            }
            temp += n;
        }
    }
    free(pixels);
}

inline void blur_and_filter(Image *image) {
    // pixels array
    int size = m * n * sizeof(pixel);
    pixel *pixels = malloc(size);
    // image data
    pixel *image_data = (pixel *) image->data;
    // copy image_data to pixels
    memcpy(pixels, image_data, size);

    int i, j, temp = 0, red, green, blue;
    pixel current_pixel;
    int m_minus_1 = m - 1, n_minus_1 = n - 1, n_minus_2 = n - 2;
    int min_intensity, max_intensity, sum_intensity;
    pixel *pixel1 ,*pixel2, *pixel3, *pixel4, *pixel5, *pixel6, *pixel7, *pixel8, *pixel9;
    pixel *min_pixel, *max_pixel;



    if (m % 2 == 0) {
        // columns
        for (i = 1; i < m_minus_1; ++i) {
            // find 9 addresses pixels around
            pixel1 = &pixels[temp];
            pixel2 = pixel1 + 1;
            pixel3 = pixel2 + 1;
            pixel4 = pixel1 + n;
            pixel5 = pixel4 + 1;
            pixel6 = pixel5 + 1;
            pixel7 = pixel4 + n;
            pixel8 = pixel7 + 1;
            pixel9 = pixel8 + 1;
            // rows
            for (j = 1; j < n_minus_2; j+=2) {

                /** first pixel*/

                // define pixel1 max and min
                sum_intensity = pixel1->red + pixel1->green + pixel1->blue;
                min_intensity = sum_intensity;
                min_pixel = pixel1;
                max_intensity = sum_intensity;
                max_pixel = pixel1;

                // pixel2
                sum_intensity = pixel2->red + pixel2->green + pixel2->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel2;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel2;
                    max_intensity = sum_intensity;
                }

                // pixel3
                sum_intensity = pixel3->red + pixel3->green + pixel3->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel3;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel3;
                    max_intensity = sum_intensity;
                }

                // pixel4
                sum_intensity = pixel4->red + pixel4->green + pixel4->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel4;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel4;
                    max_intensity = sum_intensity;
                }

                // pixel5
                sum_intensity = pixel5->red + pixel5->green + pixel5->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel5;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel5;
                    max_intensity = sum_intensity;
                }

                // pixel6
                sum_intensity = pixel6->red + pixel6->green + pixel6->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel6;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel6;
                    max_intensity = sum_intensity;
                }

                // pixel7
                sum_intensity = pixel7->red + pixel7->green + pixel7->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel7;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel7;
                    max_intensity = sum_intensity;
                }

                // pixel8
                sum_intensity = pixel8->red + pixel8->green + pixel8->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel8;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel8;
                    max_intensity = sum_intensity;
                }

                // pixel9
                sum_intensity = pixel9->red + pixel9->green + pixel9->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel9;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel9;
                    max_intensity = sum_intensity;
                }


                // sum all 9 pixels without min and max pixel
                red = pixel1->red + pixel2->red + pixel3->red + pixel4->red + pixel5->red +
                      pixel6->red + pixel7->red + pixel8->red + pixel9->red - min_pixel->red - max_pixel->red;
                green = pixel1->green + pixel2->green + pixel3->green + pixel4->green + pixel5->green +
                        pixel6->green + pixel7->green + pixel8->green + pixel9->green - min_pixel->green - max_pixel->green;
                blue = pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue + pixel5->blue +
                       pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue - min_pixel->blue - max_pixel->blue;


                // assign_sum_to_pixel function

                // divide by kernel's weight
                red = red = divideBy7(red);
                green = divideBy7(green);
                blue = divideBy7(blue);
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(blue, 0), 255));

                image_data[calcPlace(i, j, m)] = current_pixel;

                // next pixels
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;

                /** second pixel*/

                // define pixel1 max and min
                sum_intensity = pixel1->red + pixel1->green + pixel1->blue;
                min_intensity = sum_intensity;
                min_pixel = pixel1;
                max_intensity = sum_intensity;
                max_pixel = pixel1;

                // pixel2
                sum_intensity = pixel2->red + pixel2->green + pixel2->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel2;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel2;
                    max_intensity = sum_intensity;
                }

                // pixel3
                sum_intensity = pixel3->red + pixel3->green + pixel3->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel3;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel3;
                    max_intensity = sum_intensity;
                }

                // pixel4
                sum_intensity = pixel4->red + pixel4->green + pixel4->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel4;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel4;
                    max_intensity = sum_intensity;
                }

                // pixel5
                sum_intensity = pixel5->red + pixel5->green + pixel5->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel5;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel5;
                    max_intensity = sum_intensity;
                }

                // pixel6
                sum_intensity = pixel6->red + pixel6->green + pixel6->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel6;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel6;
                    max_intensity = sum_intensity;
                }

                // pixel7
                sum_intensity = pixel7->red + pixel7->green + pixel7->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel7;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel7;
                    max_intensity = sum_intensity;
                }

                // pixel8
                sum_intensity = pixel8->red + pixel8->green + pixel8->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel8;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel8;
                    max_intensity = sum_intensity;
                }

                // pixel9
                sum_intensity = pixel9->red + pixel9->green + pixel9->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel9;
                    min_intensity = sum_intensity;
                }
                if (sum_intensity > max_intensity) {
                    max_pixel = pixel9;
                    max_intensity = sum_intensity;
                }


                // sum all 9 pixels without min and max pixel
                red = pixel1->red + pixel2->red + pixel3->red + pixel4->red + pixel5->red +
                      pixel6->red + pixel7->red + pixel8->red + pixel9->red - min_pixel->red - max_pixel->red;
                green = pixel1->green + pixel2->green + pixel3->green + pixel4->green + pixel5->green +
                        pixel6->green + pixel7->green + pixel8->green + pixel9->green - min_pixel->green - max_pixel->green;
                blue = pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue + pixel5->blue +
                       pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue - min_pixel->blue - max_pixel->blue;

                // assign_sum_to_pixel function

                // divide by kernel's weight
                red = divideBy7(red);
                green = divideBy7(green);
                blue = divideBy7(blue);
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(blue, 0), 255));

                image_data[calcPlace(i, j +1, m)] = current_pixel;

                // next pixels
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;
            }
            temp += n;
        }

    } else {
        // columns
        for (i = 1; i < m_minus_1; ++i) {
            // find 9 addresses pixels around
            pixel1 = &pixels[temp];
            pixel2 = pixel1 + 1;
            pixel3 = pixel2 + 1;
            pixel4 = pixel1 + n;
            pixel5 = pixel4 + 1;
            pixel6 = pixel5 + 1;
            pixel7 = pixel4 + n;
            pixel8 = pixel7 + 1;
            pixel9 = pixel8 + 1;
            // rows
            for (j = 1; j < n_minus_1; ++j) {

                // pixel1 define max and min
                sum_intensity = pixel1->red + pixel1->green + pixel1->blue;
                min_intensity = sum_intensity;
                min_pixel = pixel1;
                max_intensity = sum_intensity;
                max_pixel = pixel1;

                // pixel2
                sum_intensity = pixel2->red + pixel2->green + pixel2->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel2;
                    min_intensity = sum_intensity;
                } else if (sum_intensity > max_intensity) {
                    max_pixel = pixel2;
                    max_intensity = sum_intensity;
                }

                // pixel3
                sum_intensity = pixel3->red + pixel3->green + pixel3->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel3;
                    min_intensity = sum_intensity;
                } else if (sum_intensity > max_intensity) {
                    max_pixel = pixel3;
                    max_intensity = sum_intensity;
                }

                // pixel4
                sum_intensity = pixel4->red + pixel4->green + pixel4->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel4;
                    min_intensity = sum_intensity;
                } else if (sum_intensity > max_intensity) {
                    max_pixel = pixel4;
                    max_intensity = sum_intensity;
                }

                // pixel5
                sum_intensity = pixel5->red + pixel5->green + pixel5->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel5;
                    min_intensity = sum_intensity;
                } else if (sum_intensity > max_intensity) {
                    max_pixel = pixel5;
                    max_intensity = sum_intensity;
                }

                // pixel6
                sum_intensity = pixel6->red + pixel6->green + pixel6->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel6;
                    min_intensity = sum_intensity;
                } else if (sum_intensity > max_intensity) {
                    max_pixel = pixel6;
                    max_intensity = sum_intensity;
                }

                // pixel7
                sum_intensity = pixel7->red + pixel7->green + pixel7->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel7;
                    min_intensity = sum_intensity;
                } else if (sum_intensity > max_intensity) {
                    max_pixel = pixel7;
                    max_intensity = sum_intensity;
                }

                // pixel8
                sum_intensity = pixel8->red + pixel8->green + pixel8->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel8;
                    min_intensity = sum_intensity;
                } else if (sum_intensity > max_intensity) {
                    max_pixel = pixel8;
                    max_intensity = sum_intensity;
                }

                // pixel9
                sum_intensity = pixel9->red + pixel9->green + pixel9->blue;
                if (sum_intensity <= min_intensity) {
                    min_pixel = pixel9;
                    min_intensity = sum_intensity;
                } else if (sum_intensity > max_intensity) {
                    max_pixel = pixel9;
                    max_intensity = sum_intensity;
                }


                // sum all 9 pixels without min and max pixel
                red = pixel1->red + pixel2->red + pixel3->red + pixel4->red + pixel5->red +
                      pixel6->red + pixel7->red + pixel8->red + pixel9->red - min_pixel->red - max_pixel->red;
                green = pixel1->green + pixel2->green + pixel3->green + pixel4->green + pixel5->green +
                        pixel6->green + pixel7->green + pixel8->green + pixel9->green - min_pixel->green - max_pixel->green;
                blue = pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue + pixel5->blue +
                       pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue - min_pixel->blue - max_pixel->blue;


                // assign_sum_to_pixel function

                // divide by kernel's weight
                red = divideBy7(red);
                green = divideBy7(green);
                blue = divideBy7(blue);
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(blue, 0), 255));

                image_data[calcPlace(i, j, m)] = current_pixel;

                // next pixels
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;
            }
            temp += n;
        }
    }

}


void myfunction(Image *image, char *srcImgpName, char *blurRsltImgName, char *sharpRsltImgName,
                char *filteredBlurRsltImgName, char *filteredSharpRsltImgName, char flag) {
    if (flag == '1') {
        // blur image
        blur(image);
        // write result image to file
        writeBMP(image, srcImgpName, blurRsltImgName);
        // sharpen the resulting image
        sharpen(image);
        // write result image to file
        writeBMP(image, srcImgpName, sharpRsltImgName);
    } else {
        // apply extermum filtered kernel to blur image
        blur_and_filter(image);
        // write result image to file
        writeBMP(image, srcImgpName, filteredBlurRsltImgName);
        // sharpen the resulting image
        sharpen(image);
        // write result image to file
        writeBMP(image, srcImgpName, filteredSharpRsltImgName);
    }
}

