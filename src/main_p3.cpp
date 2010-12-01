#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include <Imagen.h>
#include <Magick++.h>
#include <iostream> 

#include "mg.h"
#include "seam_finding.h"
#include "transfer.h"

using namespace std; 
using namespace Magick; 


void uso()
{
	fprintf(stderr,"Uso: prueba  target imagen_salida tamanyo_lado_Bi\n");
	exit(1);
}

int main(int argc,char **argv)
{
//verifica que la cantidad de argumentos es correcta 
	if(argc<4)
		uso();

//obtiene las variables de la entrada
	argv++;
	char * entrada_char1=*argv++;
	char * entrada_char2=*argv++;
	char * salida_char=*argv++;
	unsigned tam_Bi = abs( atoi(*argv++) );
	strcat(salida_char,".png");

	Imagen textureR,textureG,textureB,targetR,targetG,targetB;

	textureR=lee(entrada_char1,0);
	textureG=lee(entrada_char1,1);
	textureB=lee(entrada_char1,2);

	targetR=lee(entrada_char2,0);
	targetG=lee(entrada_char2,1);
	targetB=lee(entrada_char2,2);

	float alpha=1.0;
	//transfiere la textura de la imagen de la izquierda a la de la derecha
	transferTexture(textureR,textureG,textureB,targetR,targetG,targetB,tam_Bi,alpha);

	//Escribimos el resultado
//desde transfer.cpp
	
	return 0;
}

