#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include <Imagen.h>
#include <Magick++.h>
#include <iostream> 

#include <mg.h>
#include <seam_finding.h>

using namespace std; 
using namespace Magick; 

Imagen texR,texG,texB;

void uso()
{
	fprintf(stderr,"Uso: prueba imagen_entrada(textura) imagen_salida filas_Bi columnas_Bi filas_img_salida columnas_img_salida\n");
	exit(1);
}

void casos_error(Imagen & texR, unsigned int rows_Bi, unsigned int cols_Bi, unsigned int rows_IMout, unsigned int cols_IMout)
{
	if( rows_Bi > texR.fils() || cols_Bi > texR.cols() )
	{
		fprintf(stderr, "Bi debe caber dentro de la imagen de entrada!! \n");
		exit(1);
	}
	
	if( rows_IMout < texR.fils() || cols_IMout < texR.cols() )
	{
		fprintf(stderr, "La imagen de salida debe ser más grande que la de entrada!! \n");
		exit(1);
	}
}

int main(int argc,char **argv)
{
//verifica que la cantidad de argumentos es correcta 
	if(argc<7)
		uso();

//obtiene las variables de la entrada
	argv++;
	char * entrada_char=*argv++;
	char * salida_char=*argv++;
	int rows_Bi = abs( atoi(*argv++) );
	int cols_Bi = abs( atoi(*argv++) );
	int rows_IMout = abs( atoi(*argv++) );
	int cols_IMout = abs( atoi(*argv++) );

	//RGB son variables globales
	texR=lee(entrada_char,0);
	texG=lee(entrada_char,1);
	texB=lee(entrada_char,2);
	
//comprueba que los parámetros sean correctos
	casos_error(texR, rows_Bi, cols_Bi, rows_IMout, cols_IMout);

//se crea cada componente de la imagen de salida, todo a cero
	Imagen IMoutR(rows_IMout, cols_IMout, 0.0);
	Imagen IMoutG(rows_IMout, cols_IMout, 0.0);
	Imagen IMoutB(rows_IMout, cols_IMout, 0.0);

	

	
/*
	while( (rows_out != 0) || (cols_out != 0) )
	{
		cout<<"Calculando iteración "<< it <<" de "<< total_it <<endl;
		
		// F.E.O.
		crea_energias(uR,E);
		crea_energias(uG,E);
		crea_energias(uB,E);
		E*=1/3.0;

		// A D D /////////////////////////////////////////////////////
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
				/*if(cols_out)
				{
					find_v_seam(E,E);
					columnOut(E,1);

					Ec.resize_erase(Ec.fils(), Ec.cols()+1);
					E.resize_erase(E.fils(), E.cols()+1);
					cols_out--;
				}
				*/
/*			
			//exit(1);
		}
		///////////////////////////////////////////////////// A D D //
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

	cout<<"Creando nueva imagen"<<endl;

	if(!fork()){
		strcat(salida_char,".png");
		escribe(salida_char,IMoutR,IMoutG,IMoutB);
		exit(1);
	}

	return 0;
}

