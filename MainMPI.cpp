#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>

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

void executaAlgoritmoSequencial() {
	GeradorDeGrafo gerador = GeradorDeGrafo("grafo6.txt");
	gerador.iteraArquivoGerandoGrafoComCorUnica();
	Grafo grafoComCorUnica = gerador.getGrafo();

	gerador = GeradorDeGrafo("grafo6.txt");
	gerador.iteraArquivoGerandoGrafoComCoresRandom();
	Grafo grafoComCoresAleatorias = gerador.getGrafo();

	vector<Grafo> populacao;
	populacao.push_back(grafoComCorUnica);
	populacao.push_back(grafoComCoresAleatorias);

	chrono::time_point<chrono::system_clock> inicio, fim;
	inicio = chrono::system_clock::now();

	executaAlgoritmoGenetico(populacao);

	fim = chrono::system_clock::now();

	chrono::duration<double> milisegundos = fim - inicio;

	cout << "Tempo de processamento (Sequencial): " << milisegundos.count() << endl;
}

void executaAlgoritmoComThreads() {
	GeradorDeGrafo gerador = GeradorDeGrafo("grafo6.txt");
	gerador.iteraArquivoGerandoGrafoComCorUnica();
	Grafo grafoComCorUnica = gerador.getGrafo();

	gerador = GeradorDeGrafo("grafo6.txt");
	gerador.iteraArquivoGerandoGrafoComCoresRandom();
	Grafo grafoComCoresAleatorias = gerador.getGrafo();

	vector<Grafo> populacaoComCorUnica;
	populacaoComCorUnica.push_back(grafoComCorUnica);

	vector<Grafo> populacaoComCoresAleatorias;
	populacaoComCoresAleatorias.push_back(grafoComCoresAleatorias);

	chrono::time_point<chrono::system_clock> inicio, fim;
	inicio = chrono::system_clock::now();

	thread t1(executaAlgoritmoGenetico, populacaoComCorUnica);
	thread t2(executaAlgoritmoGenetico, populacaoComCoresAleatorias);

	t1.join();
	t2.join();

	fim = chrono::system_clock::now();
	chrono::duration<double> milisegundos = fim - inicio;

	cout << "Tempo de processamento (2 threads): " << milisegundos.count() << endl;
}

int main(int argc, char *argv[]) {

	int numbernodes, rank;
	
	MPI::Init(argc, argv);

	numnodes = MPI::COMM_WORLD.Get_size();
	rank = MPI::COMM_WORLD.Get_rank();

	switch(rank) {

		case 0:
			p = new Point(1,2);
			p->pack(buf, BUF_SIZE, MPI::COMM_WORLD);
			MPI::COMM_WORLD.Send(buf, BUF_SIZE, MPI::PACKED, 1, 0);
			break;

		case 1:
			MPI::COMM_WORLD.Recv(buf, BUF_SIZE, MPI::PACKED, 0, 0, stat);
			p = new Point(buf,BUF_SIZE,MPI::COMM_WORLD);
			break;

	}

	MPI::Finalize();
	return 0;
}

// MPI_Pack / MPI_Unpack mecanismo de send/reciever para objetos
// http://www.usrlocal.ca/~dbm/resources/MPI/4_mpi_c++/4_mpi_c++.pdf