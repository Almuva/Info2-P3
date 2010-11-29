#include <seam_finding.h>

using namespace std; 
using namespace Magick; 

// find min out of 3 integer values
double menor (double a, double b, double c){
	
	if (b<=a && b<=c)	return b; //by default
	else if (a<=b && a<=c)	return a;
	else	return c;
}

// find the position of the lower int: -1, 0, 1
int minPosition (double a, double b, double c){
	
	if (b<=a && b<=c) 	return 0;
	else if (a<=b && a<=c) 	return -1;
	else			return 1;
}

// finds the horizontal coordinate of the pixel in the last row with minimum value
unsigned int smallestV(Imagen &cumulativeE){

	int c = cumulativeE.cols()-1; // last column
	
	unsigned int v; 

	int min = 10E8; // valor de inicio

	for (unsigned int i=0; i<cumulativeE.fils(); i++){
		//if (i>330)cout<<i<<":"<<cumulativeE(i,c)<<endl;
		if (cumulativeE(i,c)<min){
			v = i;
			min = cumulativeE(i,c);
		}
 	}
 	//cout<<"D"<<v<<endl;
	return v;
}

unsigned int smallestH(Imagen &cumulativeE){

	int f = cumulativeE.fils() -1; // last row
	
	unsigned int h; 

	int min = 10E8; // valor de inicio

	for (unsigned int j=0; j<cumulativeE.cols(); j++){
		if (cumulativeE(f,j)<min){
			h = j;
			min = cumulativeE(f,j);
		}
 	}
	return h;
}

// BACKTRACK
void backtrackV(Imagen &cE, int i, unsigned int j, Imagen & E){

	//cout<<"backtrackV: "<<i<<", "<<j<<endl;
	if (i >= 0){
		// Aj = incremento de j 
		int Aj = minPosition(cE(i-1,j-1), cE(i-1,j), cE(i-1,j+1));
		int f = i-1;
		unsigned int c = j + Aj;
		backtrackV(cE, f, c, E);
		E(f, c) = 10E20;
	}	
}

// @ seams: seam de posicions de menor energia
// @ energies: e(HoG)
void find_v_seam(Imagen & E){
	
	Imagen cE(E); //matriz de valores minimos acumulados

	// the first step is to traverse the image from the second row to the last row and 
	//compute the CUMULATIVE MINIMUM ENERGY M for all possible connected seams for each entry (i, j)
	for (unsigned int i=1; i<cE.fils(); i++){
		for (unsigned int j=0; j<cE.cols(); j++){
			
			double suma =  cE(i,j) + menor(cE(i-1,j-1), cE(i-1,j), cE(i-1,j+1));
			cE(i,j) = suma;
		}
	}
	//escribe((char*)"acumuladas.jpg", e);
	unsigned int col = smallestH(cE);
	
	E(cE.fils()-1, col) = 10E20;
	backtrackV(cE, cE.fils()-1, col, E);
}

///////////////////////////////////////////////////////////////////////

// BACKTRACK
void backtrackH(Imagen &cE, int i, unsigned int j, Imagen & E){

	//cout<<"bt"<<i<<endl;
	if (i >= 0){
		int c = i-1;
		// Aj = incremento de j 
	//cout<<"aj:"<<endl;
	//cout<<"min"<<cE(j-1,c)<<":"<<cE(j,c)<<":"<<cE(j+1,c)<<endl;
		int Aj = minPosition(cE(j-1,c), cE(j,c), cE(j+1,c));
	//	cout<<Aj<<endl;
		unsigned int f = j + Aj;
		backtrackH(cE, c, f, E);
		E(f, c) = 10E20;
	}	
}

// @ seams: seam de posicions de menor energia
// @ energies: e(HoG)
void find_h_seam(Imagen &E){
	
	Imagen cE(E); //matriz de valores minimos acumulados
	// copy first row of energies
	// done!

	// the first step is to traverse the image from the second row to the last row and 
	//compute the CUMULATIVE MINIMUM ENERGY M for all possible connected seams for each entry (i, j)
	for (unsigned int j=1; j<cE.cols(); j++){
		for (unsigned int i=0; i<cE.fils(); i++){
				
			double suma =  cE(i,j) + menor(cE(i-1,j-1), cE(i,j-1), cE(i+1,j-1));
			//cout<<e(i,j)<<"-"<<menor(e(i-1,j-1), e(i-1,j), e(i-1,j+1))<<">"<< suma <<endl;
			cE(i,j) = suma;
		}
	}
	//e.recorta(0,255);
	//escribe("acumuladasH.jpg", e);
	unsigned int row = smallestV(cE);
	
	E(row, cE.cols()-1) = 10E20;
	backtrackH(cE, row, cE.cols()-1, E);
}

