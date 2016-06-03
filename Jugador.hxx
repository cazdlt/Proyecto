#include "Jugador.h"

Jugador::Jugador(){
	//pass
	cantidadInfanteria=0;
	id=0;
	color=" ";
	nombre=" ";
}

Jugador::Jugador(std::string nombre, std::string color, int cantidadInfanteria, int nid) {
	this->nombre=nombre;
	this->color=color;
	this->id=nid;
	this->cantidadInfanteria=cantidadInfanteria;

	for(int i=0; i<this->cantidadInfanteria; i++) {
		Figura aux("Infanteria", this->color);
		this->ejercito.push_back(aux);
	}
}
void Jugador::setNombre(std::string nombre) {
	this->nombre=nombre;
}
int Jugador::getID() {
	return id;
}
std::string Jugador::getNombre() {
	return this->nombre;
}
void Jugador::setColor(std::string color) {
	this->color=color;
}
std::string Jugador::getColor() {
	return this->color;
}
void Jugador::setInfanteria(int cantidad) {
	this->cantidadInfanteria=cantidad;
}
int Jugador::getInfanteria() {
	return this->cantidadInfanteria;
}
std::vector<Territorio*> Jugador::getTerritorios() {
	return territorios;
}

bool Jugador::ocupaContinente(Tablero* tablero,std::string nombre) {
	Continente* c0=NULL;
	std::vector<Continente*> ctes=tablero->getContinentes();

	for(std::vector<Continente*>::iterator it=ctes.begin(); it!=ctes.end(); it++) {
		if((*it)->getNombre()==nombre)
			c0=*it;
	}

	if(c0!=NULL) {
		std::vector<Territorio*> t0=c0->getTerritorios();
		std::vector<Territorio*> t1;

		for(std::vector<Territorio*>::iterator it=t0.begin(); it!=t0.end(); it++) {
			for(std::vector<Territorio*>::iterator it1=territorios.begin(); it1!=territorios.end(); it1++) {
				if((*it1)->getNombre()==(*it)->getNombre()) {
					t1.push_back(*it);
					break;
				}
			}
		}

		if(t1.size()==t0.size())
			return true;
	}

	return false;
}

Territorio* Jugador::searchTerritorio(std::string nombre) {
	for(std::vector<Territorio*>::iterator it=territorios.begin(); it!=territorios.end(); it++) {
		if((*it)->getNombre()==nombre)
			return (*it);
	}

	return NULL;
}

Territorio* Jugador::searchTerritorio(unsigned int inputID) {
	for(std::vector<Territorio*>::iterator it=territorios.begin(); it!=territorios.end(); it++) {
		if((*it)->getID()==inputID)
			return (*it);
	}

	return NULL;
}

int Jugador::cambiarCartas() {
	//todo cambiar por comodines
	int cnt=0;
	std::vector<Tarjeta>::iterator it;
	std::stack<Tarjeta*> art;
	std::stack<Tarjeta*> inf;
	std::stack<Tarjeta*> cab;
	std::stack<Tarjeta*> com;

	for(it=tarjetas.begin(); it!=tarjetas.end(); it++) {
		if(!it->isCanjeada()){
			if(it->getFigura()=="Artilleria")
				art.push(&(*it));
			else if(it->getFigura()=="Caballeria")
				cab.push(&(*it));
			else if(it->getFigura()=="Infanteria")
				inf.push(&(*it));
			else if(it->getFigura()=="Comodin")
				com.push(&(*it));
		}
	}

	while(art.size()>=3) {
		for(int i=0; i<3; i++) {
			Tarjeta* tar=art.top();
			std::string terr=tar->getTerritorio();
			tar->setCanjeada(true);
			art.pop();
			Territorio* t0=searchTerritorio(terr);

			if(t0!=NULL) {
				t0->setEjercito(t0->getEjercito()+2);
				std::cout<<"Dos unidades agregadas a "<<t0->getNombre()<<std::endl;
			}
		}

		cnt+=Tarjeta::vCambio;
		Tarjeta::updateVCambio();
	}

	while(cab.size()>=3) {
		for(int i=0; i<3; i++) {
			Tarjeta* tar=cab.top();
			std::string terr=tar->getTerritorio();
			tar->setCanjeada(true);
			cab.pop();
			Territorio* t0=searchTerritorio(terr);

			if(t0!=NULL) {
				t0->setEjercito(t0->getEjercito()+2);
				std::cout<<"Dos unidades agregadas a "<<t0->getNombre()<<std::endl;
			}
		}

		cnt+=Tarjeta::vCambio;
		Tarjeta::updateVCambio();
	}

	while(inf.size()>=3) {
		for(int i=0; i<3; i++) {
			Tarjeta* tar=inf.top();
			std::string terr=tar->getTerritorio();
			tar->setCanjeada(true);
			inf.pop();
			Territorio* t0=searchTerritorio(terr);

			if(t0!=NULL) {
				t0->setEjercito(t0->getEjercito()+2);
				std::cout<<"2 unidades agregadas a "<<t0->getNombre()<<std::endl;
			}
		}

		cnt+=Tarjeta::vCambio;
		Tarjeta::updateVCambio();
	}

	return cnt;

}

void Jugador::obtenerUnidades(Tablero* tablero) {
	int cnt=0;
	//por territorios ocupados
	cnt+=territorios.size()/3;
	std::cout<<std::endl;

	if(cnt)
		std::cout<<cnt<<" unidades otorgadas por los territorios que ocupas."<<std::endl;

	//por continentes ocupados
	if(ocupaContinente(tablero,"South America")) {
		cnt+=2;
		std::cout<<"2 unidades otorgadas por ocupar America del Sur."<<std::endl;
	}

	if(ocupaContinente(tablero,"Australia")) {
		cnt+=2;
		std::cout<<"2 unidades otorgadas por ocupar Australia."<<std::endl;
	}

	if(ocupaContinente(tablero,"Africa")) {
		cnt+=3;
		std::cout<<"3 unidades otorgadas por ocupar Africa."<<std::endl;
	}

	if(ocupaContinente(tablero,"North America")) {
		cnt+=5;
		std::cout<<"5 unidades otorgadas por ocupar America del norte."<<std::endl;
	}

	if(ocupaContinente(tablero,"Europe")) {
		cnt+=5;
		std::cout<<"5 unidades otorgadas por ocupar Europa."<<std::endl;
	}

	if(ocupaContinente(tablero,"Asia")) {
		std::cout<<"7 unidades otorgadas por ocupar Asia."<<std::endl;
		cnt+=7;
	}

	//cambiando cartas
	int cc=cambiarCartas();

	if(cc)
		std::cout<<cc<<" unidades otorgadas cambiando cartas."<<std::endl;

	cnt+=cc;

	ubicarUnidades(cnt,true);
}

void Jugador::ubicarUnidades(int unidades,bool flag) {
	std::string o;
	int n=1,inputID;
	Territorio* t0;
	std::cout<<std::endl<<color<<" -- Ubicando "<<unidades<<" unidades."<<std::endl;

	while(unidades) {
		if(flag)
			std::cout<<"Unidades restantes: "<<unidades<<std::endl;

		std::cout<<"Territorios disponibles -- Ejercito del territorio."<<std::endl;
		printTerritorios();
		std::cout<<"Digite el id del territorio al que desea agregar unidades: ";
		std::cin>>inputID;
		std::cin.ignore();
		t0=searchTerritorio(inputID);

		if(t0==NULL) {
			std::cout<<"Digite un territorio valido.\n\n";
			continue;
		}

		if(flag) {
			std::cout<<"Digite el numero de unidades a agregar a este territorio: ";
			std::cin>>n;
			std::cin.ignore();

			if(n>unidades) {
				std::cout<<"Digite un numero valido de unidades.\n\n";
				continue;
			}
		}

		t0->setEjercito(t0->getEjercito()+n);
		t0->updateUnidades(color);
		unidades-=n;
	}
}



void Jugador::setEjercito(Figura* figura) {
	this->ejercito.push_back(*figura);
}
std::vector<Figura> Jugador::getEjercito() {
	return this->ejercito;
}
void Jugador::restarInfanterias() {
	this->cantidadInfanteria--;
}

void Jugador::setID(int n){
	id=n;
}

int Jugador::printTerritorios() {
	int i=0;
	std::vector<Territorio*>::iterator it;
	
	if(!territorios.empty()) {
		for(it=territorios.begin(); it!=territorios.end(); it++) {
			std::cout<<'\t'<<(*it)->getID()<<". "<<(*it)->getNombre()<<" -- "<<(*it)->getEjercito()<<std::endl;
			i++;
		}
	}
	else
		std::cout<<"No existen territorios."<<std::endl;

	return i;
}

void Jugador::setTerritorios(std::vector<Territorio*> n) {
	territorios=n;
}

bool Jugador::isActive() {
	return !territorios.empty();
}

std::vector<Tarjeta> Jugador::getTarjetas(){
	return tarjetas;
}

void Jugador::setTarjetas(std::vector<Tarjeta> n){
	tarjetas=n;
}

int escojerNumDados(int max,bool flag){
	if(max==1)
		return 1;
	int ndados;
	std::cout<<"\nDigite el numero de tropas a ser utilizadas en "<<(flag? "el ataque" : "la defensa ")<<" (max="<<max<<"): ";
	std::cin>>ndados;;
	std::cin.ignore();
	if(ndados>max || ndados<1){
		std::cout<<"Digite un numero valido de tropas.";
		ndados=0;
	}
	return ndados;
}

void lanzarDados(int& eo,int& ed){
	srand(time(NULL));
	int omax=eo-1;
	int dmax=ed;
	int otropas=0,dtropas=0;
	std::vector<int> odados,ddados;

	if(omax>3)
		omax=3;
	if(dmax>2)
		dmax=2;

	while(!otropas)
		otropas=escojerNumDados(omax,true);

	while(!dtropas)
		dtropas=escojerNumDados(dmax,false);

	for(;otropas;otropas--)
		odados.push_back(rand()%6+1);
	for(;dtropas;dtropas--)
		ddados.push_back(rand()%6+1);

	std::sort(odados.begin(),odados.end(),std::greater<int>());
	std::sort(ddados.begin(),ddados.end(),std::greater<int>());

	std::cout<<"\nLanzamiento del atacante: ";
	for(unsigned int i=0;i<odados.size();i++)
		std::cout<<odados[i]<<" ";
	std::cout<<"\nLanzamiento del defensor: ";
	for(unsigned int i=0;i<ddados.size();i++)
			std::cout<<ddados[i]<<" ";
	std::cout<<std::endl;
	
	int def=0,at=0;
	if(odados[0]>ddados[0]){ //comparando dado mayor
		ed--;
		def++;
	} 
	else{
		at++;
		eo--;
	}
	if(odados.size()>1 && ddados.size()>1){ //si ambos tienen mas de un dado compara el 2do
		if(odados[1]>ddados[1]){ 
			ed--;
			def++;
		}
		else{
			at++;
			eo--;
		} 
	}
	
	if(def) std::cout<<"El defensor ha perdido "<<def<<" unidades."<<std::endl;
	if(at) 	std::cout<<"El atacante ha perdido "<<at<<" unidades.\n"<<std::endl;
	
}

bool realizarAtaque(Territorio* to,Territorio* td) {

	std::string input;
	bool terr=false;
	Jugador* old=td->getJugador();
	Jugador* n=to->getJugador();

	int eo=to->getEjercito(),ed=td->getEjercito();
	int newejercito;
	std::cout<<"\n\n"<<to->getNombre()<<" atacando "<<td->getNombre()<<std::endl;

	while(eo>1&&ed>0) {
		std::cout<<"Ejercito atacante: "<<eo<<" -- Ejercito defensor: "<<ed<<std::endl;
		std::cout<<"Digite \"roll\" para iniciar el ataque o \"cancelar\" para regresar: ";
		getline(std::cin,input);

		if(input=="cancelar")
			break;

		if(input=="roll") {
			lanzarDados(eo,ed);
			if(ed==0) { //territorio ganado
				bool flag=false;
				std::cout<<"\nEl atacante ha conquistado el territorio!"<<std::endl;
				old=td->getJugador();
				n=to->getJugador();
				old->eliminarTerritorio(td->getNombre());
				n->addTerritorio(td);

				while(!flag) {
					std::cout<<"Digite el numero de armadas a traspasar al nuevo territorio (max="<<eo-1<<"): ";
					std::cin>>newejercito;
					std::cin.ignore();

					if(newejercito>=eo) 
						std::cout<<"El territorio atacante debe quedar con al menos una unidad de ejercito."<<std::endl;					
					else {
						ed=newejercito;
						eo=eo-newejercito;
						flag=true;
						terr=true;
					}
				}
				break;
			}

			if(eo==1) 
				std::cout<<"No es posible seguir atacando."<<std::endl;						
		}
	}

	to->setEjercito(eo);
	to->updateUnidades(n->getColor());
	td->setEjercito(ed);

	if(terr)
		td->updateUnidades(n->getColor());
	else
		td->updateUnidades(old->getColor());

	return terr;
}

void Jugador::fortificar(Tablero* tablero) {
	std::string input;
	Territorio* to=NULL;
	Territorio* td=NULL;
	bool found=false,flag=false;
	int newejercito;
	int eo,ed,inputID;

	std::cout<<"\nFORTIFICAR."<<std::endl;

	while(true) {
		std::cout<<"\nTerritorios disponibles -- Ejercito del territorio."<<std::endl;
		printTerritorios();
		std::cout<<"\nDigite el id del territorio donde desea iniciar la fortificacion\nPara cancelar digite \"cancelar\": ";
		getline(std::cin,input);

		if(input=="cancelar")
			break;
		inputID=atoi(input.c_str());
		to=searchTerritorio(inputID);

		if(to==NULL) {
			std::cout<<"Digite un territorio valido."<<std::endl;
			continue;
		}

		if(to->getEjercito()<2) {
			std::cout<<"Para fortificar, el territorio debe tener minimo 2 unidades de ejercito. Por favor seleccione otro."<<std::endl;
			continue;
		}

		while(!found) {
			td=tablero->pickAdyacente(false,this,to);

			if(td!=NULL)
				found=true;
			else
				std::cout<<"Digite un territorio valido.";
		}

		found=false;

		if(td->getNombre()!="0") {
			eo=to->getEjercito();
			ed=td->getEjercito();
			std::cout<<"\n\n"<<to->getNombre()<<" fortificando "<<td->getNombre()<<std::endl;
			std::cout<<"Ejercito origen: "<<eo<<" -- Ejercito destino: "<<ed<<std::endl;

			while(!flag) {
				std::cout<<"Digite el numero de armadas a traspasar al destino: ";
				std::cin>>newejercito;
				std::cin.ignore();

				if(newejercito>=eo) {
					std::cout<<"El territorio origen debe quedar con al menos una unidad de ejercito."<<std::endl;
				}
				else {
					ed+=newejercito;
					eo-=newejercito;
					flag=true;
				}
			}

			to->setEjercito(eo);
			to->updateUnidades(this->color);
			td->setEjercito(ed);
			td->updateUnidades(this->color);
			break;
		}
		else
			delete(td);

	}
}

bool Jugador::atacar(Tablero* tablero) {

	std::string input;
	Territorio* to=NULL;
	Territorio* td=NULL;
	bool found=false;
	bool terr=false;
	int inputID=0;

	std::cout<<"\nATACAR."<<std::endl;

	while(true) {
		std::cout<<"\nTerritorios disponibles -- Ejercito del territorio."<<std::endl;
		printTerritorios();
		std::cout<<"\nDigite el id del territorio donde desea iniciar el ataque\nPara cancelar el ataque digite \"cancelar\": ";
		getline(std::cin,input);

		if(input=="cancelar")
			break;
		inputID=atoi(input.c_str());
		to=searchTerritorio(inputID);

		if(to==NULL) {
			std::cout<<"Digite un territorio valido."<<std::endl;
			continue;
		}

		if(to->getEjercito()<2) {
			std::cout<<"Para atacar, el territorio debe tener minimo 2 unidades de ejercito. Por favor seleccione otro."<<std::endl;
			continue;
		}

		while(!found) {
			td=tablero->pickAdyacente(true,this,to);

			if(td!=NULL)
				found=true;
			else
				std::cout<<"Digite un territorio valido.";
		}

		found=false;

		if(td->getNombre()!="0"){
			if(realizarAtaque(to,td))
				terr=true;
		}
		else
			delete(td);

	}

	//obtiene una carta si conquistó al menos un territorio
	if(terr) {
		std::stack<Tarjeta>* aux=tablero->getTarjetas();
		Tarjeta tar = aux->top();
		aux->pop();
		this->tarjetas.push_back(tar);
		std::cout<<"\nHaz obtenido la carta "<<tar<<std::endl;
		return true;
	}

	return false;
}

void Jugador::eliminarTerritorio(std::string nombret) {
	std::vector<Territorio*>::iterator it;

	for(it=territorios.begin(); it!=territorios.end(); it++) {
		if((*it)->getNombre()==nombret)
			break;
	}
	territorios.erase(it);
}

void Jugador::addTerritorio(Territorio* t0) {
	t0->setJugador(this);
	territorios.push_back(t0);
	t0->setOcupado(true);
	t0->setColor(color);
	std::sort(territorios.begin(),territorios.end());
}

int Jugador::costoConquista(Territorio* des,std::vector<Territorio*>& tts,Ruta& ret){
	
	std::vector<TArista> MST,r,mejorRuta;
	
	Territorio* src=NULL;
	bool flag=false;
	MST=des->rutaATodos(tts); //arbol desde el destino
			
	for(unsigned int i=0;i<MST.size();i++){
		if(tts[MST[i].des-1]->getJugador()==this){ //si encuentra un territorio propio
			src=tts[MST[i].des-1];
			if(src->getEjercito()>1){ //si tiene el ejercito suficiente
				MST=src->rutaATodos(tts); //hay que volver a verificar las rutas???.. creo que no pero funciona y ya no da el tiempo revisar
				r=encontrarRuta(src->getID(),des->getID(),MST); 
				if(!flag){ //si no tiene uno mejor pues este es
					mejorRuta=r;
					flag=true;
				}
				else if(r[r.size()-1].dist<mejorRuta[mejorRuta.size()-1].dist ) //compara el mejor anterior con el nuevo					
					mejorRuta=r;				
			}
		}
	}

			
	/* hecho a lo viejo  revisando todos los propios
	for(unsigned int i=0;i<territorios.size();i++){
		src=territorios[i];
		MST=src->rutaATodos(tts);		
		
		std::cout<<std::endl;
		if(i==0)
			mejorRuta=r;
		else
			if(r[r.size()-1].dist<mejorRuta[mejorRuta.size()-1].dist)
				mejorRuta=r;
	}
	std::cout<<"mejor ruta"<<std::endl;
		for(unsigned int j=0;j<mejorRuta.size();j++)
			std::cout<<mejorRuta[j]<<" ";
	* */
	
	//solo los indices
	ret.reserve(mejorRuta.size()+1);
	for(unsigned int i=0;i<mejorRuta.size();i++){
		if(i==0)
			ret.push_back(mejorRuta[i].src);
		ret.push_back(mejorRuta[i].des);		
	}

	return mejorRuta[mejorRuta.size()-1].dist;
}

TArista anterior(std::vector<TArista>& MST,unsigned int& src){
	
	TArista aux;
	for(unsigned int i=0;i<MST.size();i++){
				if(src==MST[i].des){
					src=MST[i].src;
					aux= MST[i];
					break;
				}
	}
	return aux;
}

std::vector<TArista> encontrarRuta(unsigned int src,unsigned int des,std::vector<TArista>& MST){
	
	std::vector<TArista> ret;
	std::deque<TArista> ruta;
	unsigned int curr;
	
	curr=des;			
	for(unsigned int i=0;i<MST.size();i++)
		if(MST[i].des==des){
			ruta.push_front(MST[i]);
			break;
		}
		
	while(ruta[0].src!=src)
		ruta.push_front(anterior(MST,curr));			
	
	if(ruta.size()>1)
		ruta.pop_back(); //idk como arreglarlo lul
		
	ret.insert(ret.end(),ruta.begin(),ruta.end());
	
	return ret;
}

Territorio* Jugador::mejorConquista(std::vector<Territorio*>& tts){
	Territorio* menor;
	int menorEjercito=99999999;
	std::vector<Territorio*> ady;
	for(unsigned int i=0;i<territorios.size();i++){
		ady=territorios[i]->getTerritoriosA();
		for(unsigned int j=0;j<ady.size();j++){
			if(ady[j]->getJugador()==this){				
				if(ady[j]->getEjercito()<(int)menorEjercito){
					menorEjercito=ady[j]->getEjercito();
					menor=ady[i];
				}						
			}
		}
	}
	return menor;
}

//EOF