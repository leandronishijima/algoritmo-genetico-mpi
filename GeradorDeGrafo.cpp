#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

#include "GeradorDeGrafo.h"

using namespace std;

void GeradorDeGrafo::iteraArquivoGerandoGrafoComCorUnica() {
	ifstream arquivo(nomeDoArquivo);

	int numeroVertice1, numeroVertice2;

 	while(!arquivo.eof()) {
		if(arquivo >> numeroVertice1 >> numeroVertice2)
			grafo.adicionaArestaComCor1(numeroVertice1, numeroVertice2);
	}

	arquivo.close();
}

void GeradorDeGrafo::iteraArquivoGerandoGrafoComCoresRandom() {
	ifstream arquivo(nomeDoArquivo);

	int numeroVertice1, numeroVertice2;

	while(!arquivo.eof())
		if(arquivo >> numeroVertice1 >> numeroVertice2)
			grafo.adicionaArestaComCorAleatoria(numeroVertice1, numeroVertice2);

	arquivo.close();
}

GeradorDeGrafo::GeradorDeGrafo(const char* nomeDoArquivo) {
	this->nomeDoArquivo = nomeDoArquivo;
}

Grafo GeradorDeGrafo::getGrafo() {
	return grafo;
}

