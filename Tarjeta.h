#ifndef __TARJETA_H__
#define __TARJETA_H__

#include "Territorio.h"
#include "Figura.h"
#include <vector>

class Tarjeta{
protected:
    std::string territorio;
    char tipo;
    std::string figura;
    bool canjeada;
public:
    static int vCambio;
	static void updateVCambio();
	 
	//CONSTRUCTORES
    Tarjeta();
	
	//ACCESO
    char getTipo();
    std::string getTerritorio();
    std::string getFigura();
    bool isCanjeada();
    void setCanjeada(bool n);
    void setTerritorio(std::string n);
    void setFigura(std::string n);
	void setTipo(char n);
};

#include "Tarjeta.hxx"

#endif
