#include <stdio.h>
#include <stdlib.h>

#include "catdig.h"

int main(void){

	char x;
	FILE *fotoin;
	fotoin = fopen ("Catarata.ppm", "r");
	if (fotoin == NULL) 
	 {
	 	printf("Erro na abertura do aquivo!\n");
	 }
	 else
	{
		fscanf(fotoin, &x);
		printf("%d\n", x);
		fclose(fotoin);
	} 	
	
  return 0;
}
