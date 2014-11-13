#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Cromossomo.h"
#include "Vertice.h"
#include "Grafo.h"

Cromossomo::Cromossomo() {
	srand(time(NULL));
}

Cromossomo::Cromossomo(Grafo grafo) {
	this->grafo = grafo;
}

void Cromossomo::randomizaCorVertice() {
	int qtdVertices = grafo.getQuantidadeVertices() - 1;
	int verticeRandom = rand() % qtdVertices + 1;
	int corRandom = rand() % 4;

	grafo.randomizaCorVerticeSeguindoHeuristica(verticeRandom, corRandom);
}

int Cromossomo::getAvaliacao() {
	return grafo.getAvaliacao();
}

int Cromossomo::getQuantidadeDeArestas() {
	return grafo.getQuantidadeAresta();
}
