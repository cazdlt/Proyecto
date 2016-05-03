#ifndef __JUGADOR__H__
#define __JUGADOR__H__

#include "Territorio.h"
#include "Figura.h"
#include "Tablero.h"
#include "Tarjeta.h"

#include <vector>
#include <stack>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

class Jugador{
    protected:
        int id; 
        std::string nombre;
        std::string color;
        int cantidadInfanteria;
        std::vector<Territorio*> territorios;
        std::vector<Figura> ejercito;
        std::vector<Tarjeta> tarjetas;
		
	public:	
		//CONSTRUCTORES
        Jugador(std::string nombre, std::string color, int cantidadInfanteria, int id);
		Jugador();
		
		//ACCESO
        void setNombre(std::string nombre);
        std::string getNombre();
        void setColor(std::string color);
        std::string getColor();
        void setInfanteria(int cantidad);
        int getInfanteria();
        void setEjercito(Figura* figura);
        std::vector<Figura> getEjercito();
		void setID(int id);
		int getID();
		std::vector<Territorio*> getTerritorios();
        void setTerritorios(std::vector<Territorio*> n);
		std::vector<Tarjeta> getTarjetas();
		void setTarjetas(std::vector<Tarjeta> n);
		
		//FUNCIONES
        void restarInfanterias();       
        void obtenerUnidades(Tablero* tablero);
        bool ocupaContinente(Tablero* tablero,std::string nombre);
        int cambiarCartas();       
        Territorio* searchTerritorio(std::string nombre);
		Territorio* searchTerritorio(unsigned int inputID) ;
        void ubicarUnidades(int unidades,bool flag);
        int printTerritorios(); //returns numero de territorios
        bool isActive();
        bool atacar(Tablero* tablero);
        void fortificar(Tablero* tablero);
        void eliminarTerritorio(std::string nombret);
        void addTerritorio(Territorio* t0);
};

//UTILS
void lanzarDados(int& eo,int& ed);
int escojerNumDados(int max,bool flag);
bool realizarAtaque(Territorio* to,Territorio* td);

#include "Jugador.hxx"
#endif

