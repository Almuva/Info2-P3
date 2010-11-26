#include <quilting.h>

void quilting(Imagen & texR, Imagen & texG, Imagen & texB, unsigned int tam_Bi, Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB)
{
	unsigned int row = 0;
	unsigned int col = 0;
	int result = -1;
	
	unsigned int margenes = tam_Bi/3; //2*tam_Bi/6 == tam_Bi/3 == Bi+dos margenes
	unsigned int increment = tam_Bi + tam_Bi/6; //Bi+un margen
	
	Imagen BiR(tam_Bi+margenes, tam_Bi+margenes);
	Imagen BiG(tam_Bi+margenes, tam_Bi+margenes);
	Imagen BiB(tam_Bi+margenes, tam_Bi+margenes);
	
	escogeBiAleatorio(IMoutR, BiR, BiG, BiB, texR, texG, texB);
	
	IMoutR.agrega(BiR, row, col);
	IMoutG.agrega(BiG, row, col);
	IMoutB.agrega(BiB, row, col);
	
//	int cont = 0; //Debugger
	
	while(1)
	{
		do
		{
			escogeBiAleatorio(IMoutR, BiR, BiG, BiB, texR, texG, texB);
			//escogeSiguienteBi(IMoutR, IMoutG, IMoutB, BiR, BiG, BiB, tam_Bi, texR, texG, texB, row, col); //Modifica Bi R,G,B
		
			result = IMoutR.agrega(BiR, row, col);
			IMoutG.agrega(BiG, row, col);
			IMoutB.agrega(BiB, row, col);
			
			col += increment;
			
			std::cout<<"caso normal"<<std::endl;
			
//			cont++; if(cont == 2) result=2; //Debugger
		}
		while(result == 0); //0==caso normal
		
		if(result == 1) //1==se llega al final de una fila
		{
			col = 0;
			row += increment;
			
			std::cout<<"borde!!!"<<std::endl;
		}
		else if(result == 2){std::cout<<"esquina!!!!!!!!!"<<std::endl; break;} //2==se llega al final de la última fila
	}
	
	
}

//Modifica las variables Bi R,G,B con un Bi cualquiera dentro de tex
void escogeBiAleatorio(Imagen & IMoutR, 
			Imagen & BiR, Imagen & BiG, Imagen & BiB, 
			Imagen & texR, Imagen & texG, Imagen & texB)
{
	unsigned int rowBi, colBi, tam_Bi = BiR.fils(); //Recordamos: Bi es cuadrado (y en este momento las columnas son 0)
	
	unsigned int tam_margen = tam_Bi/6;
	
	unsigned int max = texR.fils()-tam_Bi-2*tam_margen; //Tamaño Bi + 2 márgenes.
	rowBi = rand() % max+1; //valor aleatorio desde 0 hasta max
		
	max = texR.cols()-tam_Bi-2*tam_margen; 
	colBi = rand() % max+1;
	
	texR.extrae(rowBi, colBi, BiR);
	texG.extrae(rowBi, colBi, BiG);
	texB.extrae(rowBi, colBi, BiB);
}

