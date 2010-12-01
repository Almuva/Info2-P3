#ifndef TRANSFER_H
#define TRANSFER_H


#include <iostream> 
#include <vector>
#include "seam_finding.h"
#include "Imagen.h"

void transferTexture(Imagen& TexR,Imagen& TexG,Imagen& TexB,
				 Imagen& TargetR,Imagen& TargetG,Imagen& TargetB,
				 unsigned tam_Bi,
				 float alpha);
				 
void EscogeBiAleatorioLum(Imagen & outR, Imagen & outG, Imagen & outB, 
					Imagen & LumTarg,
					Imagen & texR, Imagen & texG, Imagen & texB,
					Imagen & LumTex,
					Imagen & BiR, Imagen & BiG, Imagen & BiB);
					
int EscogeBiSiguienteLum(unsigned int row, unsigned int col, 
					Imagen & outR, Imagen & outG, Imagen & outB, 
					Imagen & LumTarg,
					Imagen & texR, Imagen & texG, Imagen & texB,
					Imagen & LumTex,
					Imagen & BiR, Imagen & BiG, Imagen & BiB,
					unsigned tam_Bi);
	
void CalculaErrorLumTex(Imagen & LumTarg,
				   Imagen & LumTex, 
				   unsigned int tam_Bi, 
				   vector<pair<double,pair<unsigned,unsigned> > >& energias);	
				   
void CalculaErrorLumMargenes(Imagen & LumTex,Imagen & LumMargenV,Imagen & LumMargenH,
	vector<pair<double,pair<unsigned,unsigned> > >& energias);
	
double quadError(const Imagen& A,Imagen& B);

void generaCoordenadasNuevasBi(vector<pair<double,pair<unsigned,unsigned> > >& luminanciasB,
						unsigned& rowBi, unsigned& colBi);

void generaCoordenadasNuevasBi(Imagen& LumTex, 
						Imagen& LumMargenV, Imagen& LumMargenH, 
						vector<pair<double,pair<unsigned,unsigned> > >& eMargen,
						vector<pair<double,pair<unsigned,unsigned> > >& eBi,
						unsigned int & rowBi, unsigned int & colBi);
						 
void ExtraeErrorLumTex(Imagen & LumTarg, Imagen & LumTex, unsigned tam_Bi,
	vector<pair<double,pair<unsigned,unsigned> > >& luminanciasB);

	
#endif
