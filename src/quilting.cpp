#include <quilting.h>

void quilting( Imagen & texR, Imagen & texG, Imagen & texB, 
		unsigned int tam_Bi, 
		Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB)
{
	unsigned int row = 0; //Posiciones de IMout donde insertamos el Bi
	unsigned int col = 0;
	
	int result = -1; //Guarda el return de la función Imagen::agrega().

	unsigned int margenes = tam_Bi/3; //2*tam_Bi/6 == tam_Bi/3 == Bi+dos margenes
	unsigned int increment = tam_Bi + tam_Bi/6; //Bi+un margen
	
     //Creamos la imagen Bi, que se irá modificando e insertando en IMout en cada iteración.
	Imagen BiR(tam_Bi+margenes, tam_Bi+margenes);
	Imagen BiG(tam_Bi+margenes, tam_Bi+margenes);
	Imagen BiB(tam_Bi+margenes, tam_Bi+margenes);
	
     //Creamos una imagen que contiene la suma de los componentes de color de la imagen de textura. De esta forma no hay que calcularlo cada vez.
	Imagen LumTex(texR.fils(), texR.cols(), 0);
	LumTex+=texR; LumTex+=texG; LumTex+=texB;
	
	
     //Llevamos a cabo la primera inserción de Bi, la aleatoria.
	escogeBiAleatorio(BiR, BiG, BiB, texR, texG, texB);
	
	IMoutR.agrega(BiR, row, col);
	IMoutG.agrega(BiG, row, col);
	IMoutB.agrega(BiB, row, col);
	
	col += increment;
	
//	int cont = 0, max_iteraciones = 7; //Debugger
	
     //El siguiente bucle va llenando IMout según los valores que va retornando la función Imagen::agrega(), en "result"
	while(1)
	{
		do //en el main nos aseguramos que Bi+margenes sea mayor estricto que tex. Esta primera iteración siempre se hará.
		{
			//Se obtiene el siguiente Bi a insertar en IMout.
			escogeSiguienteBi(IMoutR, IMoutG, IMoutB, texR, texG, texB, LumTex, row, col, tam_Bi, BiR, BiG, BiB);
		
			//Se inserta el Bi obtenido en IMout y se recoge el resultado
			result = IMoutR.agrega(BiR, row, col);
			IMoutG.agrega(BiG, row, col);
			IMoutB.agrega(BiB, row, col);
			
			col += increment;
			
//			std::cout<<"caso normal"<<std::endl;
			
//			cont++; if(cont == max_iteraciones) result=2; //Debugger
		}
		while(result == 0); //0==caso normal
		
		if(result == 1) //1==se llega al final de una fila
		{
			col = 0;
			row += increment;
			
//			std::cout<<"borde!!!"<<std::endl;
		}
		else if(result == 2){/*std::cout<<"esquina!!!!!!!!!"<<std::endl;*/ break;} //2==se llega al final de la última fila
	}
}

//Modifica las variables Bi R,G,B con un Bi cualquiera dentro de tex
void escogeBiAleatorio(	Imagen & BiR, Imagen & BiG, Imagen & BiB, 
			Imagen & texR, Imagen & texG, Imagen & texB)
{
	unsigned int rowBi, colBi, tam_Bi = BiR.fils(); //Recordamos: Bi es cuadrado
	
	unsigned int tam_margen = tam_Bi/6;
	
	unsigned int max = texR.fils()-tam_Bi-2*tam_margen; //Tamaño Bi + 2 márgenes.
	rowBi = rand() % max+1; //valor aleatorio desde 0 hasta max
		
	max = texR.cols()-tam_Bi-2*tam_margen; 
	colBi = rand() % max+1;
	
	BiR.extrae(texR, rowBi, colBi);
	BiG.extrae(texG, rowBi, colBi);
	BiB.extrae(texB, rowBi, colBi);
}

//Modifica las variables Bi R,G,B segun los márgenes del último Bi añadido a Imout (posición de inicio: (row,col))
//Atención!!: En este caso, el tamaño de BiR, BiG y BiB ya incluye los márgenes !!
void escogeSiguienteBi(	Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB,
			Imagen & texR, Imagen & texG, Imagen & texB, Imagen & LumTex,
			unsigned int row, unsigned int col, 
			unsigned int tam_Bi, Imagen & BiR, Imagen & BiG, Imagen & BiB)
{
     //Declaramos y llenamos una imagen con la suma de colores del margen vertical. De esta forma no hay que calcularlo cada vez.
	Imagen LumMargenV(tam_Bi+tam_Bi/3, tam_Bi/6, 0);
	Imagen margenV(LumMargenV.fils(), LumMargenV.cols(), 0); //auxiliar
	
	margenV.extrae(IMoutR, row, col); LumMargenV+=margenV;
	margenV.extrae(IMoutG, row, col); LumMargenV+=margenV;
	margenV.extrae(IMoutB, row, col); LumMargenV+=margenV;

     //Declaramos y llenamos una imagen con la suma de colores del margen horizontal. De esta forma no hay que calcularlo cada vez.
	Imagen LumMargenH(tam_Bi/6, tam_Bi+tam_Bi/3, 0);
	Imagen margenH(LumMargenH.fils(), LumMargenH.cols(), 0); //auxiliar
	
	margenH.extrae(IMoutR, row, col); LumMargenH+=margenH;
	margenH.extrae(IMoutG, row, col); LumMargenH+=margenH;
	margenH.extrae(IMoutB, row, col); LumMargenH+=margenH;
	
	
     //Primera parte: Obtenemos las energías de todas las comparaciones con el margen actual. Así no hay que recorrer la textura dos veces.
	//En cada posición del vector siguiente se guarda una energía y dos coordenadas. La energía es el resultante de la comparación de los...
	//... márgenes que empiezan en las coordenadas.
	vector<pair<double,pair<unsigned,unsigned> > >energias;
	
	GuardaEnergiasMargenes(LumTex, LumMargenV, LumMargenH, energias);
	
     //Segunda parte: a partir de la energía mínima obtenida, obtenemos las posiciones del inicio del nuevo Bi.
	unsigned int rowBi=0, colBi=0;
	
	CoordenadasNuevasBi(LumTex, LumMargenV, LumMargenH, energias, rowBi, colBi);
	
     //Ahora ya podemos obtener Bi.
	BiR.extrae(texR, rowBi, colBi);
	BiG.extrae(texG, rowBi, colBi);
	BiB.extrae(texB, rowBi, colBi);
	
     //Tercera parte: Si es conveniente, Bi se modifica con valores fuera de rango para los píxeles que no se quieren copiar a IMout
     //Esos valores fuera de rango se omitirán (no serán copiados) en la función Imagen:agrega()
	if(col!=0)
	{
		Imagen LumMargenVEscogido(margenV.fils(), margenV.cols());
		margenV.extrae(LumTex, rowBi, colBi);
		
		//Esta vez obtenemos la imagen resultante del cálculo de energías.
		compara(LumMargenV, margenV, LumMargenVEscogido);
		
		//Marcamos los valores fuera de rango
		marcaSegunSeamV(LumMargenVEscogido, BiR, BiG, BiB);
	}

	if(row!=0)
	{
		Imagen LumMargenHEscogido(margenH.fils(), margenH.cols());
		margenH.extrae(LumTex, rowBi, colBi);
		
		//Esta vez obtenemos la imagen resultante del cálculo de energías.
		compara(LumMargenH, margenH, LumMargenHEscogido);
		
		//Marcamos los valores fuera de rango
		marcaSegunSeamH(LumMargenHEscogido, BiR, BiG, BiB);
	}
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

//Calcula las energías de todos los márgenes en forma de L (dividido en dos márgenes, a su vez) en la textura y...
//...los guarda en el vector energías para su posterior procesamiento.
void GuardaEnergiasMargenes(Imagen & LumTex,Imagen & LumMargenV,Imagen & LumMargenH,
	vector<pair<double,pair<unsigned,unsigned> > >& energias)
{
	Imagen margenV(LumMargenV.fils(), LumMargenV.cols(), 0); //auxiliar
	Imagen margenH(LumMargenH.fils(), LumMargenH.cols(), 0); //auxiliar
	
	//Reservamos espacio para el vector de energías.
	energias.reserve(LumTex.fils()*LumTex.cols());
	
	double valor; //Un auxiliar
	unsigned int tam_BiMargenes = LumMargenV.fils();
	 	
	//precálculo de los límites para el for
	const unsigned int MaxFils=LumTex.fils()-tam_BiMargenes,  MaxCols=LumTex.cols()-tam_BiMargenes;

     //Recorremos la textura guardando los resultados de las energías.
	for(unsigned int i=0; i<=MaxFils; i++)
		for(unsigned int j=0; j<=MaxCols; j++)
		{
			//Obtenemos el margen correspondiente a la iteración
			margenV.extrae(LumTex, i, j);
			margenH.extrae(LumTex, i, j);
			
			//Se suman las energías de los dos márgenes
			valor = compara(LumMargenV, margenV);
			valor += compara(LumMargenH, margenH);
			
			//Guardamos la energía en el vector
			pair<double,pair<unsigned,unsigned> > energia (valor,pair<unsigned,unsigned>(i,j));
			energias.push_back(energia);
		}
		
	//Ordenamos el vector
	sort(energias.begin(),energias.end());
}
	
//A partir de las energías guardadas en el vector calcula un margen de error y retorna aletoriamente la posición de...
//... inicio de uno de los márgenes en forma de L que están dentro de ese error.
void CoordenadasNuevasBi(Imagen & LumTex, Imagen & LumMargenV, Imagen & LumMargenH,
	vector<pair<double,pair<unsigned,unsigned> > >& energias,
	unsigned int & rowBi, unsigned int & colBi)
{
	const double min_energia=energias[0].first; //Recordamos: El vector está ordenado.
	const double error = min_energia*0.1;
	
	unsigned int pos_validas = 0;
	
     //Como el vector energías está ordenado, establecemos la posición en la que sus energías posteriores dejen de ser válidas.
	while(energias[pos_validas].first-min_energia < error)
		pos_validas++;

     //Obtenemos las coordenadas aleatorias de entre las válidas.
	pair<unsigned,unsigned> escogidas = energias[rand() % pos_validas].second;
	rowBi = escogidas.first;
	colBi = escogidas.second;		
}

//Marca en Bi con valores fuera de rango las posiciones que están más a la izquierda que el seam que acumula la energía mínima en el margen vertical
void marcaSegunSeamV(Imagen & LumMargenV, Imagen & BiR, Imagen & BiG, Imagen & BiB)
{
	//Marcamos con valores fuera de rango el seam en la imagen LumMargenV
	find_v_seam(LumMargenV);
	
	unsigned int col;
	
	//Marcamos con valores fuera de rango en Bi, según lo obtenido en LumMargenV
	for(unsigned int row = 0; row < LumMargenV.fils(); row++)
	{
		col = 0;
		while(LumMargenV(row, col) < 10E20) //10E20: valor fuera de rango.
		{
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

//Marca en Bi con valores fuera de rango las posiciones que están más arriba que el seam que acumula la energía mínima en el margen horizontal
void marcaSegunSeamH(Imagen & LumMargenH, Imagen & BiR, Imagen & BiG, Imagen & BiB)
{
	//Marcamos con valores fuera de rango el seam en la imagen LumMargenH
	find_h_seam(LumMargenH);
	
	unsigned int row;
	
	//Marcamos con valores fuera de rango en Bi, según lo obtenido en LumMargenH
	for(unsigned int col = 0; col < LumMargenH.cols(); col++)
	{
		row = 0;
		while(LumMargenH(row, col) < 10E20) //10E20: valor fuera de rango.
		{
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

