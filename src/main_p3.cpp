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
	fprintf(stderr,"Uso: prueba texture target imagen_salida tamanyo_lado_Bi\n");
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

	Imagen tex1R,tex1G,tex1B,tex2R,tex2G,tex2B;

	tex1R=lee(entrada_char1,0);
	tex1G=lee(entrada_char1,1);
	tex1B=lee(entrada_char1,2);

	tex2R=lee(entrada_char2,0);
	tex2G=lee(entrada_char2,1);
	tex2B=lee(entrada_char2,2);

	//transfiere la textura de la imagen de la izquierda a la de la derecha
	transferTexture(tex1R,tex1G,tex1B,tex2R,tex2G,tex2B,tam_Bi);

//Escribimos el resultado
	escribe(salida_char,tex2R,tex2G,tex2B);
	cout<<"Nueva imagen creada"<<endl;
	
	return 0;
}

