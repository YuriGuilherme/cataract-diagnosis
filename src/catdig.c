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

