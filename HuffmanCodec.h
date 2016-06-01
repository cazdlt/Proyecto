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
		~HuffmanCodec();
		bool comprimir(std::string input);		
		std::string llenarMapaCaracteres(std::string);
        NodoHuffman *crearArbol();
        void codificar(NodoHuffman *, std::string);
		bool decode (std::string in); 
		void decodificarCaracteres(std::ifstream&,unsigned int x);
	
};

std::vector<std::string> splitstring(const std::string &s, char token);

#include "HuffmanCodec.hxx"
#endif