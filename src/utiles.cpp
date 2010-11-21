#include <Imagen.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void Imagen::recorta(float M,float m)
{
  // recorta los valores mayores que M y menores que m

  int largo=dim[0]*dim[1];
  for(int i=0;i<largo;i++)
    {
      datos[i]=min(datos[i],M);
      datos[i]=max(datos[i],m);
    }
}



Imagen & Imagen::desplaza(int dim, int paso)
{

  // devuelve una nueva imagen, resultado de desplazar
  // una cantidad _paso_ de pixels en la direccion _dim_

  unsigned int fil=this->fils();
  unsigned int col=this->cols();
  Imagen * res=new Imagen(fil,col);
  switch(dim)
    {
    case 0:
      for(unsigned int i=0;i<fil;i++)
	for(unsigned int j=0;j<col;j++)
	  (*res)(i,j)=(*this)(div(i+paso,fil).rem,j);
      break;
    case 1:
      for(unsigned int i=0;i<fil;i++)
	for(unsigned int j=0;j<col;j++)
	  (*res)(i,j)=(*this)(i,div(j+paso,col).rem);
      break;
    default:
      fprintf(stderr,"\n Error en desplaza \n");
      break;
    }
  return(*res);
}


