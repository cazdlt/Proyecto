#include "Tarjeta.h"

int Tarjeta::vCambio=4;

 std::ostream& operator<<(std::ostream &o, const Tarjeta& t){ 
         o<<t.figura<<" "<<t.territorio;
         return o;            
}

bool operator==(const Tarjeta& t1,const Tarjeta& t2){
	return (t1.territorio==t2.territorio)&&(t1.figura==t2.figura);
}

Tarjeta::Tarjeta(){
    territorio="";
    figura="";
    canjeada=false;
}

Tarjeta::Tarjeta(std::string t , std::string f , bool c){
    territorio=t;
    figura=f;
    canjeada=c;
}

char Tarjeta::getTipo(){
    return tipo;
}

std::string Tarjeta::getTerritorio(){
    return territorio;
}

std::string Tarjeta::getFigura(){
    return figura;
}

std::string Tarjeta::getID(){
	char c=(canjeada?'1':'0');
	return territorio+" "+figura[0]+" "+c;
}

bool Tarjeta::isCanjeada(){
    return canjeada;
}

void Tarjeta::setCanjeada(bool n){
    canjeada=n;
}

void Tarjeta::setTipo(char n){
    tipo=n;
}

void Tarjeta::setTerritorio(std::string n){
    territorio=n;
}

void Tarjeta::setFigura(std::string n){
    figura=n;
}

void Tarjeta::updateVCambio(){
    if(vCambio<12)
        vCambio+=2;
    else if(vCambio==12)
        vCambio=15;
    else
        vCambio+=5;
}

//EOF