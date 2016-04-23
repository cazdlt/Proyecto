#include "Juego.h"

unsigned int Juego::turno=1;

Juego::Juego() {
	tablero=NULL;
	estado=1;
}

Juego::~Juego() {
	delete(tablero);
}

int Juego::getEstado() {
	return estado;
}
std::vector<Jugador> Juego::getJugadores() {
	return jugadores;
}

std::stack<Tarjeta> fillTarjetas(Tablero* t0) {
	//vars
	std::vector<Tarjeta> ret;
	Tarjeta aux;
	std::vector<Continente*> ctes=t0->getContinentes();
	std::vector<Territorio*> ttos;
	std::vector<Continente*>::iterator itC;
	std::vector<Territorio*>::iterator itT;
	int i=0;

	//llenando vector de cartas a mezclar
	for(itC=ctes.begin(); itC!=ctes.end(); itC++) {
		ttos=(*itC)->getTerritorios();

		for(itT=ttos.begin(); itT!=ttos.end(); itT++) {
			std::string tto=(*itT)->getNombre();
			aux.setTerritorio(tto);
			aux.setTipo('n');
			std::string f;

			if(i<15)
				f="Artilleria";
			else if(i<30)
				f="Caballeria";
			else
				f="Infanteria";

			aux.setFigura(f);

			ret.push_back(aux);
			i++;
		}
	}

	//comodines
	aux.setTerritorio("");
	aux.setTipo('c');
	aux.setFigura("Comodin");
	ret.push_back(aux);
	ret.push_back(aux);

	//cartas de mision????????
	/*
	for(int i=0; i<12; i++)
	{
	    aux.setTerritorio("");
	    aux.setTipo('m');
	    aux.setFigura("Mision");
	    ret.push_back(aux);
	}
	*/

	//mezclando
	random_shuffle(ret.begin(),ret.end());

	//agregando a stack
	std::stack<Tarjeta> auxT;

	for(std::vector<Tarjeta>::iterator it0=ret.begin(); it0!=ret.end(); it0++)
		auxT.push(*it0);

	return auxT;
}

int updateTurno(Juego* j0) {
	unsigned int i=j0->turno+1;
	std::vector<Jugador> j=j0->getJugadores();
	Jugador* next;

	while(true) {
		if(i>j.size())
			i=1;

		next=j0->searchJugador(i);

		if(next->isActive())
			return i;

		i++;
	}
}

std::string pickColor(std::vector<std::string>& disp) {

	std::string cor;
	std::vector<std::string>::iterator it;

	std::cout<<"Colores disponibles:\n";

	for(unsigned int i=0; i<disp.size(); i++)
		std::cout<<'\t'<<disp[i]<<std::endl;

	while(true) {
		std::cout<<"\nElige tu color: ";
		getline(std::cin,cor);
		cor[0]=toupper(cor[0]);
		it=std::find(disp.begin(),disp.end(),cor);

		if(it==disp.end())
			std::cout<<"Color invalido. Por favor elige otro."<<std::endl;
		else {
			disp.erase(it);
			return cor;
		}
	}

}

bool Juego::inicializar() {

	std::vector<std::string> cor= {"Azul","Verde","Amarillo","Rojo","Blanco","Negro"};
	int cantidadJugadores=0,cantidadFiguras=0;
	std::vector<Jugador> auxj;
	std::vector<int> dados;
	std::string nombreJ,color;
	
	std::cout<<"Digite la cantidad de jugadores: ";
	std::cin>>cantidadJugadores;
	std::cin.ignore();

	if(cantidadJugadores==3) {
		cantidadFiguras=5;
	}
	else if(cantidadJugadores==4) {
		cantidadFiguras=30;
	}
	else if(cantidadJugadores==5) {
		cantidadFiguras=25;
	}
	else if(cantidadJugadores==6) {
		cantidadFiguras=20;
	}
	else if(cantidadJugadores<3) {
		std::cout<<"No puedes estar tan solo para jugar este juego"<<std::endl;
		return false;
	}
	else {
		std::cout<<"Existen muchos jugadores en la partida deberian sacar a alguno"<<std::endl;
		return false;
	}
	
	tablero=new Tablero();
	tablero->setTarjetas(fillTarjetas(tablero));

	for(int i=0; i<cantidadJugadores; i++) {
		std::cout<<"Elige un nombre: ";
		getline(std::cin,nombreJ);
		color=pickColor(cor);
		Jugador* aux= new Jugador(nombreJ, color, cantidadFiguras, i+1);
		auxj.push_back(*aux);
	}
	std::cout<<std::endl;
	
	for(int i=0; i<cantidadJugadores; i++){
		int z=rand()%6+1;
		std::cout<<"Lanzamiento de "<<auxj[i].getColor()<<": "<<z<<std::endl;
		dados.push_back(z);
	}
	
	Jugador tempj;
	int temp;
	for(int i=0; i<cantidadJugadores; i++){
		for(int j=0;j<cantidadJugadores-1;j++){
			if(dados[j+1]>dados[j]){
				temp=dados[j];
				dados[j]=dados[j+1];
				dados[j+1]=temp;
				tempj=jugadores[j];
				jugadores[j]=jugadores[j+1];
				jugadores[j+1]=tempj;
			}
		}
	}
	
	
	int id,cnt=0,tot=0;
	std::vector<Continente*> continentes=tablero->getContinentes();
	std::vector<Jugador>::iterator itj;
	Territorio* t0=NULL;
	
	for(unsigned int i=0;i<continentes.size();i++)
		tot+=continentes[i]->getTerritorios().size();
	
	//colonizando
	while(cnt<tot) {
		for(itj=jugadores.begin(); itj!=jugadores.end()&&cnt<tot; itj++) {
			std::cout<<"\nTerritorios disponibles."<<std::endl;
            tablero->printDisponibles();
			
			while(t0==NULL) {
				std::cout<<'('<<itj->getColor()<<") Digite el id del territorio a colonizar: ";
				std::cin>>id;
				std::cin.ignore();
				t0=tablero->searchTerritorioDisponible(id);

				if(t0==NULL)
					std::cout<<"Seleccione un territorio valido."<<std::endl;
				else {
					t0->setEjercito(1);
					itj->addTerritorio(t0);
					itj->setInfanteria(itj->getInfanteria()-1);
				}
			}

			t0=NULL;
			cnt++;
		}
	}
	
	
	//llenando y ordenando territorios
	int canttotal=0;

	for(itj=jugadores.begin(); itj!=jugadores.end(); itj++){
		canttotal+=itj->getInfanteria();
		std::vector<Territorio*>  tmp=itj->getTerritorios();
		std::sort(tmp.begin(),tmp.end());
		itj->setTerritorios(tmp);
	}


	while(canttotal>0) {
		for(unsigned int i=0; i<jugadores.size()&&canttotal; i++) {
			if(jugadores[i].getInfanteria()) {
				std::cout<<"\nUnidades restantes: "<<jugadores[i].getInfanteria();
				jugadores[i].ubicarUnidades(1,false);
				jugadores[i].setInfanteria(jugadores[i].getInfanteria()-1);
				canttotal--;
			}
		}
	}

	estado=0;
	turno=1;
	return true;
}

Jugador* Juego::searchJugador(int player) {
	std::vector<Jugador>::iterator it;

	for(it=jugadores.begin(); it!=jugadores.end(); it++) {
		if(it->getID()==player)
			return &(*it);
	}

	return NULL;
}

Jugador* Juego::searchJugador(std::string player) {
	std::vector<Jugador>::iterator it;
	player[0]=toupper(player[0]);

	for(it=jugadores.begin(); it!=jugadores.end(); it++) {
		if(it->getColor()==player)
			return &(*it);
	}

	return NULL;
}

int Juego::jugarTurno(int player) {

	Jugador* j0=searchJugador(player);
	bool terr=false;
	bool estados[jugadores.size()];
	bool newestados[jugadores.size()];
	int cntactive=0;

	for(unsigned int i=0; i<jugadores.size(); i++) {
		estados[i]=jugadores[i].isActive();
	}

	if(j0==NULL)
		return 2;
	else if((int)turno!=player)
		return 1;

	std::cout<<"\n\nTURNO."<<std::endl
	         <<j0->getID()<<". "<<j0->getColor()<<" -- "<<j0->getNombre()<<std::endl;

	//turno
	j0->obtenerUnidades(tablero);
	terr=j0->atacar(tablero);
	j0->fortificar(tablero);
	std::cout<<std::endl;

	if(terr) { //check eliminado
		for(unsigned int i=0; i<jugadores.size(); i++)
			newestados[i]=jugadores[i].isActive();

		for(unsigned int i=0; i<jugadores.size(); i++) {
			if(newestados[i]!=estados[i]) {
				std::cout<<"El jugador "<<j0->getColor()<<" ha eliminado a "<<jugadores[i].getColor()<<"!\n";
			}

			if(newestados[i])
				cntactive++;
		}

		if(cntactive==1) { //check ganador
			std::cout<<"El jugador "<<j0->getColor()<<" es el ganador!"<<std::endl;
			this->estado=2;
		}

	}

	turno=updateTurno(this);
	return 0;
}

void Juego::help() {
	std::cout<<"\nCOMANDOS:\n"
	         <<"\tinicializar-- inicia una nueva partida\n"
	         <<"\tturno-- imprime el turno actual\n"
	         <<"\tturno [id]-- juega el turno de [id]\n"
	         <<"\ayuda-- imprime ayuda de comandos\n"
	         <<"\ayuda [comando]-- imprime ayuda sobre [comando]\n"
			 <<"\tver-- imprime informacion de los territorios\n"
	         <<"\tver [color]-- imprime la informacion de los territorios del jugador con [color]\n"
	         <<"\tver [id]-- imprime la informacion de los territorios del jugador con [id]\n"
			 <<"\tver jugadores-- imprime estado de jugadores de la partida\n"
	         <<"\tsalir-- sale de la aplicacion\n\n";
}

void Juego::help(std::string h) {
	//TODO
	if(h=="inicializar") {
		std::cout<<"\n\nINICIALIZAR:\n"
		         <<"inicializar-- Inicia una nueva partida.\n\n";
	}
	else if(h=="turno") {
		std::cout<<"\n\nTURNO:\n"
		         <<"\tturno [id]-- Si es el turno de jugador [id], entra a jugarlo.\n"
		         <<"\tturno-- imprime el id del jugador del turno actual.\n\n";

	}
}

void Juego::printJugadores() {
	std::vector<Jugador>::iterator it;

	if(!jugadores.empty())
		for(it=jugadores.begin(); it!=jugadores.end(); it++) {
			if(it->isActive())
				std::cout<<it->getID()<<". "<<it->getColor()<<" -- "<<it->getNombre()<<" -- Activo"<<std::endl;
			else
				std::cout<<it->getID()<<". "<<it->getColor()<<" -- "<<it->getNombre()<<" -- Eliminado"<<std::endl;
		}
	else std::cout<<"No hay jugadores en esta partida."<<std::endl;
}

Tablero* Juego::getTablero() {
	return tablero;
}

void Juego::ver(std::string input) {
	//TODO VER CONTINENTE TERRITORIO CARTASDELTURNO STATS
	Jugador* j0=NULL;
	
	if(input=="jugadores"){
            std::cout<<"Jugadores en esta partida."<<std::endl;
            printJugadores();
            std::cout<<std::endl;
			return;
	}
		
	if(atoi(input.c_str()))
		j0=searchJugador(atoi(input.c_str()));
	else
		j0=searchJugador(input);

	if(j0==NULL) {
		std::cout<<"Jugador no encontrado."<<std::endl<<std::endl;
		return;
	}

	std::string color=j0->getColor();
	color[0]=toupper(color[0]);
	std::cout<<"Territorios de "<<j0->getID()<<". "<<color<<std::endl;
	j0->printTerritorios();
	std::cout<<std::endl;

}

void Juego::print(){
	if(tablero!=NULL)
		tablero->print();
	else
		std::cout<<"Juego no iniciado.\n"<<std::endl;
}

//EOF
