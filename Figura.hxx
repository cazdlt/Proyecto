#include "Figura.h"

Figura::Figura()
{

}
Figura::Figura(std::string tipo,std::string color)
{
    this->tipo = tipo;
    this->color = color;
}
std::string Figura::getTipo()
{
    return this->tipo;
}
void Figura::setTipo(std::string tipo)
{
    this->tipo = tipo;
}
std::string Figura::getColor()
{
    return this->color;
}
void Figura::setColor(std::string color)
{
    this->color = color;
}

/*
void Figura::setUbicacion(Territorio* ter)
{
    this->ubicacion=ter;
}
Territorio* Figura::getUbicacion()
{
    return this->ubicacion;
}
*/
