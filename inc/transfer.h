#ifndef TRANSFER_H
#define TRANSFER_H


#include <iostream> 
#include <vector>
#include "seam_finding.h"

void transfer(  Imagen & texR, Imagen & texG, Imagen & texB, 
		unsigned int tam_Bi, 
		Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB);
#endif
