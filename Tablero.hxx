#include "Tablero.h"

Tablero::Tablero() {

	//CONTINENTES
	Continente* AmericaN= new Continente("North America");
	Continente* AmericaS= new Continente("South America");
	Continente* Europe= new Continente("Europe");
	Continente* Africa= new Continente("Africa");
	Continente* Asia= new Continente("Asia");
	Continente* Australia= new Continente("Australia");

	//AFRICA
	Territorio* Congo= new Territorio("Congo");
	Territorio* AfricaOriental= new Territorio("Africa Oriental");
	Territorio* Egipto= new Territorio("Egipto");
	Territorio* Madagascar= new Territorio("Madagascar");
	Territorio* AfricaDelNorte= new Territorio("Africa del Norte");
	Territorio* AfricaDelSur= new Territorio("Africa del Sur");

	//NA
	Territorio* Alaska= new Territorio("Alaska");
	Territorio* Alberta= new Territorio("Alberta");
	Territorio* AmericaCentral= new Territorio("America Central");
	Territorio* EstadosUnidosOrientales= new Territorio("Estados Unidos Orientales");
	Territorio* Groenlandia= new Territorio("Groenlandia");
	Territorio* TerritorioNoroccidental= new Territorio("Territorio Noroccidental");
	Territorio* Ontario= new Territorio("Ontario");
	Territorio* Quebec= new Territorio("Quebec");
	Territorio* EstadosUnidosOccidentales= new Territorio("Estados Unidos Occidentales");

	//AUS
	Territorio* AustraliaOriental= new Territorio("Australia Oriental");
	Territorio* Indonesia= new Territorio("Indonesia");
	Territorio* NuevaGuinea= new Territorio("Nueva Guinea");
	Territorio* AustraliaOccidental= new Territorio("Australia Occidental");

	//EU
	Territorio* GranBretana= new Territorio("Gran Bretana");
	Territorio* Islandia= new Territorio("Islandia");
	Territorio* EuropaDelNorte= new Territorio("Europa del Norte");
	Territorio* Escandinavia= new Territorio("Escandinavia");
	Territorio* EuropaDelSur= new Territorio("Europa del Sur");
	Territorio* Ucrania= new Territorio("Ucrania");
	Territorio* EuropaOccidental= new Territorio("Europa Occidental");

	//ASIA
	Territorio* Afghanistan= new Territorio("Afghanistan");
	Territorio* China= new Territorio("China");
	Territorio* India= new Territorio("India");
	Territorio* Irkutsk= new Territorio("Irkutsk");
	Territorio* Japon= new Territorio("Japon");
	Territorio* Kamchatka= new Territorio("Kamchatka");
	Territorio* MedioOriente= new Territorio("Medio Oriente");
	Territorio* Mongolia= new Territorio("Mongolia");
	Territorio* Siam= new Territorio("Siam");
	Territorio* Siberia= new Territorio("Siberia");
	Territorio* Ural= new Territorio("Ural");
	Territorio* Yakutsk= new Territorio("Yakutsk");

	//SA
	Territorio* Argentina= new Territorio("Argentina");
	Territorio* Brasil= new Territorio("Brasil");
	Territorio* Peru= new Territorio("Peru");
	Territorio* Venezuela= new Territorio("Venezuela");


//ADYACENTES
//----------------------------------NORTH AMERICA--------------------------------------------

	Alaska->AgregarTerritorio(TerritorioNoroccidental);
	Alaska->AgregarTerritorio(Kamchatka);
	Alberta->AgregarTerritorio(TerritorioNoroccidental);
	Alberta->AgregarTerritorio(Ontario);
	Alberta->AgregarTerritorio(EstadosUnidosOccidentales);
	AmericaCentral->AgregarTerritorio(EstadosUnidosOccidentales);
	AmericaCentral->AgregarTerritorio(EstadosUnidosOrientales);
	AmericaCentral->AgregarTerritorio(Venezuela);
	EstadosUnidosOrientales->AgregarTerritorio(AmericaCentral);
	EstadosUnidosOrientales->AgregarTerritorio(EstadosUnidosOccidentales);
	EstadosUnidosOrientales->AgregarTerritorio(Ontario);
	EstadosUnidosOrientales->AgregarTerritorio(Quebec);
	Groenlandia->AgregarTerritorio(TerritorioNoroccidental);
	Groenlandia->AgregarTerritorio(Ontario);
	Groenlandia->AgregarTerritorio(Quebec);
	Groenlandia->AgregarTerritorio(Islandia);
	TerritorioNoroccidental->AgregarTerritorio(Ontario);
	TerritorioNoroccidental->AgregarTerritorio(Groenlandia);
	TerritorioNoroccidental->AgregarTerritorio(Alaska);
	TerritorioNoroccidental->AgregarTerritorio(Alberta);
	Ontario->AgregarTerritorio(TerritorioNoroccidental);
	Ontario->AgregarTerritorio(EstadosUnidosOccidentales);
	Ontario->AgregarTerritorio(Alberta);
	Ontario->AgregarTerritorio(EstadosUnidosOrientales);
	Ontario->AgregarTerritorio(Quebec);
	Ontario->AgregarTerritorio(Groenlandia);
	Quebec->AgregarTerritorio(Ontario);
	Quebec->AgregarTerritorio(EstadosUnidosOrientales);
	Quebec->AgregarTerritorio(Groenlandia);
	EstadosUnidosOccidentales->AgregarTerritorio(Ontario);
	EstadosUnidosOccidentales->AgregarTerritorio(AmericaCentral);
	EstadosUnidosOccidentales->AgregarTerritorio(EstadosUnidosOrientales);
	EstadosUnidosOccidentales->AgregarTerritorio(Alberta);
//--------------------------------SOUTH AMERICA----------------------------------------
	Argentina->AgregarTerritorio(Peru);
	Argentina->AgregarTerritorio(Brasil);
	Brasil->AgregarTerritorio(Peru);
	Brasil->AgregarTerritorio(Argentina);
	Brasil->AgregarTerritorio(Venezuela);
	Brasil->AgregarTerritorio(AfricaDelNorte);
	Peru->AgregarTerritorio(Argentina);
	Peru->AgregarTerritorio(Brasil);
	Peru->AgregarTerritorio(Venezuela);
	Venezuela->AgregarTerritorio(Peru);
	Venezuela->AgregarTerritorio(Brasil);
	Venezuela->AgregarTerritorio(AmericaCentral);
//------------------------------AUSTRALIA------------------------------------------
	AustraliaOriental->AgregarTerritorio(AustraliaOccidental);
	AustraliaOriental->AgregarTerritorio(NuevaGuinea);
	Indonesia->AgregarTerritorio(AustraliaOccidental);
	Indonesia->AgregarTerritorio(NuevaGuinea);
	Indonesia->AgregarTerritorio(Siam);
	NuevaGuinea->AgregarTerritorio(Indonesia);
	NuevaGuinea->AgregarTerritorio(AustraliaOccidental);
	NuevaGuinea->AgregarTerritorio(AustraliaOriental);
	AustraliaOccidental->AgregarTerritorio(AustraliaOriental);
	AustraliaOccidental->AgregarTerritorio(Indonesia);
	AustraliaOccidental->AgregarTerritorio(NuevaGuinea);
//------------------------------AFRICA---------------------------------------------
	Congo->AgregarTerritorio(AfricaOriental);
	Congo->AgregarTerritorio(AfricaDelNorte);
	Congo->AgregarTerritorio(AfricaDelSur);
	AfricaOriental->AgregarTerritorio(Congo);
	AfricaOriental->AgregarTerritorio(AfricaDelSur);
	AfricaOriental->AgregarTerritorio(Egipto);
	AfricaOriental->AgregarTerritorio(AfricaDelNorte);
	AfricaOriental->AgregarTerritorio(Madagascar);
	Egipto->AgregarTerritorio(AfricaDelNorte);
	Egipto->AgregarTerritorio(AfricaOriental);
	Egipto->AgregarTerritorio(MedioOriente);
	Egipto->AgregarTerritorio(EuropaDelSur);
	Madagascar->AgregarTerritorio(AfricaOriental);
	Madagascar->AgregarTerritorio(AfricaDelSur);
	AfricaDelNorte->AgregarTerritorio(Egipto);
	AfricaDelNorte->AgregarTerritorio(Congo);
	AfricaDelNorte->AgregarTerritorio(AfricaOriental);
	AfricaDelNorte->AgregarTerritorio(EuropaDelSur);
	AfricaDelNorte->AgregarTerritorio(EuropaOccidental);
	AfricaDelNorte->AgregarTerritorio(Brasil);
	AfricaDelSur->AgregarTerritorio(Congo);
	AfricaDelSur->AgregarTerritorio(AfricaOriental);
	AfricaDelSur->AgregarTerritorio(Madagascar);
//--------------------------------------EUROPA-----------------------------
	GranBretana->AgregarTerritorio(Islandia);
	GranBretana->AgregarTerritorio(Escandinavia);
	GranBretana->AgregarTerritorio(EuropaOccidental);
	GranBretana->AgregarTerritorio(EuropaDelNorte);
	Islandia->AgregarTerritorio(GranBretana);
	Islandia->AgregarTerritorio(Escandinavia);
	Islandia->AgregarTerritorio(Groenlandia);
	EuropaDelNorte->AgregarTerritorio(GranBretana);
	EuropaDelNorte->AgregarTerritorio(Escandinavia);
	EuropaDelNorte->AgregarTerritorio(EuropaDelSur);
	EuropaDelNorte->AgregarTerritorio(Ucrania);
	EuropaDelNorte->AgregarTerritorio(EuropaOccidental);
	Escandinavia->AgregarTerritorio(Islandia);
	Escandinavia->AgregarTerritorio(GranBretana);
	Escandinavia->AgregarTerritorio(EuropaDelNorte);
	Escandinavia->AgregarTerritorio(Ucrania);
	EuropaDelSur->AgregarTerritorio(EuropaOccidental);
	EuropaDelSur->AgregarTerritorio(EuropaDelNorte);
	EuropaDelSur->AgregarTerritorio(Ucrania);
	EuropaDelSur->AgregarTerritorio(MedioOriente);
	EuropaDelSur->AgregarTerritorio(Egipto);
	EuropaDelSur->AgregarTerritorio(AfricaDelNorte);
	Ucrania->AgregarTerritorio(EuropaDelNorte);
	Ucrania->AgregarTerritorio(Escandinavia);
	Ucrania->AgregarTerritorio(EuropaDelSur);
	Ucrania->AgregarTerritorio(Ural);
	Ucrania->AgregarTerritorio(Afghanistan);
	Ucrania->AgregarTerritorio(MedioOriente);
	EuropaOccidental->AgregarTerritorio(GranBretana);
	EuropaOccidental->AgregarTerritorio(EuropaDelNorte);
	EuropaOccidental->AgregarTerritorio(EuropaDelSur);
	EuropaOccidental->AgregarTerritorio(AfricaDelNorte);
//-------------------------------ASIA------------------------------------------
	Afghanistan->AgregarTerritorio(Ural);
	Afghanistan->AgregarTerritorio(MedioOriente);
	Afghanistan->AgregarTerritorio(India);
	Afghanistan->AgregarTerritorio(China);
	Afghanistan->AgregarTerritorio(Ucrania);
	China->AgregarTerritorio(Siam);
	China->AgregarTerritorio(India);
	China->AgregarTerritorio(Afghanistan);
	China->AgregarTerritorio(Siberia);
	China->AgregarTerritorio(Ural);
	China->AgregarTerritorio(Mongolia);
	India->AgregarTerritorio(Siam);
	India->AgregarTerritorio(China);
	India->AgregarTerritorio(Afghanistan);
	India->AgregarTerritorio(MedioOriente);
	Irkutsk->AgregarTerritorio(Kamchatka);
	Irkutsk->AgregarTerritorio(Yakutsk);
	Irkutsk->AgregarTerritorio(Siberia);
	Irkutsk->AgregarTerritorio(Mongolia);
	Japon->AgregarTerritorio(Mongolia);
	Japon->AgregarTerritorio(China);
	Kamchatka->AgregarTerritorio(Yakutsk);
	Kamchatka->AgregarTerritorio(Irkutsk);
	Kamchatka->AgregarTerritorio(Mongolia);
	Kamchatka->AgregarTerritorio(Japon);
	Kamchatka->AgregarTerritorio(Alaska);
	MedioOriente->AgregarTerritorio(India);
	MedioOriente->AgregarTerritorio(Afghanistan);
	MedioOriente->AgregarTerritorio(Ucrania);
	MedioOriente->AgregarTerritorio(EuropaDelSur);
	MedioOriente->AgregarTerritorio(Egipto);
	Mongolia->AgregarTerritorio(Japon);
	Mongolia->AgregarTerritorio(Kamchatka);
	Mongolia->AgregarTerritorio(Irkutsk);
	Mongolia->AgregarTerritorio(Siberia);
	Mongolia->AgregarTerritorio(China);
	Siam->AgregarTerritorio(China);
	Siam->AgregarTerritorio(India);
	Siam->AgregarTerritorio(Indonesia);
	Siberia->AgregarTerritorio(Ural);
	Siberia->AgregarTerritorio(China);
	Siberia->AgregarTerritorio(Irkutsk);
	Siberia->AgregarTerritorio(Mongolia);
	Siberia->AgregarTerritorio(Yakutsk);
	Ural->AgregarTerritorio(Afghanistan);
	Ural->AgregarTerritorio(Siberia);
	Ural->AgregarTerritorio(China);
	Ural->AgregarTerritorio(Ucrania);
	Yakutsk->AgregarTerritorio(Siberia);
	Yakutsk->AgregarTerritorio(Irkutsk);
	Yakutsk->AgregarTerritorio(Kamchatka);
//-------------------------------------------------------------------------------

//AGREGANDO A CONTINENTES
	AmericaN->AgregarTerritorio(Alaska);
	AmericaN->AgregarTerritorio(Alberta);
	AmericaN->AgregarTerritorio(AmericaCentral);
	AmericaN->AgregarTerritorio(EstadosUnidosOrientales);
	AmericaN->AgregarTerritorio(Groenlandia);
	AmericaN->AgregarTerritorio(TerritorioNoroccidental);
	AmericaN->AgregarTerritorio(Ontario);
	AmericaN->AgregarTerritorio(Quebec);
	AmericaN->AgregarTerritorio(EstadosUnidosOccidentales);

	AmericaS->AgregarTerritorio(Argentina);
	AmericaS->AgregarTerritorio(Brasil);
	AmericaS->AgregarTerritorio(Peru);
	AmericaS->AgregarTerritorio(Venezuela);

	Australia->AgregarTerritorio(AustraliaOriental);
	Australia->AgregarTerritorio(Indonesia);
	Australia->AgregarTerritorio(NuevaGuinea);
	Australia->AgregarTerritorio(AustraliaOccidental);

	Africa->AgregarTerritorio(Congo);
	Africa->AgregarTerritorio(AfricaOriental);
	Africa->AgregarTerritorio(Egipto);
	Africa->AgregarTerritorio(Madagascar);
	Africa->AgregarTerritorio(AfricaDelNorte);
	Africa->AgregarTerritorio(AfricaDelSur);

	Europe->AgregarTerritorio(GranBretana);
	Europe->AgregarTerritorio(Islandia);
	Europe->AgregarTerritorio(EuropaDelNorte);
	Europe->AgregarTerritorio(Escandinavia);
	Europe->AgregarTerritorio(EuropaDelSur);
	Europe->AgregarTerritorio(Ucrania);
	Europe->AgregarTerritorio(EuropaOccidental);

	Asia->AgregarTerritorio(Afghanistan);
	Asia->AgregarTerritorio(China);
	Asia->AgregarTerritorio(India);
	Asia->AgregarTerritorio(Irkutsk);
	Asia->AgregarTerritorio(Japon);
	Asia->AgregarTerritorio(Kamchatka);
	Asia->AgregarTerritorio(MedioOriente);
	Asia->AgregarTerritorio(Mongolia);
	Asia->AgregarTerritorio(Siam);
	Asia->AgregarTerritorio(Siberia);
	Asia->AgregarTerritorio(Ural);
	Asia->AgregarTerritorio(Yakutsk);

	//AGREGANDO A TABLERO
	this->continentes.push_back(Africa);
	this->continentes.push_back(AmericaN);
	this->continentes.push_back(Australia);
	this->continentes.push_back(Europe);
	this->continentes.push_back(Asia);
	this->continentes.push_back(AmericaS);
}

Tablero::~Tablero(){
	for(unsigned int i=0;i<continentes.size();i++)
		delete continentes[i];
	continentes.clear();
}

std::vector<Continente*> Tablero::getContinentes() {
	return continentes;
}

void Tablero::print() {
	std::vector<Continente*>::iterator it;

	for(it=continentes.begin(); it!=continentes.end(); it++)
		(*it)->print();

}

void Tablero::printDisponibles() {
	std::vector<Continente*>::iterator it;
	for(it=continentes.begin(); it!=continentes.end(); it++) {
		std::cout<<(*it)->getNombre()<<":"<<std::endl;
		std::vector<Territorio*> te=(*it)->getTerritorios();
		std::vector<Territorio*>::iterator it2;
		for(it2=te.begin(); it2!=te.end(); it2++)
			if(!(*it2)->isOcupado())
				std::cout<<'\t'<<(*it2)->getID()<<".  "<<(*it2)->getNombre()<<":"<<std::endl;
	}
}


void Tablero::setTarjetas(std::stack<Tarjeta> n) {
	tarjetas=n;
}

std::stack<Tarjeta>* Tablero::getTarjetas() {
	return &tarjetas;
}

Territorio* Tablero::searchTerritorio(unsigned int id){
	for(unsigned int i=0;i<continentes.size();i++){
		std::vector<Territorio*> vt=continentes[i]->getTerritorios();
		for(unsigned int j=0;j<vt.size();j++){
			if(id==vt[j]->getID())
				return vt[j];
		}
	}
	return NULL;
}

Territorio* Tablero::searchTerritorioDisponible(unsigned int id){
	for(unsigned int i=0;i<continentes.size();i++){
		std::vector<Territorio*> vt=continentes[i]->getTerritorios();
		for(unsigned int j=0;j<vt.size();j++){
			if(id==vt[j]->getID()&&!vt[j]->isOcupado())
				return vt[j];
		}
	}
	return NULL;
}

Territorio* Tablero::pickAdyacente(bool enemigo,Jugador* j0,Territorio* terr) {

	std::vector<Territorio*> ady=terr->getTerritoriosA();
	std::string input;
	std::vector<Territorio*>::iterator it;
	Territorio* ret=NULL;
	bool found=false;
	unsigned int inputID=0;


	if(!ady.empty()) {
		std::cout<<"\nTerritorios "<<(enemigo?"enemigos":"propios")<<" adyacentes a "<<terr->getNombre()<<" -- "<<"Ejercito"<<std::endl;

			for(unsigned int i=0; i<ady.size(); i++) {
				if(enemigo) {
					if(j0!=ady[i]->getJugador()) {
						std::cout<<'\t'<<ady[i]->getID()<<". "<<ady[i]->getNombre()<<" -- "<<ady[i]->getEjercito()<<std::endl;
						found=true;
					}
				}
				else {
					if(j0==ady[i]->getJugador()) {
						std::cout<<'\t'<<ady[i]->getID()<<". "<<ady[i]->getNombre()<<" -- "<<ady[i]->getEjercito()<<std::endl;
						found=true;
					}
				}
			}
	if(found){
			std::cout<<"\nDigite el ID del territorio a "<<(enemigo?"atacar: ":"fortificar.\nPara cancelar digite \"cancelar\":  ");
			getline(std::cin,input);
			if(input=="cancelar")
				ret=new Territorio();
			else
				inputID=atoi(input.c_str());
	}
	else {
		std::cout<<"No existe ningun territorio valido para "<<(enemigo?"atacar ":"fortificar ")<<"desde este territorio."<<std::endl;
		ret=new Territorio();
	}

		for(it=ady.begin(); it!=ady.end(); it++) {
			if((*it)->getID()==inputID)
				ret=*it;
		}
	}
	else {
		std::cout<<"No existe ningun territorio valido para "<<(enemigo?"atacar ":"fortificar ")<<"desde este territorio."<<std::endl;
		ret=new Territorio();
	}

	return ret;
}

std::vector<Tarjeta> allTarjetas(Tablero* t0){
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
	return ret;
}

void Tablero::fillTarjetas() {
	
	std::vector<Tarjeta> ret=allTarjetas(this);
	
	//mezclando
	random_shuffle(ret.begin(),ret.end());

	//agregando a stack
	std::stack<Tarjeta> auxT;

	for(std::vector<Tarjeta>::iterator it0=ret.begin(); it0!=ret.end(); it0++)
		auxT.push(*it0);

	tarjetas=auxT;
}

//EOF