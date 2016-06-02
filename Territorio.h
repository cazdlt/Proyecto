#ifndef __TERRITORIO__H__
#define __TERRITORIO__H__

#include "Jugador.h"
#include "Figura.h"
#include <vector>
#include <algorithm>

class Jugador;
struct TArista;

class Territorio{
protected:
		int id;
        std::string nombre;
		std::string color;
        Jugador* miJugador;
        int ejercito;
        std::vector<Figura> unidades;
        std::vector<Territorio*> territoriosAdyacentes;
        bool ocupado;
public:
		static unsigned int CURR_ID;
		
		//CONSTRUCTORES
		Territorio();
        Territorio(std::string nombre);
		
		//ACCESO
        void setNombre(std::string nombre);
        std::string getNombre();
		unsigned int getID();
        std::vector<Territorio*> getTerritoriosA();		
		std::vector<Figura> getUnidades();
        void setUnidades(Figura &unidad);
		int cantidadUnidades();
        int getEjercito();
        void setEjercito(int n);
        void setJugador(Jugador* n);
        Jugador* getJugador();
		void setAdyacentes(std::vector<Territorio*> n);
        void setOcupado(bool ocupado);
        bool isOcupado();
		std::string getColor();
		void setColor(std::string n);
		int obtenerCostoEjercito(Territorio* des);
		std::vector<TArista> rutaAEnemigos(std::vector<Territorio*>& grafo);
		
		//FUNCIONES
		bool operator<(const Territorio& cmp);
        void AgregarTerritorio(Territorio *ter);        
        void updateUnidades(std::string color);        
		void print();
		
};

struct TArista{
	unsigned int src;
	unsigned int des;
	int dist; //distancia total para dij

	TArista(unsigned int s,unsigned int d,float peso);
	TArista();
	friend bool operator> (const TArista& a, const TArista& b);
	friend std::ostream& operator<<(std::ostream& o,TArista& obj);
};

int buscarDijsktra(unsigned int index,std::vector<TArista> n);
Territorio* buscarTerritorioGrafo(std::vector<Territorio*>& tts, int id);

#include "Territorio.hxx"
#endif


