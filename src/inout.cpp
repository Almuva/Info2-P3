#include "Imagen.h"
#include <stdio.h>

#include <Magick++.h>
#include <iostream> 
using namespace std; 
using namespace Magick; 

#define maxpaleta 65535.0
#define maxmipaleta 255.0
/* El tama#o maximo de paleta es 65536, especificado por QuantumLeap al compilar ImageMagick*/

Imagen & lee(char * archima, int campo)
{
	Image image(archima);

	unsigned int alto=image.rows();
	unsigned int ancho=image.columns();	
	
	Imagen * im=new Imagen(alto,ancho,0.0);
	double c=maxmipaleta/maxpaleta;

	 for(unsigned int i=0;i<alto;i++)
		for(unsigned int j=0;j<ancho;j++)
			switch(campo)
	{
	case 0:
		(*im)(i,j)=c*(image.pixelColor(j,i)).redQuantum();
		break;
	case 1:
		(*im)(i,j)=c*(image.pixelColor(j,i)).greenQuantum();
		break;
	case 2:
		(*im)(i,j)=c*(image.pixelColor(j,i)).blueQuantum();
		break;
	default:
		fprintf(stderr,"\n Error en inout.cpp al leer archivo \n");
		break;
	} 
	
	 return(*im);
}

int compara_dims(Imagen & im1, Imagen & im2)
{
	if((im1.fils()!=im2.fils()) | (im1.cols()!=im2.cols()))
		return 0;
	return 1;
}


void escribe(char * archima, Imagen & imR, Imagen & imG, Imagen & imB)
{
	if(!fork())
	{
		unsigned int ancho=imR.cols();
		unsigned int alto=imR.fils();
		if((compara_dims(imR,imG)!=1) | (compara_dims(imG,imB)!=1))
		{
			fprintf(stderr,"\n Error al escribir en inout.cpp: imagenes R,G,B con distintas dimensiones. \n");
			return;
		}

		Geometry geom(ancho,alto);
		Image im(geom,"white");

		float cR,cG,cB;
		cR=cG=cB=maxpaleta;

		float MR=imR.maxval();
		float mR=imR.minval();
		if(mR>=0.0 && mR<=maxmipaleta && MR>=0.0 && MR<=maxmipaleta)
		{
			mR=0.0;
			MR=1.0;
			cR=maxpaleta/maxmipaleta;
		}

		float MG=imG.maxval();
		float mG=imG.minval();
		if(mG>=0.0 && mG<=maxmipaleta && MG>=0.0 && MG<=maxmipaleta)
		{
			mG=0.0;
			MG=1.0;
			cG=maxpaleta/maxmipaleta;
		}

		float MB=imB.maxval();
		float mB=imB.minval();
		if(mB>=0.0 && mB<=maxmipaleta && MB>=0.0 && MB<=maxmipaleta)
		{
			mB=0.0;
			MB=1.0; 
			cB=maxpaleta/maxmipaleta;
		}

		for(unsigned int i=0;i<alto;i++)
			for(unsigned int j=0;j<ancho;j++)
			{
				float R=imR(i,j);
				float G=imG(i,j);
				float B=imB(i,j);
				R=cR*(R-mR)/(MR-mR);
				G=cG*(G-mG)/(MG-mG);
				B=cB*(B-mB)/(MB-mB);
				Color col((unsigned int)R,(unsigned int)G,(unsigned int)B);
				im.pixelColor(j,i,col);
			}
		im.write(archima);

		_exit(1);
	}
	return;
}


void escribe(char * archima, Imagen & imR)
{
	if(!fork())
	{
		unsigned int ancho=imR.cols();
		unsigned int alto=imR.fils();

		Geometry geom(ancho,alto);
		Image im(geom,"white");

		float M=imR.maxval();
		float m=imR.minval();
		float c=maxpaleta;
		if(m>=0.0 && m<=maxmipaleta && M>=0.0 && M<=maxmipaleta)
			{
				m=0.0;
				M=1.0;
				c=maxpaleta/maxmipaleta;
			}

		for(unsigned int i=0;i<alto;i++)
			for(unsigned int j=0;j<ancho;j++)
				{
		float R=imR(i,j);
		R=c*(R-m)/(M-m);
		Color col((unsigned int)R,(unsigned int)R,(unsigned int)R);
					im.pixelColor(j,i,col);
				}

		im.write(archima);
		_exit(1);
	}
	return;
}

void imprime_pant(Imagen & Im)
{
	for(unsigned int i=0; i<Im.fils(); i++)
	{
		for(unsigned int j=0; j<Im.cols(); j++)
		{
			printf("%f ", Im(i, j));
		}
		printf("\n");
	}
}

