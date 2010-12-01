#ifndef TRANSFER_H
#define TRANSFER_H


#include <iostream> 
#include <vector>
#include <map>
#include "seam_finding.h"
#include "Imagen.h"

void transferTexture(Imagen& AR,Imagen& AG,Imagen& AB,Imagen& BR,Imagen& BG,Imagen& BB,unsigned tam_Bi);
double compara(Imagen& A,unsigned iniciAx,unsigned iniciAy,Imagen& B,
	unsigned iniciBx,unsigned iniciBy,Imagen& Result);
#endif
