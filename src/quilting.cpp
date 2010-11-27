#include <quilting.h>

void quilting(  Imagen & texR, Imagen & texG, Imagen & texB, 
		unsigned int tam_Bi, 
		Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB)
{
	unsigned int row = 0;
	unsigned int col = 0;
	int result = -1;
	
	unsigned int margenes = tam_Bi/3; //2*tam_Bi/6 == tam_Bi/3 == Bi+dos margenes
	unsigned int increment = tam_Bi + tam_Bi/6; //Bi+un margen
	
	Imagen BiR(tam_Bi+margenes, tam_Bi+margenes);
	Imagen BiG(tam_Bi+margenes, tam_Bi+margenes);
	Imagen BiB(tam_Bi+margenes, tam_Bi+margenes);
	
	//Creamos una imagen que contiene la suma de los componentes de color de la imagen de textura. De esta forma no hay que calcularlo cada vez.
	Imagen LumTex(texR.fils(), texR.cols(), 0);
	LumTex+=texR; LumTex+=texG; LumTex+=texB;
	
	//Llevamos a caso la primera inserción de Bi, la aleatoria.
	escogeBiAleatorio(BiR, BiG, BiB, texR, texG, texB);
	
	IMoutR.agrega(BiR, row, col);
	IMoutG.agrega(BiG, row, col);
	IMoutB.agrega(BiB, row, col);
	
	col += increment;
	
	
	
	
	
//	int cont = 0, max_iteraciones = 1; //Debugger
	
	while(1)
	{
		do
		{
			escogeBiAleatorio(BiR, BiG, BiB, texR, texG, texB);
			//escogeSiguienteBi(IMoutR, IMoutG, IMoutB, BiR, BiG, BiB, tam_Bi, texR, texG, texB, LumTex, row, col); //Modifica Bi R,G,B
		
			result = IMoutR.agrega(BiR, row, col);
			IMoutG.agrega(BiG, row, col);
			IMoutB.agrega(BiB, row, col);
			
			col += increment;
			
			std::cout<<"caso normal"<<std::endl;
			
//			cont++; if(cont == max_iteraciones) result=2; //Debugger
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
void escogeBiAleatorio(	Imagen & BiR, Imagen & BiG, Imagen & BiB, 
			Imagen & texR, Imagen & texG, Imagen & texB)
{
	unsigned int rowBi, colBi, tam_Bi = BiR.fils(); //Recordamos: Bi es cuadrado (y en este momento las columnas son 0)
	
	unsigned int tam_margen = tam_Bi/6;
	
	unsigned int max = texR.fils()-tam_Bi-2*tam_margen; //Tamaño Bi + 2 márgenes.
	rowBi = rand() % max+1; //valor aleatorio desde 0 hasta max
		
	max = texR.cols()-tam_Bi-2*tam_margen; 
	colBi = rand() % max+1;
	
	BiR.extrae(texR, rowBi, colBi);
	BiG.extrae(texG, rowBi, colBi);
	BiB.extrae(texB, rowBi, colBi);
}

//Modifica las variables Bi R,G,B segun el/los margen/es del último Bi añadido a Imout (posición de inicio: (row,col))
//Atención!!: En este caso, el tamaño de BiR, BiG y BiB ya incluye los márgenes !!
void escogeSiguienteBi(	Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB, 
			Imagen & BiR, Imagen & BiG, Imagen & BiB, unsigned int tam_Bi,
			Imagen & texR, Imagen & texG, Imagen & texB, Imagen & LumTex,
			unsigned int row, unsigned int col)
{
     //Declaramos y llenamos una imagen con la suma de colores del margen vertical. De esta forma no hay que calcularlo cada vez.
	Imagen LumMargenV(tam_Bi+tam_Bi/3, tam_Bi/6);
	Imagen margenV(LumMargenV.fils(), LumMargenV.cols()); //auxiliar
	
	margenV.extrae(IMoutR, row, col); LumMargenV+=margenV;
	margenV.extrae(IMoutG, row, col); LumMargenV+=margenV;
	margenV.extrae(IMoutB, row, col); LumMargenV+=margenV;
	
//	escribe((char*)"LumMargenV.png",LumMargenV);

     //Declaramos y llenamos una imagen con la suma de colores del margen vertical. De esta forma no hay que calcularlo cada vez.
	Imagen LumMargenH(tam_Bi/6, tam_Bi+tam_Bi/3);
	Imagen margenH(LumMargenH.fils(), LumMargenH.cols()); //auxiliar
	
	margenH.extrae(IMoutR, row, col); LumMargenH+=margenH;
	margenH.extrae(IMoutR, row, col); LumMargenH+=margenH;
	margenH.extrae(IMoutR, row, col); LumMargenH+=margenH;
	
	
	//imprime_pant(LumTex);
	std::cout<<"\n\n\n\n\n\n"<<std::endl;
	imprime_pant(LumMargenH);
	
//	escribe((char*)"LumMargenH.png",LumMargenH);
	
	
     //Primera parte: Obtenemos la energía del margen (forma de L) que más se parece al actual.
//	double min_energia = EnergiaMinimaMargenes(LumTex, LumMargenV, LumMargenH);
	
//	std::cout<<"La energía mínima es: "<<min_energia<<std::endl;
	
     //Segunda parte: a partir de la energía mínima obtenida, obtenemos las posiciones del inicio del nuevo Bi.
	unsigned int rowBi=0, colBi=0;
	
//	CoordenadasNuevasBi(LumTex, LumMargenV, LumMargenH, min_energia, rowBi, colBi);
	
     //Ahora ya podemos obtener Bi.
	BiR.extrae(texR, rowBi, colBi);
	BiG.extrae(texG, rowBi, colBi);
	BiB.extrae(texB, rowBi, colBi);
}

double compara(const Imagen& A,Imagen& B)
{
	if(A.dim[0]!=B.dim[0] || A.dim[1]!=B.dim[1])
	{
		std::cout<<"FATAL ERROR Compara: diferents dimensions"<<std::endl;exit(1);
	}
	unsigned int M=A.dim[0]*A.dim[1];
	double *a=A.datos,*b=B.datos,aux,totalEnerg=0;
	
	Imagen BB(B);
	
	
	for(unsigned int i=0;i<M;i++)
	{
		std::cout<<"It. "<<i<<" de "<<M<<std::endl;
		
		
		aux=a[i]-b[i];
		totalEnerg+=aux*aux;

		
		
		std::cout<<"Valores: "<<a[i]<<", "<<b[i]<<std::endl;
		std::cout<<"a[i]-b[i] = "<<aux<<std::endl;
		std::cout<<"ans^2 = "<<aux*aux<<std::endl;
		std::cout<<"-->en..."<<totalEnerg<<"\n\n"<<std::endl;
		
		
		if(i>=100){
		char c;
		scanf("%c\n", &c);
		}
		
		
		
		BB.datos[i] = 0;
		escribe((char*)"IM.png", BB);
	}
	return totalEnerg;
}

double compara(const Imagen& A,const Imagen& B,Imagen& Result)
{
	if(A.dim[0]!=B.dim[0] || A.dim[1]!=B.dim[1])
	{
		std::cout<<"FATAL ERROR Compara: diferents dimensions"<<std::endl;exit(1);
	}
	unsigned int M=A.dim[0]*A.dim[1];
	double *a=A.datos,*b=B.datos,*r=Result.datos,aux,totalEnerg=0;
	for(unsigned int i=0;i<M;i++)
	{
		aux=a[i]-b[i];
		aux*=aux;
		r[i]=aux;
		totalEnerg+=aux;
	}
	return totalEnerg;
}	
	
double EnergiaMinimaMargenes(Imagen & LumTex, Imagen & LumMargenV, Imagen & LumMargenH)
{
	Imagen margenV(LumMargenV.fils(), LumMargenV.cols()); //auxiliar
	Imagen margenH(LumMargenH.fils(), LumMargenH.cols()); //auxiliar
	
     //A continuación se buscarán los valores para la energía mínima para los márgenes
     	double min_energia = 1000000;
     	double valor; //Un auxiliar
     	unsigned int tam_BiMargenes = LumMargenV.fils();
     	
     	
     	
	escribe((char*)"comp1_a.png",LumMargenV);
     	escribe((char*)"comp2_a.png",LumMargenH);
     	Imagen temp(LumMargenV.fils(), LumMargenV.cols());
     	
     	
	for(unsigned int i=0; i<=LumTex.fils()-tam_BiMargenes; i++)
	{
		for(unsigned int j=0; j<=LumTex.cols()-tam_BiMargenes; j++)
		{
		std::cout<<"("<<i<<", "<<j<<")"<<std::endl;
			margenV.extrae(LumTex, i, j);
			//Se aplica la definición de energia de la práctica
			valor = compara(LumMargenV, margenV, temp);
			
			escribe((char*)"comp1_b.png",margenV);
			std::cout<<"valor1: "<<valor<<std::endl;
			
			
			
			
			margenH.extrae(LumTex, i, j);

			valor = compara(LumMargenH, margenH);
			
			escribe((char*)"comp2_b.png",margenH);
			std::cout<<"valor2: "<<valor<<std::endl;
			
			char r = 'n';
			scanf("%c\n", &r);
			
			
			if(valor < min_energia) min_energia = valor; //%%%Posible refactor: min_energia = min(valor, min_energia);
		}
	}
	return min_energia;
}
	
	
void CoordenadasNuevasBi(Imagen & LumTex, Imagen & LumMargenV, Imagen & LumMargenH, double min_energia, unsigned int & rowBi, unsigned int & colBi)
{
	double error = min_energia*0.1;
	
	Imagen margenV(LumMargenV.fils(), LumMargenV.cols()); //auxiliar
	Imagen margenH(LumMargenH.fils(), LumMargenH.cols()); //auxiliar
	
	double valor = 0.0; //auxiliar
	
     //Ahora que disponemos del rango de energias que aceptaremos (min_energia+-error), guardamos en una lista las posiciones de los márgenes aceptables.
	std::pair<unsigned int,unsigned int> p;
	std::vector< std::pair<unsigned int,unsigned int> > coordenadas;
	//std::vector<int> coordenadas;
	
	unsigned int tam_BiMargenes = LumMargenV.fils();
	
	for(unsigned int i=0; i<=LumTex.fils()-tam_BiMargenes; i++) //%%% <= ??
	{
		for(unsigned int j=0; j<=LumTex.cols()-tam_BiMargenes; j++) //%%% <= ??
		{
			margenV.extrae(LumTex, i, j);
			//Se aplica la definición de energia de la práctica
		//	margenV-=LumMargenV;
		//	margenV*=margenV;
		//	valor=margenV.sum();
			valor = compara(LumMargenV, margenV);
			
			margenH.extrae(LumTex, i, j);
		//	margenH-=LumMargenH;
		//	margenH*=margenH;
		//	valor+=margenH.sum();
			valor += compara(LumMargenH, margenH);
			
			
			if(  (valor <= min_energia+error) && (valor >= min_energia-error)  )
			{
				//Si el valor de energía es aceptable añadimos las coordenadas en dos posiciones seguidas del vector.
				//De esta manera, las posiciones pares del vector contendrán filas y las impares columnas.
				p.first = i;
				p.second = j;
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

