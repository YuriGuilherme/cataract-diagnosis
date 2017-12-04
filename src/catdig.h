#ifndef CATDIG_H
#define CATDIG_H

/* TYPES */
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

typedef struct {
  int input_length;
  char ** input_name;
  char * format_name;
  char * output_name;
} Arg;

enum flags {input=1, output, format};
/* END-TYPES */

/* FUNCTIONS */
void __init__(int argc, char* argv[]);

float exec(char * input_name, char * output_name, char * format_name);

PPM *openFile(const char *file_name);

PPM *newPPM(int width, int heigth, int maxColor);

void savePPMInFile(const char *file_name, PPM *ppm);

void cleanPPM(PPM * ppm);

PPM * colorToGrayscale(PPM * ppm);

PPM * ppmGaussianSmoothFilter( PPM * ppm );

PPM * binarizacao(PPM * ppm);

PPM * ppmSobelSmoothFilter( PPM * ppm );

PPM * neighborhoodAnalysis(PPM * ppm);
/* END-FUNCTIONS */

#endif
