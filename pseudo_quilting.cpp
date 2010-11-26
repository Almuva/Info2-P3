//------------------------PSEUDO QUILTING PARA CONSEGUIR IMAGEN 2.B (TB SIRVE PARA 2.A))------------------------\\

//Idea: Se podría crear una clase ImagenColor que contenga tres imagenes (R, G, B)...

#include <vector>
#include <utility>

//Modifica las variables Bi R,G,B segun el/los margen/es del último Bi añadido a Imout (posición de inicio: (row,col))
//Atención!!: En este caso, el tamaño de BiR, BiG y BiB ya incluye los márgenes !!
void escogeSiguienteBi(Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB, 
		Imagen & BiR, Imagen & BiG, Imagen & BiB, unsigned int tam_Bi,
		Imagen & texR, Imagen & texG, Imagen & texB,
		unsigned int tam_Bi, unsigned int row, unsigned int col)
{
     //Creamos una imagen que contiene la suma de los componentes de color de la imagen de textura. De esta forma no hay que calcularlo cada vez.
	Imagen LumTex(texR.fils(), texR.cols(), 0.0);//%%% fuera de aquí!!
	LumTex+=texR; LumTex+=texG; LumTex+=texB;//%%%(tb)
	

     //Declaramos y llenamos una imagen con la suma de colores del margen vertical. De esta forma no hay que calcularlo cada vez.
	Imagen LumMargenV(tam_Bi+tam_Bi/3, tam_Bi/6);
	Imagen margenV(LumMargenV.fils(), LumMargenV.cols()); //auxiliar
	
	margenV.extrae(BiR, row, col); LumMargenV+=margenV;
	margenV.extrae(BiG, row, col); LumMargenV+=margenV;
	margenV.extrae(BiB, row, col); LumMargenV+=margenV;

     //Declaramos y llenamos una imagen con la suma de colores del margen vertical. De esta forma no hay que calcularlo cada vez.
	Imagen LumMargenH(tam_Bi/6, tam_Bi+tam_Bi/3);
	Imagen margenH(LumMargenH.fils(), LumMargenH.cols()); //auxiliar
	
	margenH.extrae(BiR, row, col); LumMargenH+=margenH;
	margenH.extrae(BiG, row, col); LumMargenH+=margenH;
	margenH.extrae(BiB, row, col); LumMargenH+=margenH;
	
     //Primera parte: Obtenemos la energía del margen (forma de L) que más se parece al actual.
	double min_energia = EnergiaMinimaMargenes(LumTex, LumMargenV, LumMargenH);
	
     //Segunda parte: a partir de la energía mínima obtenida, obtenemos las posiciones del inicio del nuevo Bi.
	unsigned int rowBi, colBi;
	
	CoordenadasNuevasBi(LumTex, LumMargen, min_energia, rowBi, colBi);
	
     //Ahora ya podemos obtener Bi.
	BiR.extrae(IMoutR, rowBi, colBi);
	BiG.extrae(IMoutG, rowBi, colBi);
	BiB.extrae(IMoutB, rowBi, colBi);
}	
	
	

double EnergiaMinimaMargenes(Imagen & LumTex, Imagen & LumMargenV, Imagen & LumMargenH)
{
	Imagen margenV(LumMargenV.fils(), LumMargenV.cols()); //auxiliar
	Imagen margenH(LumMargenH.fils(), LumMargenH.cols()); //auxiliar
	
     //A continuación se buscarán los valores para la energía mínima para los márgenes
     	double min_energia = 1000000;
     	double valor; //Un auxiliar
     	unsigned int tam_BiMargenes = LumMargenV.fils();
     	
	for(int i=0, i<=LumTex.fils()-tam_BiMargenes, i++) //%%% <= ??
	{
		for(int j=0, j<=LumTex.cols()-tam_BiMargenes, j++) //%%% <= ??
		{
			margenV.extrae(LumTex, i, j);
			//Se aplica la definición de energia de la práctica
			margenV-=LumMargenV;
			margenV*=margenV;
			valor=margenV.sum();
		//	valor = compara(LumMargenV, margenV);
			
			margenH.extrae(LumTex, i, j);
			margenH-=LumMargenH;
			margenH*=margenH;
			valor+=margenH.sum();
		//	valor += compara(LumMargenH, margenH);
			
			if(valor < min_energia) min_energia = valor; //%%%Posible refactor: min_energia = min(valor, min_energia);
		}
	}
	return min_energia;
}
	
	
void CoordenadasNuevasBi(Imagen & LumTex, Imagen & LumMargen, double min_energia, unsigned int & rowBi, unsigned int & colBi)
{
	double error = min_energia*0.1;
	
     //Ahora que disponemos del rango de energias que aceptaremos (min_energia+-error), guardamos en una lista las posiciones de los márgenes aceptables.
	std::pair<unsigned int,unsigned int> p;
	std::vector<pair<unsigned int,unsigned int>> coordenadas;
	//std::vector<int> coordenadas;
	
	unsigned int tam_BiMargenes = LumMargenV.fils();
	
	for(int i=0, i<=LumTex.fils()-tam_BiMargenes, i++) //%%% <= ??
	{
		for(int j=0, j<=LumTex.cols()-tam_BiMargenes, j++) //%%% <= ??
		{
			margenV.extrae(LumTex, i, j);
			//Se aplica la definición de energia de la práctica
			margenV-=LumMargenV;
			margenV*=margenV;
			valor=margenV.sum();
		//	valor = compara(LumMargenV, margenV);
			
			margenH.extrae(LumTex, i, j);
			margenH-=LumMargenH;
			margenH*=margenH;
			valor+=margenH.sum();
		//	valor += compara(LumMargenH, margenH);
			
			
			if(  (valor <= min_energia+error) && (valor >= min_energia-error)  )
			{
				//Si el valor de energía es aceptable añadimos las coordenadas en dos posiciones seguidas del vector.
				//De esta manera, las posiciones pares del vector contendrán filas y las impares columnas.
				p.first(i);
				p.second(j);
				coordenadas.push_back(p);
			//	coordenadas.push_back(i);
			//	coordenadas.push_back(j);
			}
		}
	}
	
     //Ya casi estamos. Ahora hay que escoger una posición de las que hay en el vector, aleatoriamente.
	//int pos_escogida = rand() % (coordenadas.size()/2); //1:el vector siempre será par. Dividido entre 2 siempre dará entero.
							    //2:seguidamente se entenderá porqué se divide entre 2.
	//rowBi = coordenadas.at(pos_escogida*2); //Por eso antes se divide entre 2: queremos obtener la posición de una fila! (la columna irá justo después)
	//colBi = coordenadas.at(pos_escogida*2+1);
	
	p = coordenadas.at(rand() % coordenadas.size());
							    
	rowBi = p.first;
	colBi = p.second;		
}





