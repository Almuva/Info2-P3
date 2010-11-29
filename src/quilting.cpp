#include <quilting.h>

void quilting( Imagen & texR, Imagen & texG, Imagen & texB, 
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
	
	int cont = 0, max_iteraciones = 7; //Debugger
	
	 //El siguiente bucle va llenando IMout según los valores que va retornando la función Imagen::agrega(), en "result"
	while(1)
	{
		do //en el main nos aseguramos que Bi+margenes sea mayor estricto que tex. Esta primera iteración siempre se hará.
		{
			//Se obtiene el siguiente Bi a insertar en IMout.
			escogeSiguienteBi(IMoutR, IMoutG, IMoutB, texR, texG, texB, LumTex, row, col, tam_Bi, BiR, BiG, BiB);
		
			result = IMoutR.agrega(BiR, row, col);
			IMoutG.agrega(BiG, row, col);
			IMoutB.agrega(BiB, row, col);
			
			col += increment;
			
			//std::cout<<"caso normal"<<std::endl;
			
			cont++; if(cont == max_iteraciones) result=2; //Debugger
		}
		while(result == 0); //0==caso normal
		
		if(result == 1) //1==se llega al final de una fila
		{
			col = 0;
			row += increment;
			
			//std::cout<<"borde!!!"<<std::endl;
		}
		else if(result == 2){/*std::cout<<"esquina!!!!!!!!!"<<std::endl;*/ break;} //2==se llega al final de la última fila
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
			Imagen & texR, Imagen & texG, Imagen & texB, Imagen & LumTex,
			unsigned int row, unsigned int col, 
			unsigned int tam_Bi, Imagen & BiR, Imagen & BiG, Imagen & BiB)
{
	 //Declaramos y llenamos una imagen con la suma de colores del margen vertical. De esta forma no hay que calcularlo cada vez.
	Imagen LumMargenV(tam_Bi+tam_Bi/3, tam_Bi/6, 0);
	Imagen margenV(LumMargenV.fils(), LumMargenV.cols()); //auxiliar
	
	margenV.extrae(IMoutR, row, col); LumMargenV+=margenV;	
	margenV.extrae(IMoutG, row, col); LumMargenV+=margenV;
	margenV.extrae(IMoutB, row, col); LumMargenV+=margenV;

	 //Declaramos y llenamos una imagen con la suma de colores del margen vertical. De esta forma no hay que calcularlo cada vez.
	Imagen LumMargenH(tam_Bi/6, tam_Bi+tam_Bi/3, 0);
	Imagen margenH(LumMargenH.fils(), LumMargenH.cols()); //auxiliar
	
	margenH.extrae(IMoutR, row, col); LumMargenH+=margenH;
	margenH.extrae(IMoutG, row, col); LumMargenH+=margenH;
	margenH.extrae(IMoutB, row, col); LumMargenH+=margenH;
	
	
	 //Primera parte: Obtenemos la energía del margen (forma de L) que más se parece al actual.
	//double min_energia = EnergiaMinimaMargenes(LumTex, LumMargenV, LumMargenH);/*refactored*/
	vector<pair<double,pair<unsigned,unsigned> > >energias;
	EnergiaMinimaMargenes(LumTex, LumMargenV, LumMargenH, energias);
	
	 //Segunda parte: a partir de la energía mínima obtenida, obtenemos las posiciones del inicio del nuevo Bi.
	unsigned int rowBi=0, colBi=0;
	
	CoordenadasNuevasBi(LumTex, LumMargenV, LumMargenH, energias, rowBi, colBi);
	
	 //Ahora ya podemos obtener Bi.
	BiR.extrae(texR, rowBi, colBi);
	BiG.extrae(texG, rowBi, colBi);
	BiB.extrae(texB, rowBi, colBi);
/*	
	if(col!=0)
	{
		Imagen LumMargenVEscogido(margenV.fils(), margenV.cols());
		margenV.extrae(LumTex, rowBi, colBi);
		
		//Esta vez obtenemos la imagen resultante del cálculo de energías.
		compara(LumMargenV, margenV, LumMargenVEscogido);
		
		marcaSegunSeamV(LumMargenVEscogido, BiR, BiG, BiB);
	}

	if(row!=0)
	{
		Imagen LumMargenHEscogido(margenH.fils(), margenH.cols());
		margenH.extrae(LumTex, rowBi, colBi);
		
		//Esta vez obtenemos la imagen resultante del cálculo de energías.
		compara(LumMargenH, margenH, LumMargenHEscogido);
		
		marcaSegunSeamH(LumMargenHEscogido, BiR, BiG, BiB);
	}
*/
	
	escribe((char*)"Bi_a_agregar.png", BiR, BiG, BiB);
}

//Aplica el significado de "energía" aplicado en la práctica y la retorna.
//Las dos imágenes serán siempre dos márgenes.
double compara(const Imagen& A,Imagen& B)
{
	if(A.dim[0]!=B.dim[0] || A.dim[1]!=B.dim[1])
	{
		std::cout<<"FATAL ERROR Compara(): diferentes dimensiones"<<std::endl;exit(1);
	}
	unsigned int M=A.dim[0]*A.dim[1];
	double *a=A.datos,*b=B.datos,aux,totalEnerg=0;
	
	for(unsigned int i=0;i<M;i++)
	{	
		aux=a[i]-b[i];
		totalEnerg+=aux*aux;
	}
	return totalEnerg;
}

//Aplica el significado de "energía" aplicado en la práctica y la retorna.
//Además, modifica por parámetro una Imagen con el resultado
//Las dos imágenes serán siempre dos márgenes.
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

//Busca todos los márgenes en forma de L (dividido en dos márgenes, a su vez) en la textura y...
//...retorna la energía del margen L que mejor se adapta a LumMargenV y LumMargenH.
double EnergiaMinimaMargenes(Imagen & LumTex,Imagen & LumMargenV,Imagen & LumMargenH,
	vector<pair<double,pair<unsigned,unsigned> > >& energias)
{
	Imagen margenV(LumMargenV.fils(), LumMargenV.cols()); //auxiliar
	Imagen margenH(LumMargenH.fils(), LumMargenH.cols()); //auxiliar
	
	//A continuación se buscarán los valores para la energía mínima para los márgenes
	//double min_energia = 1000000;/*refactored ! unused*/
		energias.reserve(LumTex.fils()*LumTex.cols());
	
		double valor; //Un auxiliar
		unsigned int tam_BiMargenes = LumMargenV.fils();
	 	
	//precalculo
	const unsigned int MaxFils=LumTex.fils()-tam_BiMargenes,MaxCols=LumTex.cols()-tam_BiMargenes;

	for(unsigned int i=0; i<=MaxFils; i++)
		for(unsigned int j=0; j<=MaxCols; j++)
		{
			//Obtenemos el margen correspondiente a la iteración
			margenV.extrae(LumTex, i, j);
			margenH.extrae(LumTex, i, j);
			
			//Se suman las energías de los dos márgenes
			valor = compara(LumMargenV, margenV);
			valor += compara(LumMargenH, margenH);
			
			//Si la energía obtenida es menor a la que guardamos, guardamos ésa.
			//min_energia = min(valor, min_energia);/*refactored*/
			pair<double,pair<unsigned,unsigned> > energia (valor,pair<unsigned,unsigned>(i,j));
			energias.push_back(energia);
		}
	sort(energias.begin(),energias.end());
	return energias[0].first;
}
	
//A partir de min_energia calcula un margen de error y retorna aletoriamente la posición de...
//... inicio de uno de los márgenes en forma de L que están dentro de ese error.
void CoordenadasNuevasBi(Imagen & LumTex, Imagen & LumMargenV, Imagen & LumMargenH,
	vector<pair<double,pair<unsigned,unsigned> > >& energias,
	unsigned int & rowBi, unsigned int & colBi)
{
	//double error = energias[0].first*0.1;
	const double min_energia=energias[0].first,error = min_energia*0.1;
	
	Imagen margenV(LumMargenV.fils(), LumMargenV.cols()); //auxiliar
	Imagen margenH(LumMargenH.fils(), LumMargenH.cols()); //auxiliar
	
	//double valor = 0.0; //auxiliar
	unsigned int valids = 0;

	while(energias[valids].first-min_energia < error)
		valids++;

	pair<unsigned,unsigned> triat = energias[rand() % valids].second;
	rowBi = triat.first;
	colBi = triat.second;

	 //Ahora que disponemos del rango de energias que aceptaremos (min_energia+-error), guardamos en una lista las posiciones de los márgenes aceptables. /*refactored*/
	/*std::pair<unsigned int,unsigned int> p;
	std::vector< std::pair<unsigned int,unsigned int> > coordenadas;
	
	unsigned int tam_BiMargenes = LumMargenV.fils();
	
	for(unsigned int i=0; i<=LumTex.fils()-tam_BiMargenes; i++) //%%% <= ??
	{
		for(unsigned int j=0; j<=LumTex.cols()-tam_BiMargenes; j++) //%%% <= ??
		{
			//Obtenemos el margen correspondiente a la iteración
			margenV.extrae(LumTex, i, j);
			margenH.extrae(LumTex, i, j);
			
			//Se suman las energías de los dos márgenes
			valor = compara(LumMargenV, margenV);
			valor += compara(LumMargenH, margenH);
			
			//Si el valor de energía es aceptable añadimos las coordenadas al vector de pairs.
			if( (valor <= min_energia+error) && (valor >= min_energia-error) )
			{
				p.first = i;
				p.second = j;
				coordenadas.push_back(p);
			}
		}
	}*/

	//Ya casi estamos. Ahora hay que escoger una posición (pair) de las que hay en el vector, aleatoriamente.
	/*if(coordenadas.size()==0)
		std::cout<<"CoordenadasNuevasBi: no hay margenes aceptables!"<<std::endl;
	else
		p = coordenadas.at(rand() % coordenadas.size());

	//(rowBi y colBi se modifican por parámetro)			
	rowBi = p.first;
	colBi = p.second;*/		
}

void marcaSegunSeamV(Imagen & LumMargenV, Imagen & BiR, Imagen & BiG, Imagen & BiB)
{
	 //Marcamos con valores fuera de rango el seam en la imagen LumMargenVEscogido
	find_v_seam(LumMargenV);
	
	//imprime_pant(LumMargenV);
	
	unsigned int col;
	
	for(unsigned int row = 0; row < LumMargenV.fils(); row++)
	{
		col = 0;
		while(LumMargenV(row, col) < 10E20) //10E20: valor fuera de rango.
		{
		//std::cout<<"Marcando V seam: "<<row<<", "<<col<<std::endl;
			BiR(row, col) = 10E20;
			BiG(row, col) = 10E20;
			BiB(row, col) = 10E20;
			col++;
			
			if(col == LumMargenV.cols()) //Debugger
			{
				fprintf(stderr,"En ''marcaSegunSeamV()'' se pasa de largo!!!\n");
				exit(1);
			}
		
		}
	}
}

void marcaSegunSeamH(Imagen & LumMargenH, Imagen & BiR, Imagen & BiG, Imagen & BiB)
{
	 //Marcamos con valores fuera de rango el seam en la imagen LumMargenVEscogido
	find_h_seam(LumMargenH);
	
	//imprime_pant(LumMargenH);
	
	unsigned int row;
	
	for(unsigned int col = 0; col < LumMargenH.cols(); col++)
	{
		row = 0;
		while(LumMargenH(row, col) < 10E20) //10E20: valor fuera de rango.
		{
		//std::cout<<"Marcando H seam: "<<row<<", "<<col<<std::endl;
			BiR(row, col) = 10E20;
			BiG(row, col) = 10E20;
			BiB(row, col) = 10E20;
			row++;
			
			if(row == LumMargenH.fils()) //Debugger
			{
				fprintf(stderr,"En ''marcaSegunSeamH()'' se pasa de largo!!!\n");
				exit(1);
			}
		
		}
	}
}

