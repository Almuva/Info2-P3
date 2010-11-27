#ifndef QUILTING_H
#define QUILTING_H

#include <stdio.h>
#include <iostream> 
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <utility>

#include <Imagen.h>

void quilting(  Imagen & texR, Imagen & texG, Imagen & texB, 
		unsigned int tam_Bi, 
		Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB);

void escogeBiAleatorio( Imagen & BiR, Imagen & BiG, Imagen & BiB, 
			Imagen & texR, Imagen & texG, Imagen & texB);

void escogeSiguienteBi( Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB, 
			Imagen & BiR, Imagen & BiG, Imagen & BiB, unsigned int tam_Bi,
			Imagen & texR, Imagen & texG, Imagen & texB,  Imagen & LumTex,
			unsigned int row, unsigned int col);
			
double compara(const Imagen& A,const Imagen& B,Imagen& Result);

double compara(const Imagen& A,const Imagen& B);

double EnergiaMinimaMargenes(Imagen & LumTex, Imagen & LumMargenV, Imagen & LumMargenH);

void CoordenadasNuevasBi(Imagen & LumTex, Imagen & LumMargenV, Imagen & LumMargenH,
			 double min_energia, 
			 unsigned int & rowBi, unsigned int & colBi);

#endif
