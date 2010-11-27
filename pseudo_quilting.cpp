//------------------------PSEUDO QUILTING PARA CONSEGUIR IMAGEN 2.B (TB SIRVE PARA 2.A))------------------------\\

//Idea: Se podría crear una clase ImagenColor que contenga tres imagenes (R, G, B)...

#include "seam_finding.h"

Al final de quilting()
{
	if(col!=0)
	{
		Imagen LumMargenVEscogido(margenV.fils(), margenV.cols());
		margenV.extrae(LumTex, rowBi, colBi);
		
		//Esta vez obtenemos la imagen resultante del cálculo de energías.
		compara(LumMargenV, margenV, LumMargenVEscogido);
		
		marcaSegunSeamV(LumMargenVEscogido, BiR, BiG, BiB);
	}
	
	if(row!=0)
	{
		Imagen LumMargenHEscogido(margenH.fils(), margenH.cols());
		margenH.extrae(LumTex, rowBi, colBi);
		
		//Esta vez obtenemos la imagen resultante del cálculo de energías.
		compara(LumMargenH, margenH, LumMargenHEscogido);
		
		marcaSegunSeamH(LumMargenHEscogido, BiR, BiG, BiB);
	}


}


void marcaSegunSeamV(Imagen & LumMargenV, Imagen & BiR, Imagen & BiG, Imagen & BiB)
{
     //Marcamos con valores fuera de rango el seam en la imagen LumMargenVEscogido
	find_v_seam(LumMargenV);
	
	unsigned int col = 0;
	
	for(unsigned int row = 0; row < LumMargenV.fils(); row++)
	{
		while(LumMargenV(row, col) < 10E20) //10E20: valor fuera de rango.
		{
			BiR(row, col) = 10E20;
			BiG(row, col) = 10E20;
			BiB(row, col) = 10E20;
			col++;
		/*	
			if(col == LumMargenV.cols()) //Debugger
			{
				fprintf(stderr,"En ''marcaSegunSeamV()'' se pasa de largo!!!\n");
				exit(1);
			}
		*/
		}
	}
}

void marcaSegunSeamH(Imagen & LumMargenH, Imagen & BiR, Imagen & BiG, Imagen & BiB)
{
     //Marcamos con valores fuera de rango el seam en la imagen LumMargenVEscogido
	find_h_seam(LumMargenH);
	
	unsigned int row = 0;
	
	for(unsigned int col = 0; col < LumMargenV.cols(); col++)
	{
		while(LumMargenV(row, col) < 10E20) //10E20: valor fuera de rango.
		{
			BiR(row, col) = 10E20;
			BiG(row, col) = 10E20;
			BiB(row, col) = 10E20;
			row++;
		/*	
			if(row == LumMargenV.fils()) //Debugger
			{
				fprintf(stderr,"En ''marcaSegunSeamH()'' se pasa de largo!!!\n");
				exit(1);
			}
		*/
		}
	}
}


