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
	if( tam_Bi+2*tam_Bi/6 > texR.fils() || tam_Bi+2*tam_Bi/6 > texR.cols() )
	{
		fprintf(stderr, "ERROR: Bi+margenes(1/6 de Bi) debe caber dentro de la imagen de entrada!! \n");
		exit(1);
	}
	
	if( rows_IMout < texR.fils() || cols_IMout < texR.cols() )
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
	Imagen IMoutR(rows_IMout, cols_IMout, 0.0);
	Imagen IMoutG(rows_IMout, cols_IMout, 0.0);
	Imagen IMoutB(rows_IMout, cols_IMout, 0.0);

	quilting(texR, texG, texB, tam_Bi, IMoutR, IMoutG, IMoutB);

	
/*
	while( (rows_out != 0) || (cols_out != 0) )
	{
		cout<<"Calculando iteración "<< it <<" de "<< total_it <<endl;
		
		// F.E.O.
		crea_energias(uR,E);
		crea_energias(uG,E);
		crea_energias(uB,E);
		E*=1/3.0;

		if(rows_out >= 0 && cols_out >= 0)
		{
			// cout<<"x"<<endl;
			//cout<<"filas >= 0 && columnas >= 0 no implementado"<<endl;
			if (rows_out)
			{
				//cout<<"x1"<<endl;
				int r = rows_out;
				find_h_seam(E);
				while(rows_out)
				{
			//cout<<"xa:"<<rows_out<<endl;
					int i= smallestV(E);
					E(i, E.cols()-1)=10E20;
					backtrackH(E, E.cols()-1, i);
			//cout<<"xb:"<<rows_out<<endl;
					rows_out--;	
				}
				//cout<<"x2"<<endl;
				rowsIn(E,r);
				
				E.resize_erase(E.fils()+r, E.cols());
			}
				if(cols_out)
				{
					find_v_seam(E,E);
					columnOut(E,1);

					Ec.resize_erase(Ec.fils(), Ec.cols()+1);
					E.resize_erase(E.fils(), E.cols()+1);
					cols_out--;
				}
				
			
			//exit(1);
		}
		else if(rows_out <= 0 && cols_out <= 0)
		{
			if(rows_out != 0)
			{
				find_h_seam(E);
				// At the end of this process, the minimum value of the last row in M will indicate the end of the minimal connected vertical seam.// Hence, in the second step we BACKTRACK from this minimum entry on M to find the path of the optimal seam
				E(smallestV(E), E.cols()-1) = 10E20;
				backtrackH(E, E.cols()-1, smallestV(E));
				rowOut(E,-1);

				E.resize_erase(E.fils()-1, E.cols());
				rows_out++;				
			}
			else if(cols_out != 0)
			{
				find_v_seam(E);
				// At the end of this process, the minimum value of the last row in M will indicate the end of the minimal connected vertical seam.// Hence, in the second step we BACKTRACK from this minimum entry on M to find the path of the optimal seam
				E(E.fils()-1, smallestH(E)) = 10E20;
				backtrackV(E, E.fils()-1, smallestH(E));
				columnOut(E,-1);

				
				E.resize_erase(E.fils(), E.cols()-1);
				cols_out++;
			}
		}
		else if(rows_out >= 0 && cols_out <= 0)
		{
			cout<<"filas >= 0 && columnas <= 0 no implementado"<<endl;
			exit(1);
		}
		else if(rows_out <= 0 && cols_out >= 0)
		{
			cout<<"filas <= 0 && columnas >= 0 no implementado"<<endl;
			exit(1);
		}

		it++;
	}
*/

	Imagen extret(20,20);
	if(!extret.extrae(texR,1,0)){cout<<"NO EXTRET"<<endl;}

	escribe((char*)"extret.png",extret);

	cout<<"Creando nueva imagen"<<endl;
	IMoutR=texR;
	IMoutG=texG;
	IMoutB=texB;
	escribe(salida_char,IMoutR,IMoutG,IMoutB);

	return 0;
}

