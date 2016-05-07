#ifndef HUFFMANCODEC_H
#define HUFFMANCODEC_H

#include "NodoHuffman.h"
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <bitset>

class HuffmanCodec{

	protected:
		std::map<char, std::string> codificacion; /** mapa que muestra cada caracter y su codificacion binaria*/
		NodoHuffman * raiz; 
		std::map<char,int> caracteres; /** mapa que muestra cada caracter y su frecuencia*/
public:
		HuffmanCodec();
		HuffmanCodec(std::map<char,int> m);
		bool comprimir(std::string input);		
		std::string llenarMapaCaracteres(std::string);
        NodoHuffman *crearArbol(std::map<char, int>);
        void codificar(NodoHuffman *, std::string);
		bool decode (std::string in);
	
};

#include "HuffmanCodec.hxx"
#endif