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

  return 0;
}
