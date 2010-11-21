#ifndef IMAGEN_H
#define IMAGEN_H

class Imagen
{
	public:
	unsigned int dim[2];
	double * datos;
	Imagen();
	Imagen(Imagen & im2);
	Imagen(unsigned int fil, unsigned int col);
	Imagen(unsigned int fil, unsigned int col, float val);
	~Imagen();
	void operator*=(float dt);
	void operator+=(float val);
	void operator+=(Imagen & im2);
	void operator-=(Imagen & im2);
	void operator*=(Imagen & im2);
	void operator/=(Imagen & im2);
	void operator=(Imagen & im2);
	unsigned int fils(){return dim[0];}
	unsigned int cols(){return dim[1];}
	unsigned int area(){return dim[0]*dim[1];}
	inline double & operator()(unsigned int i, unsigned int j)
	{
		//evita leer fuera de rango
		const unsigned int N=5;
		if(i>=dim[0])
		{
			if(i-dim[0]<=N)	//sale por abajo
			{
				i=dim[0]*2-(i+2);
			}
			else	//sale por arriba
			{
				i=-i;
			}
		}
		if(j>=dim[1])
		{
			if(j-dim[1]<=N)	//sale por la derecha
			{
				j=dim[1]*2-(j+2);
			}
			else	//sale por la izquierda
			{
				j=-j;
			}
		}
		return datos[i*dim[1]+j];
	};
	float maxval();
	float minval();

	void resize_erase(unsigned int rows, unsigned int cols);
	int agrega(Imagen & im, unsigned int row, unsigned int col);
	bool extrae(Imagen& I,unsigned int f,unsigned int c);

	void recorta(float M,float m);
	Imagen & desplaza(int dim, int paso);
};

Imagen & lee(char * archima, int campo);
int compara_dims(Imagen & im1, Imagen & im2);
void escribe(char * archima, Imagen & imR, Imagen & imG, Imagen & imB);
void escribe(char * archima, Imagen & imR);

void imprime_pant(Imagen & Im);


inline double max(double a, double b)
{
	if(a<=b)
		return(b);
	else
		return(a);
}


inline double min(double a, double b)
{
	if(a>=b)
		return(b);
	else
		return(a);
}

inline int signo(double a)
{
	if(a!=0.0)
		if(a>0)
			return(1);
		else
			return(-1);
	else
		return(0);
}
#endif

