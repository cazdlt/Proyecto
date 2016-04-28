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
	friend  std::ostream& operator<<(std::ostream &o, const Tarjeta& t);
	friend bool operator==(const Tarjeta& t1,const Tarjeta& t2); 
	
	//CONSTRUCTORES
    Tarjeta();
	Tarjeta(std::string t , std::string f , bool c);
	
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
