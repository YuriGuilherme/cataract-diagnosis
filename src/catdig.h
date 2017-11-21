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
PPM *openFile(const char *file_name);

#endif /* CATDIG_H */
