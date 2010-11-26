#ifndef QUILTING_H
#define QUILTING_H

#include <stdio.h>
#include <iostream> 
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include <Imagen.h>

void quilting(Imagen & texR, Imagen & texG, Imagen & texB, unsigned int tam_Bi, Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB);

void escogeBiAleatorio(Imagen & IMoutR, 
			Imagen & BiR, Imagen & BiG, Imagen & BiB, 
			Imagen & texR, Imagen & texG, Imagen & texB);

#endif
