#include "Tarjeta.h"

int Tarjeta::vCambio=4;

 std::ostream& operator<<(std::ostream &o, const Tarjeta& t){ 
         o<<t.figura<<" "<<t.territorio;
         return o;            
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
