#include <transfer.h>
#include <quilting.h>

void transferTexture(Imagen& TexR,Imagen& TexG,Imagen& TexB,
				 Imagen& TargetR,Imagen& TargetG,Imagen& TargetB,
				 unsigned tam_Bi,
				 float alpha)
{
	// texture backup
	Imagen outR(TargetR.fils(), TargetR.cols());
	Imagen outG(TargetB.fils(), TargetB.cols());
	Imagen outB(TargetG.fils(), TargetG.cols());
	
	
	// Luminancias
	Imagen LumTex(TexR.fils(), TexR.cols());
	Imagen LumTarg(TargetR.fils(), TargetR.cols());
	
	Imagen imagenAuxiliar;
	
	//cada luminancia es una imagen a parte que guarda la luminancia de la imagen de entrada
	imagenAuxiliar=TexR; imagenAuxiliar*=0.30; LumTex=imagenAuxiliar;
	imagenAuxiliar=TexG; imagenAuxiliar*=0.59; LumTex+=imagenAuxiliar;
	imagenAuxiliar=TexB; imagenAuxiliar*=0.11; LumTex+=imagenAuxiliar;
	
	imagenAuxiliar=TargetR; imagenAuxiliar*=0.30; LumTarg=imagenAuxiliar;
	imagenAuxiliar=TargetG; imagenAuxiliar*=0.59; LumTarg+=imagenAuxiliar;
	imagenAuxiliar=TargetB; imagenAuxiliar*=0.11; LumTarg+=imagenAuxiliar;
	
// 	escribe("L1.png",LumTex);
// 	escribe("L2.png",LumTarg);
/// awesome edu! la formula es perfecta!
	
	
	unsigned int row = 0; //Posiciones de IMout donde insertamos el Bi
	unsigned int col = 0;
	
 	int result = -1; //Guarda el return de la función Imagen::agrega().

	unsigned int margenes = tam_Bi/3; //2*tam_Bi/6 == tam_Bi/3 == Bi+dos margenes
	unsigned int increment = tam_Bi + tam_Bi/6; //Bi+un margen
	
     //Creamos la imagen Bi, que se irá modificando e insertando en outRGB en cada iteración.
	Imagen BiR(tam_Bi+margenes, tam_Bi+margenes);
	Imagen BiG(tam_Bi+margenes, tam_Bi+margenes);
	Imagen BiB(tam_Bi+margenes, tam_Bi+margenes);
	
	//Llevamos a cabo la primera inserción de Bi, la aleatoria.
	// el bi cogido de la textura no tiene que respetar las reglas de la sintesis
	// pero si del mapeo de textura por luminancia
 	EscogeBiAleatorioLum(outR, outG, outB, 
					 LumTarg,
					 TexR, TexG, TexB, 
					 LumTex,
					 BiR, BiG, BiB);
	

	// 	col += increment;
	
	int cont = 0, max_iteraciones = 7; //Debugger
	
     //El siguiente bucle va llenando IMout según los valores que va retornando la función Imagen::agrega(), en "result"
	while(cont < max_iteraciones )
	{
		do //en el main nos aseguramos que Bi+margenes sea mayor estricto que tex. Esta primera iteración siempre se hará.
		{
			//Se obtiene el siguiente Bi a insertar en outRGB.
			result = EscogeBiSiguienteLum(row, col,
									outR, outG, outB, 
									LumTarg,
									TexR, TexG, TexB, 
									LumTex,
									BiR, BiG, BiB,
									tam_Bi);
			col += increment;
			
//			std::cout<<"caso normal"<<std::endl;
			cont++; if(cont == max_iteraciones) result=2; //Debugger
		}
		while(result == 0); //0==caso normal
		
		if(result == 1) //1==se llega al final de una fila
		{
			col = 0;
			row += increment;
//			std::cout<<"borde!!!"<<std::endl;
		}
		else if(result == 2){// 	std::cout<<"esquina!!!!!!!!!"<<std::endl;
			break;} //2==se llega al final de la última fila
	}
	
	/*
*/

	escribe((char*)"output.jpg",outR,outG,outB);
	cout<<"Nueva imagen creada"<<endl;
}

//Modifica las variables Bi R,G,B con un Bi cualquiera dentro de tex
void EscogeBiAleatorioLum(Imagen & outR, Imagen & outG, Imagen & outB, 
				   Imagen & LumTarg,
				   Imagen & texR, Imagen & texG, Imagen & texB,
				   Imagen & LumTex,
				   Imagen & BiR, Imagen & BiG, Imagen & BiB)
{
	unsigned int rowBi, colBi, tam_Bi = BiR.fils(); //Recordamos: Bi es cuadrado
	
	/// CORREGIDO!
// 	unsigned int tam_margen = (tam_Bi-tam_Bi/3)/6;
// 	
// 	unsigned int max = texR.fils()-tam_Bi-2*tam_margen; //Tamaño Bi + 2 márgenes.
// 	rowBi = rand() % max+1; //valor aleatorio desde 0 hasta max
// 	max = texR.cols()-tam_Bi-2*tam_margen; 
// 	colBi = rand() % max+1;
	
	vector<pair<double,pair<unsigned,unsigned> > > luminanciasB;
	
	ExtraeErrorLumTex(LumTarg, LumTex, tam_Bi, luminanciasB);
	
	generaCoordenadasNuevasBi(luminanciasB, rowBi, colBi);
	
	BiR.extrae(texR, rowBi, colBi);
	BiG.extrae(texG, rowBi, colBi);
	BiB.extrae(texB, rowBi, colBi);
	
	outR.agrega(BiR, 0, 0);
	outG.agrega(BiG, 0, 0);
	outB.agrega(BiB, 0, 0);
}

//Modifica las variables Bi R,G,B con un Bi cualquiera dentro de tex
void ExtraeErrorLumTex(Imagen & LumTarg, Imagen & LumTex, unsigned tam_Bi,
	vector<pair<double,pair<unsigned,unsigned> > >& luminanciasB)
{
}

//Modifica las variables Bi R,G,B segun los márgenes del último Bi añadido a outRGB (posición de inicio: (row,col))
//Atención!!: En este caso, el tamaño de BiR, BiG y BiB ya incluye los márgenes !!
int EscogeBiSiguienteLum(unsigned int row, unsigned int col, 
					Imagen & outR, Imagen & outG, Imagen & outB, 
					Imagen & LumTarg,
					Imagen & texR, Imagen & texG, Imagen & texB,
					Imagen & LumTex,
					Imagen & BiR, Imagen & BiG, Imagen & BiB,
					unsigned tam_Bi)
{
	int result = -1;
	
///Declaramos y llenamos una imagen con la suma de colores del margen vertical. De esta forma no hay que calcularlo cada vez.
	Imagen LumMargenV(BiR.fils()/4, BiR.fils()/8); ///tam_Bi/6 = BiR.fils()/8  [[ recordad que el tamaño de BiR es tam_Bi +tam_Bi/3]]
	
	Imagen auxV(LumMargenV.fils(), LumMargenV.cols()); //auxiliar
	auxV.extrae(outR, row, col);  LumMargenV=auxV;
	auxV.extrae(outG, row, col); LumMargenV+=auxV;
	auxV.extrae(outB, row, col);  LumMargenV+=auxV;

///Declaramos y llenamos una imagen con la suma de colores del margen horizontal. De esta forma no hay que calcularlo cada vez.
	Imagen LumMargenH(BiR.fils()/8, BiR.fils()/4, 0);
	
	Imagen auxH(LumMargenH.fils(), LumMargenH.cols(), 0); //auxiliar
	auxH.extrae(outR, row, col); LumMargenH=auxH;
	auxH.extrae(outG, row, col);  LumMargenH+=auxH;
	auxH.extrae(outB, row, col); LumMargenH+=auxH;
	
	
///Primera parte: Obtenemos los errores de todas las comparaciones con el margen actual y con la imagen targetRGB
	//Así no hay que recorrer la textura dos veces.
	//En cada posición del vector siguiente se guarda una energía y dos coordenadas. La energía es el resultante de la comparación de los márgenes que empiezan en las coordenadas.
	
	/// error en los margenes del Bi: en el solape entre texturaRGB y outRGB
	vector<pair<double,pair<unsigned,unsigned> > > errorLuminanciasMargen,errorLuminanciasB;
	CalculaErrorLumMargenes(LumTex, LumMargenV, LumMargenH, errorLuminanciasMargen);
	
	/// error en el conjunto del Bi: en el solape entre texturaRGB y targetRGB
	CalculaErrorLumTex(LumTarg, LumTex, tam_Bi, errorLuminanciasB);
	
	
	
///Segunda parte: 
	/// a partir de los errores mínimos obtenidos, obtenemos de entre estos Bi candidatos, las posiciones del inicio de un nuevo Bi aleatorio.
	unsigned int rowBi=0, colBi=0;
	
	generaCoordenadasNuevasBi(LumTex, LumMargenV, LumMargenH, errorLuminanciasMargen, errorLuminanciasB, rowBi, colBi);
	
     //Ahora ya podemos obtener Bi.
	BiR.extrae(texR, rowBi, colBi);
	BiG.extrae(texG, rowBi, colBi);
	BiB.extrae(texB, rowBi, colBi);
	
///Tercera parte: Si es conveniente, Bi se modifica con valores fuera de rango para los píxeles que no se quieren copiar a IMout
     //Esos valores fuera de rango se omitirán (no serán copiados) en la función Imagen:agrega()
	if(col!=0)
	{
		Imagen LumMargenVEscogido(auxV.fils(), auxV.cols());
		auxV.extrae(LumTex, rowBi, colBi);
		
		//Esta vez obtenemos la imagen resultante del cálculo de energías.
		compara(LumMargenV, auxV, LumMargenVEscogido);
		
		//Marcamos los valores fuera de rango
		marcaSegunSeamV(LumMargenVEscogido, BiR, BiG, BiB);
	}

	if(row!=0)
	{
		Imagen LumMargenHEscogido(auxH.fils(), auxH.cols());
		auxH.extrae(LumTex, rowBi, colBi);
		
		//Esta vez obtenemos la imagen resultante del cálculo de energías.
		compara(LumMargenH, auxH, LumMargenHEscogido);
		
		//Marcamos los valores fuera de rango
		marcaSegunSeamH(LumMargenHEscogido, BiR, BiG, BiB);
	}
	
	//Se inserta el Bi obtenido en IMout y se recoge el resultado
	result = outR.agrega(BiR, row, col);
	outG.agrega(BiG, row, col);
	outB.agrega(BiB, row, col);
	
	return result;
}

void generaCoordenadasNuevasBi(Imagen& LumTex, 
						 Imagen& LumMargenV, Imagen& LumMargenH, 
						 vector<pair<double,pair<unsigned,unsigned> > >& eMargen,
						 vector<pair<double,pair<unsigned,unsigned> > >& eBi,
						 unsigned int & rowBi, unsigned int & colBi)
{
	float THRESHOLD = 0.1;
	float ALPHA = 0.5;
	
	const double min_energiaM=eMargen[0].first; //Recordamos: El vector está ordenado.
	const double min_energiaB=eBi[0].first; //Recordamos: El vector está ordenado.
	
	if (ALPHA > 1.0){
		fprintf(stderr,"ALPHA mayor que 1.0!!! en transfer.cpp||generaCoordenadasNuevasBi()\n");
		exit(1);
	}	
	
	const double errorAverage = (min_energiaM*THRESHOLD)*ALPHA + (min_energiaB*THRESHOLD)*(1-ALPHA);
	
	unsigned int pos_validas = 0;
     //Como el vector energías está ordenado, establecemos la posición en la que sus energías posteriores dejen de ser válidas.
	while( (eMargen[pos_validas].first - eMargen[0].first) < eMargen[0].first*THRESHOLD 
			&&  (eBi[pos_validas].first - eBi[0].first) < eBi[0].first*THRESHOLD  )
		
		pos_validas++;

     //Obtenemos las coordenadas aleatorias de entre las válidas.
	pair<unsigned,unsigned> escogidas = eMargen[rand() % pos_validas].second;
	//pair<unsigned,unsigned> escogidas = energias[0].second;
	rowBi = escogidas.first;
	colBi = escogidas.second;	
}


//A partir de las energías guardadas en el vector calcula un margen de error y retorna aletoriamente la posición de...
//... inicio de uno de los márgenes en forma de L que están dentro de ese error.
void generaCoordenadasNuevasBi( vector<pair<double,pair<unsigned,unsigned> > >& energias,
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
	//pair<unsigned,unsigned> escogidas = energias[0].second;
	rowBi = escogidas.first;
	colBi = escogidas.second;		
}

double QuadError(const Imagen& A, Imagen& B)
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


void CalculaErrorLumTex(Imagen & LumTarg,Imagen & LumTex, unsigned int tam_Bi, vector<pair<double,pair<unsigned,unsigned> > >& energias)
{	
	//Reservamos espacio para el vector de energías.
	energias.reserve(LumTex.fils()*LumTex.cols());
	
	// Bi del taget con al que queremos mapear el error de luminancia
	Imagen LumTargetBi0(tam_Bi, tam_Bi, 0); 
	LumTargetBi0.extrae(LumTarg, 0, 0);
	
	Imagen LumTexBi(tam_Bi, tam_Bi, 0); //auxiliar
	
	double valor; //Un auxiliar
	 	
	//precálculo de los límites para el for
	const unsigned int MaxFils=LumTex.fils()-tam_Bi,  MaxCols=LumTex.cols()-tam_Bi;

     //Recorremos la textura guardando los resultados de las energías.
	for(unsigned int i=0; i<=MaxFils; i++)
		for(unsigned int j=0; j<=MaxCols; j++) 
		{
			//Obtenemos el margen correspondiente a la iteración
			LumTexBi.extrae(LumTex, i, j);
			
			//Se suman las energías de los dos Bi's
			valor = QuadError(LumTargetBi0, LumTexBi);
			
			//Guardamos la energía en el vector
			pair<double,pair<unsigned,unsigned> > energia (valor,pair<unsigned,unsigned>(i,j));
			energias.push_back(energia);
		}
		
	//Ordenamos el vector
	sort(energias.begin(),energias.end());
}

//Calcula las energías de todos los márgenes en forma de L (dividido en dos márgenes, a su vez) en la textura y...
//...los guarda en el vector energías para su posterior procesamiento.
void CalculaErrorLumMargenes(Imagen & LumTex,Imagen & LumMargenV,Imagen & LumMargenH,
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

/*
*/


