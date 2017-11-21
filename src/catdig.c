#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "catdig.h"

PPM *newPPM(char * comment, int width, int height, int maxColor) {
    PPM *ppm = (PPM *) malloc(sizeof(PPM));
    ppm->pixels = (Pixel *) malloc(width * height * sizeof(Pixel));
    ppm->comment = malloc(sizeof(char) * 100);
    ppm->comment = comment;
    ppm->width = width;
    ppm->height = height;
    ppm->maxColor = maxColor;
    return ppm;
}

void cleanPPM(PPM * ppm) {
    free(ppm->pixels);
    free(ppm);
}

void savePPMInFile(const char *file_name, PPM *ppm) {
    FILE * file = fopen(file_name, "w+");
    fprintf(file, "P3\n%d %d\n%d", ppm->width, ppm->height, ppm->maxColor);

    int x;
    printf(ppm->comment);
    for(x = 0; x < (ppm->height * ppm->width); x++) {
        Pixel *p = &(ppm->pixels[x]);
        fprintf(file, "\n%d %d %d", p->red, p->green, p->blue);
    }
}

PPM *openFile(const char *file_name) {

    FILE *file = fopen(file_name, "r");

    if (file == NULL) return NULL;

    char format[4];
    fscanf(file, "%s\n", format);

    if (strcmp("P3", format) == 0) {

        int width, height, maxColor;
        char comment[100];

        fgets(comment, sizeof(comment), file);
        fscanf(file, "%d", &(width));
        fscanf(file, "%d", &(height));
        fscanf(file, "%d", &(maxColor));
        PPM *ppm = newPPM(comment, width, height, maxColor);
        int x;
        for (x = 0; x < (height * width); x++) {
            Pixel *p = &(ppm->pixels[x]);
            fscanf(file, "%d", &(p->red));
            fscanf(file, "%d", &(p->green));
            fscanf(file, "%d", &(p->blue));
        }
        fclose(file);
        printf(ppm->comment);
        return ppm;
    }
    fclose(file);
    return NULL;
}

/* Adiciona-se então 30% do vermelho mais 59% do verde mais 11% do azul*/


void colorToGrayscale(PPM * ppm) {
    int x;
    int brightness;
    for(x = 0; x < (ppm->height * ppm->width); x++) {
        Pixel *p = &(ppm->pixels[x]);
        brightness = (int) (p->red * 0.3) + (p->green * 0.59) + (p->blue * 0.11);
        p->red = brightness;
        p->green = brightness;
        p->blue = brightness;
    }
}

Pixel * image_read_pixel(PPM * ppm, int x) {
    if( x >= (ppm->height * ppm->width) ) x = (ppm->height * ppm->width) - 1;
    if( x < 0 ) x = 0;

    return &ppm->pixels[x];
}

PPM * ppmGaussianSmoothFilter( PPM * ppm ) {
    int x, y, col, row, newpx;
    Pixel * px;
    int sum, div;

    int kernel[25] = {2,  4,  5,  4, 2,\
                      4,  9, 12,  9, 4,\
                      5, 12, 15, 12, 5,\
                      4,  9, 12,  9, 4,\
                      2,  4,  5,  4, 2};

    /* Debug */
    printf( "Filtrando Imagem: tipo=P3; width=%d; height=%d\n", ppm->width, ppm->height );

    PPM * newimg = newPPM( ppm->comment ,ppm->width, ppm->height, ppm->maxColor );

    for(col = 0; col < (ppm->height * ppm->width); col++) {
        sum = 0;
        div = 0;

        for(x = 0; x < 25; x++) {
            px = image_read_pixel( ppm,  (col + ((x - ((2 * ppm->width)+2)))));
            sum += ( px->red *  kernel[x] );
            div += kernel[x];
        }

        newpx = (int) sum / div;

        newimg->pixels[col].red = newpx;
        newimg->pixels[col].green = newpx;
        newimg->pixels[col].blue = newpx;
    }

    return newimg;
}

PPM * realceArestas(PPM * ppm) {
  PPM * newppm = newPPM(ppm->comment, ppm->width, ppm->height, ppm->maxColor);
  int x;
  for (x = 0; x < (ppm->height * ppm->width); x++) {
    Pixel *p = &(ppm->pixels[x]);
    if (p->red < 130) {
      newppm->pixels[x].red = 0;
      newppm->pixels[x].green = 0;
      newppm->pixels[x].blue = 0;
    } else {
      newppm->pixels[x].red = 1;
      newppm->pixels[x].green = 1;
      newppm->pixels[x].blue = 1;
    }
    newppm->maxColor = 1;
  }
    return newppm;
}
