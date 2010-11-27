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

void backtrackV(Imagen &cE, int i, unsigned int j);

void backtrackH(Imagen &cE, int i, unsigned int j);

void find_v_seam(Imagen &e);

void find_h_seam(Imagen &e);

#endif
