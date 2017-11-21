#include <stdio.h>
#include <stdlib.h>

#include "catdig.h"

int main(int argc, char* argv[]) {

  PPM *image = openFile(argv[2]);
  if (image == NULL) {
    printf("Arquivo não é um PPM P3 ou não existe");
    return 1;
  }

  savePPMInFile("bin/normal.ppm", image);

  colorToGrayscale(image);
  savePPMInFile("bin/cinza.ppm", image);

  PPM * image_gaussian = ppmGaussianSmoothFilter(image);
  savePPMInFile("bin/gaussian.ppm", image_gaussian);

  PPM * image_binaria = realceArestas(image);
  savePPMInFile("bin/binaria.ppm", image_binaria);

  PPM * image_binaria_gaussian = realceArestas(image_gaussian);
  savePPMInFile("bin/binaria_gaussian.ppm", image_binaria_gaussian);

  cleanPPM(image);
  return 0;
}
