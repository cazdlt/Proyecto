#include "Juego.h"

int main() {
	//----------------VARIABLES-----------------
	std::string entrada;
	Juego juego;
	//----------------COMANDOS------------------
	juego.inicializar("lul");
	juego.print();
	juego.costoConquista("China");
	std::cout<<"Bienvenido al juego. RISK."<<std::endl;

	do{
		std::cout<<"$ ";
		getline(std::cin,entrada);

		if(entrada.find("inicializar")==0) {
			if(!juego.getEstado())
				std::cout<<"El juego ya esta en curso."<<std::endl;
			else if(juego.getEstado()==2){
				std::cout<<"Juego finalizado. Iniciando nueva partida."<<std::endl;
				if(juego.inicializar())
                    std::cout<<"Juego inicializado."<<std::endl;
			}
			else{
				if(entrada.size()>12){
					if(juego.inicializar(entrada.substr(12)))
						std::cout<<"Juego inicializado.";
				}
				else if(juego.inicializar())
					std::cout<<"Juego inicializado.";
			}
            std::cout<<std::endl;
		}

		else if(entrada.find("ayuda")==0) {
			if(entrada.size()>5)
				juego.help(entrada.substr(5));
			else
				juego.help();
		}

		else if(entrada.find("turno")==0) {
			if(!juego.getEstado()) {
				if(entrada.size()>6) {
					int flag=juego.jugarTurno(atoi(entrada.substr(6).c_str()));

					if(!flag){
						std::cout<<"Turno completado correctamente."<<std::endl;
					}
					else if(flag==1)
						std::cout<<"Turno invalido."<<std::endl;
					else if(flag==2)
						std::cout<<"Jugador invalido."<<std::endl;
				}
				else
					std::cout<<"Turno actual: "<<Juego::turno<<std::endl;
			}
			else if(juego.getEstado()==1)
				std::cout<<"No existe ningun juego activo."<<std::endl;
			else if(juego.getEstado()==2)
				std::cout<<"Juego finalizado."<<std::endl;
		}
		else if(entrada.find("ver")==0){
            if(entrada.size()>4)
                juego.ver(entrada.substr(4));
			else
				juego.print();
		}
		else if(entrada.find("guardar")==0&&entrada.size()>8){
			juego.save(entrada.substr(8));
		}
		else if(entrada=="conquista_mas_barata"){			
			juego.mejorConquista();
		}
		else if(entrada.find("costo_conquista")==0 && entrada.size()>16){
			juego.costoConquista(entrada.substr(16));
		}
		else if(entrada!="salir"&&entrada!="")
            std::cout<<"Comando no encontrado. Digite help para visualizar las opciones disponibles."<<std::endl;
	}while(entrada!="salir");

	return 0;
}
