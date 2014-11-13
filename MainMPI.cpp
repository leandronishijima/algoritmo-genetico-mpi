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

	int numbernodes, mynode;
	
	MPI::Init();

	numnodes = MPI::COMM_WORLD.Get_size();
	mynode   = MPI::COMM_WORLD.Get_rank();

	if( mynode != 0 ){
	    MPI::COMM_WORLD.Send( &sum, 1, MPI::INT, 0, 1 );
	} else {
	    for( int j=1; j<numnodes; ++j ){
	      MPI::COMM_WORLD.Recv( &accum, 1, MPI::INT, j, 1, status);
	      sum = sum + accum;
        }
	}
    if( mynode == 0 )
	    std::cout << "The sum from 0 to 1000 is: " << sum << endl;

	MPI::Finalize();
	return 0;
}

// MPI_Pack / MPI_Unpack mecanismo de send/reciever para objetos
// http://www.usrlocal.ca/~dbm/resources/MPI/4_mpi_c++/4_mpi_c++.pdf