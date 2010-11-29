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
#include <algorithm>
#include <vector>

#include "Imagen.h"
#include "seam_finding.h"

void quilting(  Imagen & texR, Imagen & texG, Imagen & texB, 
		unsigned int tam_Bi, 
		Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB);

void escogeBiAleatorio( Imagen & BiR, Imagen & BiG, Imagen & BiB, 
			Imagen & texR, Imagen & texG, Imagen & texB);

void escogeSiguienteBi(	Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB,
			Imagen & texR, Imagen & texG, Imagen & texB, Imagen & LumTex,
			unsigned int row, unsigned int col, 
			unsigned int tam_Bi, Imagen & BiR, Imagen & BiG, Imagen & BiB);
			
double compara(const Imagen& A,const Imagen& B,Imagen& Result);

double compara(const Imagen& A,const Imagen& B);

void GuardaEnergiasMargenes(Imagen & LumTex,Imagen & LumMargenV, Imagen & LumMargenH,
	vector<pair<double,pair<unsigned,unsigned> > >& energias);

void CoordenadasNuevasBi(Imagen & LumTex, Imagen & LumMargenV, Imagen & LumMargenH,
	vector<pair<double,pair<unsigned,unsigned> > >& energias, 
	unsigned int & rowBi, unsigned int & colBi);

void marcaSegunSeamV(Imagen & LumMargenV, Imagen & BiR, Imagen & BiG, Imagen & BiB);

void marcaSegunSeamH(Imagen & LumMargenH, Imagen & BiR, Imagen & BiG, Imagen & BiB);

#endif
