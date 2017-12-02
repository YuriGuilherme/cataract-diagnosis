#ifndef CATDIG_H
#define CATDIG_H

typedef struct Pixel {
  int red, green, blue;
} Pixel;

typedef struct PPM {
  int height;
  int width;
  int maxColor;
  char * comment;
  Pixel * pixels;
} PPM;


void __init__(int argc, char* argv[]);

PPM *openFile(const char *file_name);

PPM *newPPM(int width, int heigth, int maxColor);

void savePPMInFile(const char *file_name, PPM *ppm);

void cleanPPM(PPM * ppm);

PPM * colorToGrayscale(PPM * ppm);

PPM * ppmGaussianSmoothFilter( PPM * ppm );

PPM * binarizacao(PPM * ppm);

PPM * ppmSobelSmoothFilter( PPM * ppm );

PPM * neighborhoodAnalysis(PPM * ppm);

#endif
