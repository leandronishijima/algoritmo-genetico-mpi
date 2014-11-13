#include "Vertice.h"

Vertice::Vertice() {
	valor = 0l;
	cor = 0;
	real = false;
}

void Vertice::setValor(int valor) {
	real = true;
	this->valor = valor;
}

void Vertice::setCor(int cor) {
	this->cor = cor;
}

int Vertice::getValor() {
	return valor;
}

int Vertice::getCor() {
	return cor;
}

bool Vertice::equals(Vertice other) {
	return getValor() == other.getValor() && getCor() == other.getCor();
}

bool Vertice::isReal() {
	return real;
}
