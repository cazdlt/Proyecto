#include "Territorio.h"

unsigned int Territorio::CURR_ID=1;

bool Territorio::operator<(const Territorio& cmp){
    return id < cmp.id;
}

Territorio::Territorio(){
	id=0;
	nombre="0";
	ocupado=false;
	ejercito=0;
	miJugador=NULL;
	color="";
}

Territorio::Territorio(std::string nombre) {
	this->nombre=nombre;
	ejercito=0;
	miJugador=NULL;
	ocupado=false;
	color="";
	id=CURR_ID;
	CURR_ID++;
}
void Territorio::setNombre(std::string nombre) {
	this->nombre=nombre;
}

unsigned int Territorio::getID(){
	return id;
}

std::string Territorio::getNombre() {
	return this->nombre;
}
std::vector<Territorio*> Territorio::getTerritoriosA() {
	return this->territoriosAdyacentes;
}
void Territorio::AgregarTerritorio(Territorio *ter) {
	this->territoriosAdyacentes.push_back(ter);
}

void Territorio::setUnidades(Figura& unidad) {
	this->unidades.push_back(unidad);
}
std::vector<Figura> Territorio::getUnidades() {
	return this->unidades;
}
int Territorio::cantidadUnidades() {
	return this->unidades.size();
}
int Territorio::getEjercito() {
	return ejercito;
}

void Territorio::setEjercito(int n) {
	ejercito=n;
}

void Territorio::setJugador(Jugador* n) {
	miJugador=n;
}

Jugador* Territorio::getJugador() {
	return miJugador;
}

void Territorio::updateUnidades(std::string color) {

	std::vector<Figura> u;
	Figura aux;
	int n=ejercito;
	aux.setColor(color);

	while(n) {
		if(n>=10) {
			aux.setTipo("Artilleria");
			u.push_back(aux);
			n-=10;
		}
		else if(n>=5) {
			aux.setTipo("Caballeria");
			u.push_back(aux);
			n-=5;
		}
		else {
			aux.setTipo("Infanteria");
			u.push_back(aux);
			n--;
		}
	}

	this->unidades=u;
}

void Territorio::setAdyacentes(std::vector<Territorio*> n) {
	territoriosAdyacentes=n;
}
void Territorio::setOcupado(bool ocupado) {
	this->ocupado=ocupado;
}

bool Territorio::isOcupado() {
	return this->ocupado;
}

void Territorio::print(){
	std::vector<Territorio*>  ady=territoriosAdyacentes;
	std::cout<<'('<<color<<") "<<id<<".  "<<nombre<<" -- "<<ejercito<<": "<<std::endl;
	for(unsigned int i=0;i<ady.size();i++)
				std::cout<<"\t \t \t"<<ady[i]->getID()<<".  "<<ady[i]->getNombre()<<std::endl;
}

std::string Territorio::getColor(){
	return color;
}

void Territorio::setColor(std::string n){
	color=n;
}

//EOF
