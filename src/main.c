#include <stdio.h>
#include <stdlib.h>

#include "catdig.h"

void main(int argc, char* argv[]) {


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

  PPM * image_grey = colorToGrayscale(image);
  cleanPPM(image);
  savePPMInFile("bin/cinza.ppm", image_grey);

  PPM * image_gaussian = ppmGaussianSmoothFilter(image_grey);
  cleanPPM(image_grey);
  savePPMInFile("bin/gaussian.ppm", image_gaussian);

  PPM * image_sobel = ppmSobelSmoothFilter(image_gaussian);
  cleanPPM(image_gaussian);
  savePPMInFile("bin/sobel_2.ppm", image_sobel);

  PPM * image_binaria = binarizacao(image_gaussian);
  puts("Binario gerado");
  savePPMInFile("bin/binaria.ppm", image_binaria);

  cleanPPM(image_sobel);
  cleanPPM(image_binaria);
}
