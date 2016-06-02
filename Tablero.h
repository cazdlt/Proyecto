#ifndef __TABLERO__H__
#define __TABLERO__H__

#include <stack>
#include <vector>
#include "Continente.h"
#include "Tarjeta.h"
#include <algorithm>

class Tablero{
    protected:
        std::vector<Continente*> continentes;
        std::stack<Tarjeta> tarjetas;
	public:
		//CONSTRUCTORES
        Tablero();
		~Tablero();
		
		//ACCESO
        std::vector<Continente*> getContinentes();
		void setTarjetas(std::stack<Tarjeta> n);
		std::stack<Tarjeta>* getTarjetas();
        
		//FUNCIONES
		void print();
		void printDisponibles();     
		Territorio* searchTerritorio(unsigned int id);
		Territorio* searchTerritorio(std::string nombre);
		Territorio* searchTerritorioDisponible(unsigned int id);
        Territorio* pickAdyacente(bool enemigo,Jugador* j0,Territorio* terr);
		void fillTarjetas();
		std::vector<Territorio*> getTerritorios();
};

//UTILS
std::vector<Tarjeta> allTarjetas(Tablero* t0);

#include "Tablero.hxx"
#endif
