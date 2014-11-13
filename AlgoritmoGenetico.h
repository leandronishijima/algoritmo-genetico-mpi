#ifndef ALGORITMOGENETICO_H_
#define ALGORITMOGENETICO_H_

#include <vector>
#include "Grafo.h"
#include "Cromossomo.h"

using namespace std;

class AlgoritmoGenetico {

	vector<Cromossomo> populacao;
	Cromossomo cromossomoMaisAdaptado;
	long tempoExecucao;

public:
	AlgoritmoGenetico();
	AlgoritmoGenetico(vector<Grafo> populacaoInicial);
	void executaAlgoritmo();

private:
	void adicionaGrafoAPopulacao(Grafo grafo);
	bool criterioDeParada();
	void validaNovoCromossomoMaisAdaptado();
	bool verificaAvaliacaoMaxima();
	int avaliacaoCromossomoMaisAdaptado();
};

#endif
