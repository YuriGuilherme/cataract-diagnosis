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

  cleanPPM(image);
  return 0;
}
