#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <string>

#include "Grafo.h"
#include "Cromossomo.h"
#include "AlgoritmoGenetico.h"
#include "Vertice.h"
#include "GeradorDeGrafo.h"
#include "mpi.h"

using namespace std;

void executaAlgoritmoGenetico(vector<Grafo> populacao) {
	AlgoritmoGenetico algoritmo = AlgoritmoGenetico(populacao);
	algoritmo.executaAlgoritmo();
}

void executaAlgoritmoSequencialComGrafoComCoresIguais(const char* nomeDoArquivo) {
	GeradorDeGrafo gerador = GeradorDeGrafo(nomeDoArquivo);
	gerador.iteraArquivoGerandoGrafoComCorUnica();
	Grafo grafoComCorUnica = gerador.getGrafo();

	vector<Grafo> populacao;
	populacao.push_back(grafoComCorUnica);

	chrono::time_point<chrono::system_clock> inicio, fim;
	inicio = chrono::system_clock::now();

	executaAlgoritmoGenetico(populacao);

	fim = chrono::system_clock::now();

	chrono::duration<double> milisegundos = fim - inicio;

	cout << "Tempo de processamento slave 1: " << milisegundos.count() << endl;
}

void executaAlgoritmoSequencialComCoresAleatorias(const char* nomeDoArquivo) {
	GeradorDeGrafo gerador = GeradorDeGrafo(nomeDoArquivo);
	gerador.iteraArquivoGerandoGrafoComCoresRandom();
	Grafo grafoComCoresAleatorias = gerador.getGrafo();

	vector<Grafo> populacao;
	populacao.push_back(grafoComCoresAleatorias);

	chrono::time_point<chrono::system_clock> inicio, fim;
	inicio = chrono::system_clock::now();

	executaAlgoritmoGenetico(populacao);

	fim = chrono::system_clock::now();

	chrono::duration<double> milisegundos = fim - inicio;

	cout << "Tempo de processamento slave 2: " << milisegundos.count() << endl;
}

int main(int argc, char *argv[]) {

	int buffer[10];
	MPI_Status status;
	
	MPI::Init(argc, argv);

	int id = MPI::COMM_WORLD.Get_rank();

	if(id == 0) {

		int numero = 6;
		MPI::COMM_WORLD.Send(&numero, 1, MPI::INT, 1, 0);
		MPI::COMM_WORLD.Send(&numero, 1, MPI::INT, 2, 0);

		cout << "Master: " << numero << endl;
	} else if(id == 1) {
		cout << "iniciando Slave1 com arestas de cores iguais:" << endl;
		
		int novo;

		MPI::COMM_WORLD.Recv(&novo, 1, MPI::INT, 0, 0);

		string nomeDoArquivoSlave1 = "grafo" + to_string(novo) + ".txt";

		executaAlgoritmoSequencialComGrafoComCoresIguais(nomeDoArquivoSlave1.c_str());
	} 
	else {
		cout << "iniciando Slave2 grafo com população aleatória:" << endl;
		
		int novo;

		MPI::COMM_WORLD.Recv(&novo, 1, MPI::INT, 0, 0);

		string nomeDoArquivoSlave2 = "grafo" + to_string(novo) + ".txt";

		executaAlgoritmoSequencialComCoresAleatorias(nomeDoArquivoSlave2.c_str());
	}

	MPI::Finalize();
	return 0;
}