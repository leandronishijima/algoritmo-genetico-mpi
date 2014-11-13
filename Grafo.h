#ifndef GRAFO_H_
#define GRAFO_H_

#include <map>
#include <vector>
#include "Vertice.h"
#include "Aresta.h"

using namespace std;

class Grafo {

	map<int, vector<Aresta> > listaDeAdjacencia;
	map<int, Vertice> vertices;
	vector<Aresta> arestas;
	int avaliacao;

public:
	Grafo();
	Vertice adicionaVertice(int numeroVertice, int corVertice);
	void adicionaArestaComCor1(int verticeValor1, int verticeValor2);
	void adicionaArestaComCorAleatoria(int verticeValor1, int verticeValor2);
	void calculaAvaliacao();
	int getAvaliacao();
	void randomizaCorVerticeSeguindoHeuristica(int verticeNumero, int cor);
	int getQuantidadeVertices();
	int getQuantidadeAresta();

private:
	bool naoExisteAdjacenteComCor(Vertice vertice, int cor);
	Vertice buscaOuAdicionaVerticeComCor1(int valorVertice);
	Vertice buscaOuAdicionaVerticeComCorRandom(int valorVertice);
	void adicionaArestaNaListaDeAdjacencia(Vertice vertice1, const Aresta& aresta);
	void criaAresta(Vertice vertice1, Vertice vertice2);
	bool isArestaComVerticesComCoresDiferentes(Aresta aresta);
};

#endif
