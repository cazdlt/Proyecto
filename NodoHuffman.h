#ifndef NODOHUFFMAN_H__
#define NODOHUFFMAN_H__

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
		bool isLeaf();
};

#include "NodoHuffman.hxx"

#endif
