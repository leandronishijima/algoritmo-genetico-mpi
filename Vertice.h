#ifndef VERTICE_H_
#define VERTICE_H_

class Vertice {

	int valor;
	int cor;
	bool real;

public:
	Vertice();
	void setValor(int);
	void setCor(int);
	int getCor(void);
	int getValor(void);
	bool isReal();
	bool equals(Vertice other);
};

#endif
