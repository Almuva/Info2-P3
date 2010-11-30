#include <transfer.h>

void transferTexture(Imagen& AR,Imagen& AG,Imagen& AB,Imagen& BR,Imagen& BG,Imagen& BB,unsigned tam_Bi)
{
	Imagen Luminancia1,Luminancia2,imagenAuxuliar;
	
	//cada luminancia es una imagen a parte que guarda la luminancia de la imagen de entrada
	Luminancia1=AR; Luminancia1*=0.3;
	imagenAuxuliar=AG; imagenAuxuliar*=0.59; Luminancia1+=imagenAuxuliar;
	imagenAuxuliar=AB; imagenAuxuliar*=0.11; Luminancia1+=imagenAuxuliar;
	
	Luminancia2=BR; Luminancia2*=0.3;
	imagenAuxuliar=BG; imagenAuxuliar*=0.59; Luminancia2+=imagenAuxuliar;
	imagenAuxuliar=BB; imagenAuxuliar*=0.11; Luminancia2+=imagenAuxuliar;
	
	
}
