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
		
		//ACCESO
        void setNombre(std::string nombre);
        std::string getNombre();
        void setColor(std::string color);
        std::string getColor();
        void setInfanteria(int cantidad);
        int getInfanteria();
        void setEjercito(Figura* figura);
        std::vector<Figura> getEjercito();
		int getID();
		std::vector<Territorio*> getTerritorios();
        void setTerritorios(std::vector<Territorio*> n);
		
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

#include "Jugador.hxx"
#endif

