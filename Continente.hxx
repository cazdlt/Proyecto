#include "Continente.h"


Continente::Continente(std::string nombre)
{
    this->nombre=nombre;
}

Continente::~Continente(){
	for(unsigned int i=0;i<territorios.size();i++)
		delete territorios[i];
	territorios.clear();
}

void Continente::setNombre(std::string nombre)
{
    this->nombre=nombre;
}

void Continente::print(){
	std::cout<<nombre<<": \n";
    for(std::vector<Territorio*>::iterator it=territorios.begin();it!=territorios.end();it++){
		std::cout<<'\t';
       (*it)->print();
    }
}

std::string Continente::getNombre()
{
    return this->nombre;
}


std::vector<Territorio*> Continente::getTerritorios()
{
    return territorios;
}
void Continente::AgregarTerritorio(Territorio* ter)
{
    this->territorios.push_back(ter);
}

//EOF