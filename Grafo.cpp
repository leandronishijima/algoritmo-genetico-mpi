#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>

#include "Grafo.h"
#include "Vertice.h"
#include "Aresta.h"

using namespace std;

Grafo::Grafo() {
	srand(1);
	avaliacao = -1;
}

Vertice Grafo::adicionaVertice(int numeroVertice, int corVertice) {
	Vertice v = Vertice();
	v.setValor(numeroVertice);
	v.setCor(corVertice);

	vertices[numeroVertice] = v;

	return v;
}

Vertice Grafo::buscaOuAdicionaVerticeComCor1(int valorVertice) {
	Vertice vertice = vertices[valorVertice];

	if (vertice.isReal())
		return vertice;
	else
		return adicionaVertice(valorVertice, 1);
}

void Grafo::adicionaArestaNaListaDeAdjacencia(Vertice vertice, const Aresta& aresta) {
	listaDeAdjacencia[vertice.getValor()].push_back(aresta);
}

void Grafo::criaAresta(Vertice vertice1, Vertice vertice2) {
	Aresta aresta = Aresta(vertice1.getValor(), vertice2.getValor());

	arestas.push_back(aresta);

	adicionaArestaNaListaDeAdjacencia(vertice1, aresta);
	adicionaArestaNaListaDeAdjacencia(vertice2, aresta);
}

void Grafo::adicionaArestaComCor1(int verticeValor1, int verticeValor2) {
	Vertice vertice1 = buscaOuAdicionaVerticeComCor1(verticeValor1);
	Vertice vertice2 = buscaOuAdicionaVerticeComCor1(verticeValor2);

	criaAresta(vertice1, vertice2);
}

Vertice Grafo::buscaOuAdicionaVerticeComCorRandom(int valorVertice) {
	Vertice vertice = vertices[valorVertice];

	if (vertice.isReal())
		return vertice;
	else
		return adicionaVertice(valorVertice, rand() % 4);
}

void Grafo::adicionaArestaComCorAleatoria(int verticeValor1, int verticeValor2) {
	Vertice vertice1 = buscaOuAdicionaVerticeComCorRandom(verticeValor1);
	Vertice vertice2 = buscaOuAdicionaVerticeComCorRandom(verticeValor2);

	criaAresta(vertice1, vertice2);
}

int Grafo::getQuantidadeVertices() {
	return vertices.size();
}

int Grafo::getQuantidadeAresta() {
	return arestas.size();
}

bool Grafo::naoExisteAdjacenteComCor(Vertice vertice, int novaCor) {
	vector<Aresta> adjacentes = listaDeAdjacencia[vertice.getValor()];

	for(vector<Aresta>::iterator it = adjacentes.begin() ; it != adjacentes.end(); ++it) {
		Aresta aresta = *it;

		int indiceOutroVertice = aresta.getOutroVertice(vertice.getValor());
		int corAdjacente = vertices[indiceOutroVertice].getCor();

		if (corAdjacente == novaCor)
			return false;
	}

	return true;
}

void Grafo::randomizaCorVerticeSeguindoHeuristica(int verticeNumero, int cor) {
 	Vertice vertice = vertices[verticeNumero];

	if (naoExisteAdjacenteComCor(vertice, cor)) {
		vertice.setCor(cor);
		vertices[verticeNumero] = vertice;
		calculaAvaliacao();
	}
}

bool Grafo::isArestaComVerticesComCoresDiferentes(Aresta aresta) {
	int indiceVertice1 = aresta.getIndiceVertice1();
	int indiceVertice2 = aresta.getIndiceVertice2();

	Vertice v1 = vertices[indiceVertice1];
	Vertice v2 = vertices[indiceVertice2];

	return v1.getCor() != v2.getCor();
}

void Grafo::calculaAvaliacao() {
	int novaAvaliacao = 0;

	for(vector<Aresta>::iterator it = arestas.begin() ; it != arestas.end(); ++it) {
		Aresta aresta = *it;

		if (isArestaComVerticesComCoresDiferentes(aresta))
			novaAvaliacao++;
	}

	avaliacao = novaAvaliacao;
}

int Grafo::getAvaliacao() {
	if(avaliacao == -1)
		calculaAvaliacao();

	return avaliacao;
}

