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
//test
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

int escogerFiguras(int cantidadJugadores){
	if(cantidadJugadores==3) {
		return 35;
	}
	else if(cantidadJugadores==4) {
		return 30;
	}
	else if(cantidadJugadores==5) {
		return 25;
	}
	else if(cantidadJugadores==6) {
		return 20;
	}
	else if(cantidadJugadores<3) {
		std::cout<<"No puedes estar tan solo para jugar este juego"<<std::endl;
		return 0;
	}
	else {
		std::cout<<"Existen muchos jugadores en la partida deberian sacar a alguno"<<std::endl;
		return 0;
	}
}

bool Juego::llenarJugadores(int cantidadJugadores){
	
	srand(time(0));
	std::vector<int> dados;
	std::string nombreJ,color;
	int cantidadFiguras;
	std::vector<std::string> cor= {"Azul","Verde","Amarillo","Rojo","Blanco","Negro"};
		
	cantidadFiguras=escogerFiguras(cantidadJugadores);
	if(!cantidadFiguras)
		return false;
		
	for(int i=0; i<cantidadJugadores; i++) {
		std::cout<<"\nElige un nombre: ";
		getline(std::cin,nombreJ);
		color=pickColor(cor);
		Jugador auxj(nombreJ, color, cantidadFiguras, i+1);
		jugadores.push_back(auxj);
	}
		
	std::cout<<std::endl;
	
	for(int i=0; i<cantidadJugadores; i++){
		int z=rand()%6+1;
		std::cout<<"Lanzamiento de "<<jugadores[i].getColor()<<": "<<z<<std::endl;
		dados.push_back(z);
	}
	std::cout<<"Digite una tecla para continuar..."<<std::endl;
	std::cin.get();

	for(int i=0; i<cantidadJugadores; i++){
		for(int j=0;j<cantidadJugadores-1;j++){
			if(dados[j]<dados[j+1]){
				std::swap(dados[j],dados[j+1]);		
				std::swap(jugadores[j],jugadores[j+1]);
			}
		}
	}
	for(int i=0;i<cantidadJugadores;i++)
		jugadores[i].setID(1+i);
	
	return true;
}

bool Juego::inicializar() {
	
	Territorio::CURR_ID=1;
	int cantidadJugadores=0;
	int id,cnt=0,tot=0;
	std::vector<Continente*> continentes=tablero->getContinentes();
	std::vector<Jugador>::iterator itj;
	Territorio* t0=NULL;
	
	std::cout<<"Digite la cantidad de jugadores: ";
	std::cin>>cantidadJugadores;
	std::cin.ignore();
	
	if(!llenarJugadores(cantidadJugadores))
		return false;
	
	tablero=new Tablero();
	tablero->fillTarjetas();
	
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

std::vector<std::string> splitstring(const std::string &s, char token) {
    std::vector<std::string> ret;
	std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, token)) {
		if(!item.empty())
			ret.push_back(item);
    }
    return ret;
}

bool Juego::save(std::string input){
	std::vector<std::string> in=splitstring(input,' ');
	
	if(in.size()>1){
		if(in[0]=="comprimido")
			std::swap(in[0],in[1]);
		else{
			std::cout<<"Comando invalido. Digite help para visualizar las opciones disponibles."<<std::endl;
			return false;
		}			
	}
	
	std::ofstream arch(in[0]);
	if(arch.is_open()){
		guardarPartida(arch,jugadores);
		arch.close();
	}
	else{
		std::cout<<"Error de archivo."<<std::endl;
		return false;
	}
	
	if(in.size()>1) //TODO
		comprimir(in[0]);
	
	
	return true;
}

/**
 *	FORMATO:
 * 	"txt"
 * 	cantidadJugadores*turno*valorCambioTarjetas
 * 	color*nombre
 * 	*carta1*carta2*cartaN /////carta=="figura territorio-canjeada"
 * 	*territorio1*territorioN /////territorio=="id-ejercito"
 * 	color*nombre
 * 	...........
 * 	
 * */
bool guardarPartida(std::ofstream& file,std::vector<Jugador> jugadores){ 
	unsigned int sz=jugadores.size();
	std::vector<Tarjeta> tjs;
	std::vector<Territorio*> tts;
	
	file<<"txt"<<std::endl;
	file<<sz<<"*"<<Juego::turno<<"*"<<Tarjeta::vCambio<<std::endl;
	for(unsigned int i=0;i<sz;i++){
		file<<jugadores[i].getColor()<<"*"<<jugadores[i].getNombre()<<std::endl;
		tjs=jugadores[i].getTarjetas();
		tts=jugadores[i].getTerritorios();
		
		for(unsigned int j=0;j<tjs.size();j++)
			file<<"*"<<tjs[j]<<"-"<<tjs[j].isCanjeada();
		file<<std::endl;
		for(unsigned int j=0;j<tts.size();j++)
			file<<"*"<<tts[j]->getID()<<"-"<<tts[j]->getEjercito();
		file<<std::endl;
	}
	return true;
}

/**
 * @param t1: vector con las cartas ya en mano
 * @param t2: vector con todas las cartas
 * @return  stack mezclado sin las cartas ya en mano
 **/
std::stack<Tarjeta> compararTarjetas(std::vector<Tarjeta>& t1,std::vector<Tarjeta>& t2){
	
	std::vector<std::vector<Tarjeta>::iterator> vit;
	for(std::vector<Tarjeta>::iterator it=t1.begin() ; it!=t1.end() ; it++){
		if(find(t2.begin(),t2.end(),*it) != t2.end())
			vit.push_back(it);
	}
	for(unsigned int i=0;i<vit.size();i++)
		t2.erase(vit[i]);
	
	random_shuffle(t2.begin(),t2.end());
	
	std::stack<Tarjeta> auxT;
	for(std::vector<Tarjeta>::iterator it0=t2.begin(); it0!=t2.end(); it0++)
		auxT.push(*it0);
		
		
	return auxT;
}

bool Juego::inicializar(std::string input) {
	
	Territorio::CURR_ID=1;
	std::ifstream arch(input);
	std::string line;
	tablero=new Tablero();
	
	
	if(arch.is_open()){
		getline(arch,line);
		if(line=="txt")
			textinit(arch);
		//else usar el comprimido
		arch.close();
		return true;
	}
	else{
		std::cout<<"Error de archivo.";
		return false;
	}
}

void Juego::textinit(std::ifstream& arch){
	
	std::string line;
	std::vector<std::string> in,sp;
	int i=0,cnt=0;
	std::vector<Tarjeta> vt,tarjetas=allTarjetas(tablero);
	
	while(getline(arch,line)){
			
			in=splitstring(line,'*');
			
			if(i==0){ //datos juego
				turno=atoi(in[1].c_str());
				Tarjeta::vCambio=atoi(in[2].c_str());
			}
			if(i==1){ //datos jugador
				cnt++;
				Jugador auxj(in[1],in[0],0,cnt);
				jugadores.push_back(auxj);
			}
			else if(i==2){ //cartas jugador
				std::vector<Tarjeta> jt;
				for(unsigned int j=0;j<in.size();j++){ //para cada carta agregar a vector
					sp=splitstring(in[j],'-');
					std::vector<std::string> tar=splitstring(sp[0],' ');
					bool canjeada=(sp[1]=="0"?false:true);
					Tarjeta auxt(tar[1],tar[0],canjeada);
					jt.push_back(auxt);
					vt.push_back(auxt);
				}
				jugadores[cnt-1].setTarjetas(jt);
			}
			else if(i==3){ //territorios jugador
				for(unsigned int j=0;j<in.size();j++){
					sp=splitstring(in[j],'-');
					Territorio* t0=tablero->searchTerritorio(atoi(sp[0].c_str()));
					t0->setEjercito(atoi(sp[1].c_str()));
					jugadores[cnt-1].addTerritorio(t0);
				}
				i=0;
			}
			i++;
		}
		tablero->setTarjetas(compararTarjetas(vt,tarjetas));
		estado=0;
}

bool comprimir(std::string in){
	//TODO
	return true;
}

//EOF
