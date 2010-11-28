#ifndef SEAMFINDING_H
#define SEAMFINDING_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <Imagen.h>
#include <Magick++.h>
#include <iostream> 

double menor (double a, double b, double c);

int minPosition (double a, double b, double c);

unsigned int smallestV(Imagen &cumulativeE);

unsigned int smallestH(Imagen &cumulativeE);

void backtrackV(Imagen &cE, int i, unsigned int j, Imagen &E);

void backtrackH(Imagen &cE, int i, unsigned int j, Imagen &E);

void find_v_seam(Imagen &E);

void find_h_seam(Imagen &E);

#endif
