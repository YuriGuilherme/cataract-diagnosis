#ifndef CATDIG_H
#define CATDIG_H

typedef struct {
  int red;
  int green;
  int blue;
} Pixel;

typedef struct {
  int height;
  int width;
  Pixel * pixels;
} ppm;

typedef enum {PPM} inputFormat;

#endif /* CATDIG_H */