#ifndef __FIGURA_H__
#define __FIGURA_H__

#include <iostream>

class Figura{
    protected:
        std::string tipo;
        std::string color;
	public:
		//CONSTRUCTORES
        Figura();
        Figura(std::string,std::string);
		
		//ACCESO
        std::string getTipo();
        void setTipo(std::string);
        std::string getColor();
        void setColor(std::string);
};

#include "Figura.hxx"
#endif // FIGURA_H
