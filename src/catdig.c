#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "catdig.h"

/* https://www.youtube.com/watch?v=e2QIFGpE0Lo&list=PL4_SsHNp9R6cf6pDTSSmz2XUWUh4Z7Hck&index=13 */
void __init__(int argc, char* argv[]) {

}

PPM *newPPM(int width, int height, int maxColor) {
  PPM *ppm = (PPM *) malloc(sizeof(PPM));
  ppm->pixels = (Pixel *) malloc(width * height * sizeof(Pixel));
  ppm->comment = malloc(sizeof(char) * 100);
  ppm->comment = "#Genereted by catdig";
  ppm->width = width;
  ppm->height = height;
  ppm->maxColor = maxColor;
  return ppm;
}

void applyInRGB(int color, Pixel* pixel) {
  pixel->red = color;
  pixel->green = color;
  pixel->blue = color;
}

void cleanPPM(PPM * ppm) {
  /* Desaloca os ponteiros ppm e variável responsável usando o "free". */
    free(ppm->pixels);
    free(ppm);
}

void savePPMInFile(const char *file_name, PPM *ppm) {
  /* Joga seus valores no arquivo 'file' ordenadamente na sequencia RGB. */
    FILE * file = fopen(file_name, "w+");
    fprintf(file, "P3\n%d %d\n%d", ppm->width, ppm->height, ppm->maxColor);

    int x;
    printf(ppm->comment);
    for(x = 0; x < (ppm->height * ppm->width); x++) {
        Pixel* pixel = &(ppm->pixels[x]);
        fprintf(file, "\n%d %d %d", pixel->red, pixel->green, pixel->blue);
    }
}

PPM *openFile(const char *file_name) {

/* Processo de abertura e leitura da foto propriamente dita.
Essa função lê cada dado da foto e aplica na struct PPM criada no ínicio. */

    FILE *file = fopen(file_name, "r");


    if (file == NULL) return NULL;/* Processo de debug da abertura do arquivo. */

    char format[4];
    fscanf(file, "%s\n", format);

    if (strcmp("P3", format) == 0) {

        int width, height, maxColor;
        char comment[100];

        fgets(comment, sizeof(comment), file);
        fscanf(file, "%d", &(width));
        fscanf(file, "%d", &(height));
        fscanf(file, "%d", &(maxColor));
        PPM *ppm = newPPM(width, height, maxColor);
        int x;
        for (x = 0; x < (height * width); x++) {
            Pixel* pixel = &(ppm->pixels[x]);
            fscanf(file, "%d", &(pixel->red));
            fscanf(file, "%d", &(pixel->green));
            fscanf(file, "%d", &(pixel->blue));
        }
        fclose(file);
        printf(ppm->comment);
        return ppm;
    }
    fclose(file);
    return NULL;
}



PPM * colorToGrayscale(PPM * ppm) {

  /* Adiciona a cada variável da struct as diretrizes para transfomar o arquivo em escala de cinza. +30% R, + %59 G, %11 B.*/

  int brightness, x;

  PPM* newppm = newPPM(
    ppm->width,
    ppm->height,
    ppm->maxColor
  );

  for(x = 0; x < (ppm->height * ppm->width); x++) {

    Pixel* pixel = &(ppm->pixels[x]);
    brightness = (int) (pixel->red * 0.3) + (pixel->green * 0.59) + (pixel->blue * 0.11);

    applyInRGB(brightness, &newppm->pixels[x]);
  }
  return newppm;
}

Pixel * image_read_pixel(PPM * ppm, int col, int row) {
  if( col >= ppm->width ) col = ppm->width - 1;
  if( row >= ppm->height ) row = ppm->height - 1;
  if( col < 0 ) col = 0;
  if( row < 0 ) row = 0;
  int x = ((row* ppm->width)+col);
  return &ppm->pixels[x];
}

PPM * ppmGaussianSmoothFilter( PPM * ppm ) {

/*Aplica o filtro Gaussian com a matriz indicada no pdf base de 5x5, necessária para remoção de imperfeições. 
Nota-se sempre a utilização apenas de um ponteiro como referência onde a struct abrange todas as informações 
necessárias. */


    int x, nx, y, col, ncol, row, newpx;
    Pixel * px;
    int sum, div;


    int kernel[25] = {2,  4,  5,  4, 2,\
                      4,  9, 12,  9, 4,\
                      5, 12, 15, 12, 5,\
                      4,  9, 12,  9, 4,\
                      2,  4,  5,  4, 2};

    /* Debug */
    /* printf( "Filtrando Imagem: tipo=P3; width=%d; height=%d\n", ppm->width, ppm->height ); */

    PPM * newimg = newPPM(
      ppm->width,
      ppm->height,
      ppm->maxColor
    );

    for(col = 0; col < (ppm->height * ppm->width); col++) {
        sum = 0;
        div = 0;
        row = (int) col / ppm->width;
        ncol = col - (row * ppm->width);
        for(x = 0; x < 25; x++) {
            y = (int) x / 5;
            nx = x - (y * 5);

            px = image_read_pixel( ppm, ncol + (nx-2), row + (y-2));
            sum += ( px->red *  kernel[x]);
            div += kernel[x];
        }

        newpx = (int) sum / div;

        applyInRGB(newpx, &newimg->pixels[col]);
    }

    return newimg;
}

int mod(int x) {
  return x>=0?x:-x;
}

static float sobel_x[9]={-1,  0,  1,
                         -2,  0,  2,
                         -1,  0,  1};

static float sobel_y[9]={ 1,  2,  1,
                          0,  0,  0,
                         -1, -2, -1 };
PPM * ppmSobelSmoothFilter( PPM * ppm ) {
  int dx, dy, val, y, x, k, col;
  int w = ppm->width;

  PPM * newppm = newPPM(
    ppm->width,
    ppm->height,
    ppm->maxColor
  );

  Pixel * p = ppm->pixels;

  for ( k=0; k < (ppm->width * ppm->height); k++) {
    y = (int) k / ppm->width;
    x = k - (y * ppm->width);
    if(y!=0 && x!=0 && x!=ppm->width-1 && y!=ppm->height-1) {
      int v[9] = {
        p[k+w-1].red, p[k+w].red, p[k+w+1].red,
        p[k-1].red  , p[k].red  , p[k+1].red,
        p[k-w-1].red, p[k-w].red, p[k-w+1].red
      };
      dx = 0;
      dy = 0;
      for(col = 0; col < 9;col++) {
        dx += v[col] * sobel_x[col];
        dy += v[col] * sobel_y[col];
      }
      val = mod(dx)+mod(dy);

      applyInRGB(val, &newppm->pixels[k]);
    } else {
      applyInRGB(0, &newppm->pixels[k]);
    }
  }

  return newppm;
}

/* Atenuação dos valores que não são arestas */

void calculateHistogram(PPM * ppm, int histogram[]) {
  int x;
  int brightness;

  for( x = 0; x < 255; x++) {
    histogram[x] = 0;
  }

  for( x = 0; x < (ppm->height * ppm->width); x++) {
    Pixel * pixel = &ppm->pixels[x];
    histogram[pixel->red]++;
  }
}


PPM * binarizacao(PPM * ppm) {
  int x;
  int histogram[255];
  float proportion[255], omega[255], mu[255];
  int threshold;
  float sigma ,maxSigma;
  puts("init ok");
  /* Calculado o histograma da imagem */
  calculateHistogram(ppm, histogram);
  puts("histogram ok");
  /* Calculando a proporção de uma cor na imagem */
  for( x = 0; x < 255; x++) {
    proportion[x] = (float) histogram[x] / (ppm->height * ppm->width);
  }
  puts("proportion ok");

  /* Calculando omega e mu */
  omega[0] = proportion[0];
  mu[0] = 0.0;
  for(x = 1; x <= 255; x++) {
    omega[x] = omega[x-1] + proportion[x];
    mu[x] = mu[x - 1] + (x * proportion[x]);
  }
  puts("omega ok");

  /* Calculando e achando o maior sigma */
  threshold = 0;
  maxSigma = 0.0;
  for( x = 0; x < 255; x++) {
    sigma = 0.0;

    if( omega[x] >= 0.0 && omega[x] <= 1.0) {
      float numerador = mu[255] * omega[x] - mu[x];
      float quociente = omega[x] * (1.0f - omega[x]);
      sigma = (numerador * numerador) / quociente;
    }
    if( sigma > maxSigma) {
      maxSigma = sigma;
      threshold = x;
    }
  }

  PPM * newppm = newPPM(
    ppm->width,
    ppm->height,
    1 /* maxColor */
  );


  for (x = 0; x < (ppm->height * ppm->width); x++) {
    if (ppm->pixels[x].red <= threshold) {
      applyInRGB(0, &newppm->pixels[x]);
    } else {
      applyInRGB(1, &newppm->pixels[x]);
    }
  }

  puts("Deu tudo certo");
  return newppm;
}
