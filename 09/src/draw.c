#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "draw.h"


// If you want you can use the provided struct and static function

typedef struct COLOR_s {
   unsigned char r; // red channel
   unsigned char g; // green channel
   unsigned char b; // blue channel
} COLOR;

static COLOR color_converter(double value) {
    COLOR c;
    c.r = 0;
    c.g = 0;
    c.b = 0;

    // TODO color mapping
    if (value<=0.25 )
    {
        c.r=0;
        //Green has slope 1
        c.g=convertValue(value);
        c.b=255;
    }
    else if (value<=0.5 )
    {
        c.r=0;
        c.g=255;
         //Blue has slope 1
        c.b=convertValue(value);
    }
    else if (value<=0.75 )
    {
        //Red has slope 1
        c.r=convertValue(value);;
        c.g=255;
        c.b=0;
    }
    else
    {
        c.r=255;
        c.g=convertValue(value);;
         //Blue has slope 1
        c.b=0;
    }
    
    return c;
}

unsigned char convertValue(double value) {
    return (unsigned char)(value * 255);
}

void draw_grid(double* grid, uint32_t x, uint32_t y, const char* filepath) {

    FILE *fp = fopen(filepath, "w");
    if (fp != NULL) {
        // Write the PPM header with meta information
        fprintf(fp, "P3\n%d %d\n255\n", x, y);

        // Iterate through the grid and convert values to color
        for (uint32_t i = 0; i < y; ++i) {
            for (uint32_t j = 0; j < x; ++j) {
                // Pass grid value and convert it to a COLOR struct
                COLOR c = color_converter(grid[x * i + j]);
              //debugger  COLOR c = color_converter((double)rand() / RAND_MAX);
                fprintf(fp, "%d %d %d\n", c.r, c.g, c.b);
            }
        }

        // Close the file
        fclose(fp);
    } else {
        // Handle the case where file opening fails
        printf("Failed to open the file for writing.\n");
    }
    
}
