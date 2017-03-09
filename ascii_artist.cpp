#include <stdlib.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef unsigned char byte;

const char MAP[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
const int CELL_WIDTH = 10;
const int CELL_HEIGHT = 20;

char path[1024];

int main()
{
    printf("file path: ");
    scanf("%s", path);

    int width, height, components;
    width = height = 0;
    byte* data = (byte*) stbi_load(path, &width, &height, &components, 3);

    if (data == 0)
    {
        printf("couldn't load image...\n");
        system("pause");
        return 0;
    }

    for (int y = 0; y + CELL_HEIGHT <= height; y += CELL_HEIGHT)
    {
        for (int x = 0; x + CELL_WIDTH <= width; x += CELL_WIDTH)
        {
            double average_luminance = 0;
            for (int ox = 0; ox < CELL_WIDTH; ox++)
                for (int oy = 0; oy < CELL_HEIGHT; oy++)
                {
                    byte* pixel = &data[((y + oy) * width + (x + ox)) * 3];
                    double r = pixel[0] / 255.0;
                    double g = pixel[1] / 255.0;
                    double b = pixel[2] / 255.0;

                    // double luminance = 0.2126 * r + 0.7152 * g + 0.0722 * b;
                    double luminance = 0.299*r + 0.587*g + 0.114*b;
                    average_luminance += luminance;
                }

            average_luminance /= CELL_WIDTH * CELL_HEIGHT;
            average_luminance = 1 - average_luminance;
            average_luminance *= average_luminance;
            average_luminance *= average_luminance;
            average_luminance = 1 - average_luminance;

            int index = (int)(average_luminance * sizeof(MAP));
            if (index >= sizeof(MAP))
                index = sizeof(MAP) - 1;

            char character = MAP[index];
            printf("%c", character);
        }
        printf("\n");
    }

    stbi_image_free(data);
    system("pause");
}
