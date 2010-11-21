#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <Imagen.h>
#include <iostream> 

#include <mg.h>

double calcula_gradiente(Imagen & Im, unsigned int i, unsigned int j)
{
	double gradiente = 0.0;

	//comparamos el pixel con los 4 vecinos en vertical y horizontal. Lo añadimmos al gradiente
	gradiente = fabs(Im(i, j) - Im(i-1, j)) 
		  + fabs(Im(i, j) - Im(i, j+1)) 
		  + fabs(Im(i, j) - Im(i+1, j)) 
		  + fabs(Im(i, j) - Im(i, j-1));

	//comparamos el pixel con los 4 vecinos en diagonal. Como tienen menos importancia, multiplicamos por sqrt(2). Lo añadimmos al gradiente
	gradiente += (fabs(Im(i, j) - Im(i-1, j-1)) 
		    + fabs(Im(i, j) - Im(i-1, j+1)) 
		    + fabs(Im(i, j) - Im(i+1, j-1)) 
		    + fabs(Im(i, j) - Im(i+1, j+1))) 
			/ sqrt(2);

	return gradiente;
}


void crea_energias(Imagen & Im, Imagen & En) //La Imagen En será donde guardaremos las energías
{
	int fils = En.fils();
	int cols = En.cols();

	for(int i = 0; i < fils; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			En(i, j) += calcula_gradiente(Im, i, j);
		}
	}
}
