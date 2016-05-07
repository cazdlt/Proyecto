#ifndef NODOHUFFMAN_H__
#define NODOHUFFMAN_H__

using namespace std;

class NodoHuffman{
	private:
		char letra;
		int frecuencia;
		NodoHuffman *izq;
		NodoHuffman *der;
	public:
		NodoHuffman();
		~NodoHuffman();
		char getLetra();
		void setLetra(char);
		int getFrecuencia();
		void setFrecuencia(int);
		NodoHuffman *getIzq();
		void setIzq(NodoHuffman *);
		NodoHuffman *getDer();
		void setDer(NodoHuffman *);
		void preOrden();
};

#include "NodoHuffman.hpp"

#endif
