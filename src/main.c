#include <stdio.h>
#include <stdlib.h>

#include "catdig.h"
#include "help.h"

int main(int argc, char* argv[]) {


  /* This function is responsible for executing the program
   *
   *@params
   *  int argc  -> Number of arguments
   *  char argv -> List of arguments and flags
   *
   *#flags
   *  -i <file_name>  -> To input file
   *  -o <file_name>  -> To output file
   *  -f <forma_name> -> Name of format (Ex.: PPM or BPM)
   */

  __init__(argc, argv);

  PPM *image = openFile(argv[2]);

  if (image == NULL)
    printf("Arquivo não é um PPM P3 ou não existe");

  savePPMInFile("bin/normal.ppm", image);

  image = colorToGrayscale(image);
  savePPMInFile("bin/cinza.ppm", image);

  image= ppmGaussianSmoothFilter(image);
  savePPMInFile("bin/gaussian.ppm", image);

  image = binarizacao(image);
  savePPMInFile("bin/binaria.ppm", image);

  image = ppmSobelSmoothFilter(image);
  savePPMInFile("bin/sobel.ppm", image);

  image = neighborhoodAnalysis(image);
  savePPMInFile("bin/object.ppm", image);

  cleanPPM(image);

  return 0;
}
