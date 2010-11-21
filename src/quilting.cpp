#include <quilting.h>

void quilting(Imagen & texR, Imagen & texG, Imagen & texB, unsigned int tam_Bi, Imagen & IMoutR, Imagen & IMoutG, Imagen & IMoutB)
{
	
	if( IMoutR.agrega(texR, 0, 0) || IMoutG.agrega(texG, 0, 0) || IMoutB.agrega(texB, 0, 0))
	{
		std::cout << "Ojo, que te sales de rango!!!"<< std::endl;
		exit(1);
	} 
	
	if( IMoutR.agrega(texR, 50, 170) || IMoutG.agrega(texG, 50, 170) || IMoutB.agrega(texB, 50, 170))
	{
		std::cout << "Ojo, que te sales de rango!!!"<< std::endl;
		exit(1);
	} 
	
	if( IMoutR.agrega(texR, 160, 20) || IMoutG.agrega(texG, 160, 20) || IMoutB.agrega(texB, 160, 20))
	{
		std::cout << "Ojo, que te sales de rango!!!"<< std::endl;
		exit(1);
	} 
	
	if( IMoutR.agrega(texR, 150, 160) || IMoutG.agrega(texG, 150, 160) || IMoutB.agrega(texB, 150, 160))
	{
		std::cout << "Ojo, que te sales de rango!!!"<< std::endl;
		exit(1);
	} 
}
