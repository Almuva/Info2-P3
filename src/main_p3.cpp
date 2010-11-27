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
	fprintf(stderr,"Uso: prueba imagen_entrada(textura) imagen_salida tamanyo_lado_Bi filas_img_salida columnas_img_salida\n");
	exit(1);
}

void casos_error(Imagen & texR, unsigned int tam_Bi, unsigned int rows_IMout, unsigned int cols_IMout)
{
	//Al tamaño de Bi le sumamos el margen (1/6 de la dimensión)
	if( tam_Bi+tam_Bi/3 > texR.fils() || tam_Bi+tam_Bi/3 > texR.cols() )
	{
		fprintf(stderr, "ERROR: Bi+margenes(1/6 de Bi) debe caber dentro de la imagen de entrada!! \n");
		exit(1);
	}
	
	if( rows_IMout <= texR.fils() || cols_IMout <= texR.cols() )
	{
		fprintf(stderr, "ERROR: La imagen de salida debe ser más grande que la de entrada!! \n");
		exit(1);
	}
}

int main(int argc,char **argv)
{
//verifica que la cantidad de argumentos es correcta 
	if(argc<6)
		uso();

//obtiene las variables de la entrada
	argv++;
	char * entrada_char=*argv++;
	char * salida_char=*argv++;
	int tam_Bi = abs( atoi(*argv++) );
	int rows_IMout = abs( atoi(*argv++) );
	int cols_IMout = abs( atoi(*argv++) );
	strcat(salida_char,".png");

	Imagen texR,texG,texB;
	texR=lee(entrada_char,0);
	texG=lee(entrada_char,1);
	texB=lee(entrada_char,2);

//comprueba que los parámetros sean correctos
	casos_error(texR, tam_Bi, rows_IMout, cols_IMout);

//se crea cada componente de la imagen de salida, todo a cero
	Imagen IMoutR(rows_IMout, cols_IMout, 0);
	Imagen IMoutG(rows_IMout, cols_IMout, 0);
	Imagen IMoutB(rows_IMout, cols_IMout, 0);
	
	
//La función quilting() emprea el bucle principal de llenado de IMout con Bi's
	quilting(texR, texG, texB, tam_Bi, IMoutR, IMoutG, IMoutB);

//Escribimos el resultado
	cout<<"Creando nueva imagen"<<endl;
	escribe(salida_char,IMoutR,IMoutG,IMoutB);
	
/*
//PRUEBA: Función comp()
	Imagen texAll(texR.fils(), texR.cols()); texAll+=texR; texAll+=texG; texAll+=texB; 
	Imagen comp(50,50) ,imgA(comp.fils(),comp.cols(), 0),imgB(comp.fils(),comp.cols());
	
	//imgA.extrae(texAll,0,0);
	imgB.extrae(texAll,1,1);
	
	double enx = compara(imgA,imgB);
	cout<<"EnergiaX: "<<enx<<endl;
	
	double en = compara(imgA,imgB,comp);
	cout<<"Energia: "<<en<<endl;
	escribe((char*)"compara.png",comp);
*/

	return 0;
}

