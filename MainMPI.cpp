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
	
	MPI::Init(argc, argv);

	MPI::Status status;

	int id = MPI::COMM_WORLD.Get_rank();

	switch(id) {

		case 0:
			string nomeDoArquivo = "grafo6.txt";
			MPI::COMM_WORLD.Send(nomeDoArquivo.c_str(), 1, MPI::CHAR, 1, 0);
			MPI::COMM_WORLD.Send(nomeDoArquivo.c_str(), 1, MPI::CHAR, 2, 0);
			break;

		case 1:
			const char *nomeDoArquivoSlave1;
			MPI::COMM_WORLD.Recv(&nomeDoArquivoSlave1, 1, MPI::CHAR, 0, 0, status);

			cout << nomeDoArquivoSlave1 << endl;

			executaAlgoritmoSequencialComGrafoComCoresIguais("grafo6.txt");
			break;

		case 2:
			const char *nomeDoArquivoSlave2;
			MPI::COMM_WORLD.Recv(&nomeDoArquivoSlave2, 1, MPI::CHAR, 0, 0, status);

			cout << nomeDoArquivoSlave2 << endl;

			executaAlgoritmoSequencialComCoresAleatorias("grafo6.txt");
			break;
	}

	MPI::Finalize();
	return 0;
}

// MPI_Pack / MPI_Unpack mecanismo de send/reciever para objetos
// http://www.usrlocal.ca/~dbm/resources/MPI/4_mpi_c++/4_mpi_c++.pdf