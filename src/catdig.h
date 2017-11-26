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

typedef enum {ppm} inputFormat;

PPM *newPPM(char * comment, int width, int heigth, int maxColor);
void cleanPPM(PPM * ppm);
void savePPMInFile(const char *file_name, PPM *ppm);
void colorToGrayscale(PPM * ppm) ;
Pixel * image_read_pixel(PPM * ppm, int col, int row);
PPM * ppmGaussianSmoothFilter( PPM * ppm );
PPM * ppmSobelSmoothFilter( PPM * ppm );
PPM *openFile(const char *file_name);

PPM * realceArestas(PPM * ppm);
#endif /* CATDIG_H */
