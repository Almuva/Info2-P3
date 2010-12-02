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

	Imagen texR,texG,texB;
	//se crea cada componente de la imagen de salida
	Imagen IMoutR(rows_IMout, cols_IMout),IMoutG(rows_IMout, cols_IMout),IMoutB(rows_IMout, cols_IMout);

	texR=lee(entrada_char,0);
	texG=lee(entrada_char,1);
	texB=lee(entrada_char,2);
	
	bool transfer=false;
	
	if(transfer)
	{
		IMoutR=lee(salida_char,0);
		IMoutG=lee(salida_char,1);
		IMoutB=lee(salida_char,2);
		rows_IMout=IMoutR.fils();
		cols_IMout=IMoutR.cols();
	}
	else
	{
		//comprueba que los parámetros sean correctos
		casos_error(texR, tam_Bi, rows_IMout, cols_IMout);
	}

//La función quilting() emprea el bucle principal de llenado de IMout con Bi's
	quilting(texR, texG, texB, tam_Bi, IMoutR, IMoutG, IMoutB);

//Escribimos el resultado
	std::string s="result "+std::string(salida_char);
	escribe((char*)s.c_str(),IMoutR,IMoutG,IMoutB);
	cout<<"Nueva imagen creada"<<endl;
	return 0;
}

