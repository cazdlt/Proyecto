#ifndef __CONTINENTE__H__
#define __CONTINENTE__H__

#include <list>
#include "Territorio.h"

class Continente{
    protected:
        std::string nombre;
        std::vector<Territorio*> territorios;
	public:
		//CONSTRUCTORES
        Continente(std::string nombre);
		~Continente();
		//ACCESO
        void setNombre(std::string nombre);
        std::string getNombre();
        std::vector<Territorio*> getTerritorios();
		
		//FUNCIONES
        void AgregarTerritorio(Territorio* ter);
        void print();
};

#include "Continente.hxx"
#endif
