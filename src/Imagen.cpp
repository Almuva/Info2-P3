#include <Imagen.h>
#include <stdio.h>
#include <math.h>
#include <cstring>

Imagen::Imagen()
{
	dim[0]=0;
	dim[1]=0;
	datos=new double[1];
}

Imagen::Imagen(Imagen & im2)
{
	dim[0]=im2.fils();
	dim[1]=im2.cols();
	unsigned int largo=dim[0]*dim[1];
	datos=new double[largo];
	memcpy (datos,im2.datos,largo*sizeof(double));
}

Imagen::Imagen(unsigned int fil, unsigned int col)
{
	dim[0]=fil;
	dim[1]=col;
	datos=new double[fil*col];
}

Imagen::Imagen(unsigned int fil, unsigned int col, float val)
{
	dim[0]=fil;
	dim[1]=col;
	unsigned int largo=fil*col;
	datos=new double[largo];
	for(unsigned int i=0; i<largo;i++)
		datos[i]=val;
}

Imagen::~Imagen()
{
	delete[] datos;
}

void Imagen::operator*=(float dt)
{
	unsigned int largo=dim[0]*dim[1];
	for(unsigned int i=0;i<largo;i++)
		datos[i]*=dt;
}

void Imagen::operator+=(float dt)
{
	unsigned int largo=dim[0]*dim[1];
	for(unsigned int i=0;i<largo;i++)
		datos[i]+=dt;
}

void Imagen::operator+=(Imagen & im2)
{
	unsigned int fil2=im2.fils();
	unsigned int col2=im2.cols();
	if(dim[0]!=fil2 || dim[1]!=col2)
		{
			fprintf(stderr,"Diferentes dimensiones al sumar imagenes \n");
			return;
		}

	unsigned int largo=dim[0]*dim[1];
	for(unsigned int i=0; i<largo; i++)
		datos[i]+=im2.datos[i];

	return;
}

void Imagen::operator-=(Imagen & im2)
{
	unsigned int fil2=im2.fils();
	unsigned int col2=im2.cols();
	if(dim[0]!=fil2 || dim[1]!=col2)
		{
			fprintf(stderr,"Diferentes dimensiones al restar imagenes \n");
			return;
		}

	unsigned int largo=dim[0]*dim[1];
	for(unsigned int i=0; i<largo; i++)
		datos[i]-=im2.datos[i];

	return;
}


void Imagen::operator*=(Imagen	& im2)
{
	unsigned int fil2=im2.fils();
	unsigned int col2=im2.cols();
	if(dim[0]!=fil2 || dim[1]!=col2)
		{
			fprintf(stderr,"Diferentes dimensiones al multiplicar imagenes \n");
			return;
		}
	unsigned int largo=dim[0]*dim[1];
	for(unsigned int i=0; i<largo; i++)
		this->datos[i] *= (&im2)->datos[i];

	return;
}

void Imagen::operator/=(Imagen	& im2)
{
	// si el divisor es 0, pone 0 en el cociente...
	unsigned int fil2=im2.fils();
	unsigned int col2=im2.cols();
	if(dim[0]!=fil2 || dim[1]!=col2)
		{
			fprintf(stderr,"Diferentes dimensiones al multiplicar imagenes \n");
			return;
		}

	unsigned int largo=dim[0]*dim[1];
	double div;
	for(unsigned int i=0; i<largo; i++)
		{
			div=im2.datos[i];
			if(fabs(div)>1e-10)
	datos[i]/=div;
			else
	datos[i]=0.0;
		}
	return;
}

void Imagen::operator=(Imagen & im2)
{
	// este operador no duplica la memoria //
	unsigned int fil2=im2.fils(),col2=im2.cols(),largo=fil2*col2;
		if(dim[0]!=fil2 || dim[1]!=col2)
		{
			//fprintf(stderr,"Diferentes dimensiones al copiar imagenes \n");
			dim[0]=fil2;
			dim[1]=col2;
			delete[] datos;
			datos=new double[fil2*col2];
		}
	memcpy (datos,im2.datos,largo*sizeof(double));
}


float Imagen::minval()
{
	float m=1e20;
	unsigned int largo=dim[0]*dim[1];
	for(unsigned int i=0; i<largo; i++)
		m=min(m,datos[i]);

	return m;
}


float Imagen::maxval()
{
	float m=-1e20;
	unsigned int largo=dim[0]*dim[1];
	for(unsigned int i=0; i<largo; i++)
		m=max(m,datos[i]);

	return m;
}

//Se llama igual y hace lo mismo que la función de octave
double Imagen::sum()
{
	double suma = 0.0;
	unsigned int largo=dim[0]*dim[1];
	for(unsigned int i=0; i<largo; i++)
		suma+=datos[i];

	return suma;
}

void Imagen::resize_erase(unsigned int rows, unsigned int cols)
{
	delete[] datos;
	dim[0] = rows;
	dim[1] = cols;

	unsigned int largo = dim[0]*dim[1];
	datos=new double[largo];
	for(unsigned int i=0; i<largo;i++)
		datos[i]=0.0;
}

//Extrae (copia) de I una imagen, del tamaño (f, c), del tamaño de this y la asigna.
//Retorna true si es posible i false sino
void Imagen::extrae(Imagen& I,unsigned int row,unsigned int col)
{
	unsigned int fils=dim[0]+row,cols=dim[1]+col,i=0;
	if(I.fils()<fils || I.cols()<cols)	//check: no se pueden pedir valores fuera de la imagen.
	{
		fprintf(stderr,"ERROR: (extrae) Intenta extraer fuera de la imagen !\n");exit(1);
	}

	for(unsigned int f=row;f<fils;f++)
		for(unsigned int c=col;c<cols;c++)
		{
			datos[i]=I(f,c);
			i++;
		}
}

//Mete en this una imagen más pequeña, im, partiendo de la posición row, col
//Valores de return: 1 si metiendo im se llega al lateral de this.
//			2 si metiendo im se llega a la esquina inferior derecha de this.
//			0 si se mete y no ocurre lo anterior
int Imagen::agrega(Imagen & im, unsigned int row, unsigned int col)
{
	if(  (row > dim[0]-1) || (col > dim[1]-1)  )
	{
		fprintf(stderr,"En ''Imagen::agrega(...)'' se lee fuera de rango!!!\n");
		exit(1);
	}
	
	unsigned int retorno = 0;

	unsigned int index_im = 0; //Para ir leyando im
	
	unsigned int jump_cols = 0; //Para omitir x ultimas columnas de im
	
	//Posiciones de Imagen donde acaba im
	unsigned int row_end = row + im.fils()-1;
	unsigned int col_end = col + im.cols()-1;
	
	//Si im se sale de la Imagen (por la derecha)...
	if(col_end > dim[1])
	{
	//...hay que modificar los finales y que asignar un salto en im.
		jump_cols = col_end - dim[1]+1;
		col_end = dim[1]-1;
		retorno = 1;
	}
	
	if(row_end > dim[0])
	{
		row_end = dim[0]-1;
		
		if(retorno == 1) retorno = 2;
	}
	
	//bucle de copia
	for(unsigned int i = row; i<=row_end; i++)
	{
		for(unsigned int j = col; j<=col_end; j++)
		{
			//10E20 es el numero que usamos para marcar el trozo de Bi que no se debe meter en la imagen de salida.
			if(im.datos[index_im] != 10E20) datos[i*dim[1]+j] = im.datos[index_im];
			index_im++;
		}
		index_im+=jump_cols;
	}
	
//	std::cout<<"retorno: "<<retorno<<std::endl;
	
	return retorno;
}






