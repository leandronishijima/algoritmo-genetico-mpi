#ifndef GERADORDEGRAFO_H_
#define GERADORDEGRAFO_H_

#include <fstream>
#include <iostream>

#include "Grafo.h"

using namespace std;

class GeradorDeGrafo {

	Grafo grafo;
	const char* nomeDoArquivo;

public:
	GeradorDeGrafo(const char* nomeDoArquivo);
	Grafo getGrafo();
	void iteraArquivoGerandoGrafoComCorUnica();
	void iteraArquivoGerandoGrafoComCoresRandom();
};

#endif
