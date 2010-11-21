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

Imagen uR,uG,uB;

void uso()
{
	fprintf(stderr,"Uso: prueba imagen_entrada(textura) imagen_salida filas_Bi columnas_Bi\n");
	exit(1);
}

int main(int argc,char **argv)
{
	//verifica que la cantidad de argumentos es correcta 
	if(argc<5)
		uso();

	argv++;
	char * entrada_char=*argv++;
	char * salida_char=*argv++;
	int rows_Bi = atoi(*argv++);
	int cols_Bi = atoi(*argv++);

	cout<<"Leyendo "<<entrada_char<<endl;
	//ara RGB son variables globals
	uR=lee(entrada_char,0);
	uG=lee(entrada_char,1);
	uB=lee(entrada_char,2);

	if(   ( (rows_out<0) && (abs(rows_out)>uR.fils()) ) || ( (cols_out<0) && (abs(cols_out)>uR.cols()) )   )
	{
		fprintf(stderr, "Valor de las filas o columnas a eliminar demasiado grande! \n");
	}

	//Se crea la matriz de energias de la matriz
	Imagen E(uR.fils(), uR.cols());

	unsigned int it = 1;
	unsigned int total_it = abs(rows_out) + abs(cols_out);
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
		escribe(salida_char,uR,uG,uB);
		exit(1);
	}

	return 0;
}

