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
//	memset(datos,val,largo*sizeof(double));
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

void Imagen::resize_erase(unsigned int rows, unsigned int cols)
{

	delete[] datos;
	dim[0] = rows;
	dim[1] = cols;
	datos=new double[dim[0]*dim[1]];

}
