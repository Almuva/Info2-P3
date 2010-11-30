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
#include "quilting.h"

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
	int tam_Bi = abs( atoi(*argv++) );
	strcat(salida_char,".png");

	Imagen tex1R,tex1G,tex1B,tex2R,tex2G,tex2B,Luminancia1,Luminancia2,imagenAuxuliar;

	tex1R=lee(entrada_char1,0);
	tex1G=lee(entrada_char1,1);
	tex1B=lee(entrada_char1,2);

	tex2R=lee(entrada_char2,0);
	tex2G=lee(entrada_char2,1);
	tex2B=lee(entrada_char2,2);
	
//cada luminancia es una imagen a parte que guarda la luminancia de la imagen de entrada
	Luminancia1=tex1R; Luminancia1*=0.3;
	imagenAuxuliar=tex1G; imagenAuxuliar*=0.59; Luminancia1+=imagenAuxuliar;
	imagenAuxuliar=tex1B; imagenAuxuliar*=0.11; Luminancia1+=imagenAuxuliar;
	
	Luminancia2=tex2R; Luminancia2*=0.3;
	imagenAuxuliar=tex2G; imagenAuxuliar*=0.59; Luminancia2+=imagenAuxuliar;
	imagenAuxuliar=tex2B; imagenAuxuliar*=0.11; Luminancia2+=imagenAuxuliar;

//Escribimos el resultado
	//escribe(salida_char,IMoutR,IMoutG,IMoutB);
	escribe("LumLemon.jpg",Luminancia1);
	escribe("LumPear.jpg",Luminancia2);
	cout<<"Nueva imagen creada"<<endl;
	
	return 0;
}

