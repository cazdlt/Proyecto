#include "Territorio.h"

unsigned int Territorio::CURR_ID=1;

TArista::TArista(){
	src=-1;
	dist=0;
}

TArista::TArista(unsigned int s, unsigned int d, float peso){
		src=s;
		des=d;
		dist=peso;
}

bool operator> (const TArista& a, const TArista& b){
    return a.dist> b.dist; 
}

std::ostream& operator<<(std::ostream& o,TArista& obj){
	o<<obj.src<<"-("<<obj.dist<<")-"<<obj.des;
	return o;
}

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

int Territorio::obtenerCostoEjercito(Territorio* des){
	int w=0;
	
	for(unsigned int i=0;i<territoriosAdyacentes.size();i++){
		if(territoriosAdyacentes[i]==des)
			w=territoriosAdyacentes[i]->getEjercito();
	}
	
	return w;
}

int buscarDijsktra(unsigned int index,std::vector<TArista> n){
	for(unsigned int i=0;i<n.size();i++){
		if(n[i].des==index)
			return i;
	}
	return -1;
}

Territorio* buscarTerritorioGrafo(std::vector<Territorio*>& tts, unsigned int id){
	
	for(unsigned int i=0;i<tts.size();i++){
			if(id==tts[i]->getID())
				return tts[i];
	
	}
	return NULL;
}

std::vector<TArista> Territorio::rutaATodos(std::vector<Territorio*>& tts){ //si da tiempo hacer que solo vaya hasta  un nodo destino
	
	TArista aux;
	std::vector<TArista> nodos,MST;
	Territorio* curr=NULL;
	std::vector<Territorio*> ady;
	int auxDist;
	int adyIndex,adyIndexDijkstra;
	unsigned int src=this->id;	

	//init
	for(unsigned int i=0;i<tts.size();i++){
		aux.des=tts[i]->getID();
		if(src==aux.des)
			aux.dist=0;
		else
			aux.dist=99999999;
		nodos.push_back(aux);
	}
	
	while(!nodos.empty()){
		
		std::sort(nodos.begin(),nodos.end(),std::greater<TArista>());
		aux=nodos.back();
		nodos.pop_back();
		
		if(aux.des!=src)
			MST.push_back(aux);
			
		curr=buscarTerritorioGrafo(tts,aux.des);
		ady=curr->getTerritoriosA();
		for(unsigned int j=0;j<ady.size();j++){
			adyIndex=ady[j]->getID()-1;
			adyIndexDijkstra=buscarDijsktra(adyIndex+1,nodos);
			if(adyIndexDijkstra>=0){
				auxDist=aux.dist+curr->obtenerCostoEjercito(tts[adyIndex]);
				if(auxDist<nodos[adyIndexDijkstra].dist){
					TArista temp(aux.des,adyIndex+1,auxDist);
					nodos[adyIndexDijkstra]=temp;
				}
			}
		}
	}
		
	return MST;
}
//EOF
