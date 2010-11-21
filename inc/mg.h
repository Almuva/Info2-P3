#ifndef MG_H
#define MG_H

double val_mayor_histograma(Imagen & Im, int x, int y);

double calcula_gradiente(Imagen & Im, unsigned int i, unsigned int j);

void crea_energias(Imagen & Im, Imagen & En);

#endif
