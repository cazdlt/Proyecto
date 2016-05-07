#ifndef __JUEGO__H__
#define __JUEGO__H__

#include "Jugador.h"
#include "Tablero.h"

#include <time.h>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <fstream>

class Juego{
	protected:
		std::vector<Jugador> jugadores;
		Tablero *tablero;
		int estado; //0. jugando -- 1. no iniciado -- 2. finalizado
        map<char, string> codificacion; /** mapa que muestra cada caracter y su codificacion binaria*/
        NodoHuffman * raiz; // CAMBIAR A PROTECTED
	    std::map<char,int> caracteres; /** mapa que muestra cada caracter y su frecuencia*/

	public:
	    static unsigned int turno;
		//CONSTRUCTORES
	    Juego();
	    ~Juego();

		//ACCESO
		int getEstado();
        std::vector<Jugador> getJugadores();
		Tablero* getTablero();

		//FUNCIONES
        bool inicializar();
		bool inicializar(std::string);
        int jugarTurno(int player); //0. turno completado -- 1.no es el turno -- 2. no existe player
        Jugador* searchJugador(int id);
        Jugador* searchJugador(std::string nombre);
        void printJugadores();
        void help();
        void help(std::string input);
        void ver(std::string input);
		void print();
		bool save(std::string input);
		void textinit(std::ifstream& file);
		bool llenarJugadores(int cant);

        bool comprimir(std::string input);
		std::string llenarMapaCaracteres(std::string);
        NodoHuffman *crearArbol(map<char, int>);
        void codificar(NodoHuffman *, string);


};

//UTILS

std::vector<std::string> splitstring(const std::string &s, char token);
std::string pickColor(std::vector<std::string>& disp);
int updateTurno(Juego* j0);
bool guardarPartida(std::ofstream& file,std::vector<Jugador> jugadores);
bool decode(std::string in);
std::stack<Tarjeta> compararTarjetas(std::vector<Tarjeta>& t1,std::vector<Tarjeta>& t2);



#include "Juego.hxx"
#endif
