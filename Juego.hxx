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
	std::vector<std::string> cor = {"Azul","Verde","Amarillo","Rojo","Blanco","Negro"};

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
	std::vector<Continente*> continentes;
	std::vector<Jugador>::iterator itj;
	Territorio* t0=NULL;

	std::cout<<"Digite la cantidad de jugadores: ";
	std::cin>>cantidadJugadores;
	std::cin.ignore();

	if(!llenarJugadores(cantidadJugadores))
		return false;

	tablero=new Tablero();
	tablero->fillTarjetas();
	continentes=tablero->getContinentes();
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

	if(in.size()>1) {
		comprimir(in[0]);
		remove(in[0].c_str());
	}

	return true;
}

bool guardarPartida(std::ofstream& file,std::vector<Jugador> jugadores){
	size_t sz=jugadores.size();
	std::vector<Tarjeta> tjs;
	std::vector<Territorio*> tts;
	file<<"0"<<std::endl;
	file<<sz<<std::endl;
	for(unsigned int i=0;i<sz;i++){

		//info
		file<<jugadores[i].getNombre()<<std::endl;
		file<<jugadores[i].getColor()<<std::endl;

		//territorios
		tts=jugadores[i].getTerritorios();
		file<<tts.size()<<std::endl;
		for(unsigned int j=0;j<tts.size();j++)
			file<<tts[j]->getID()<<" "<<tts[j]->getEjercito()<<std::endl;

		//tarjetas
		tjs=jugadores[i].getTarjetas();
		file<<tjs.size()<<std::endl;
		for(unsigned int j=0;j<tjs.size();j++)
			file<<tjs[j].getID()<<std::endl;

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
		Tarjeta::updateVCambio();
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
		if(line=="1"){
			arch.close();
			decode(input);
			arch.open("temp");
			textinit(arch);
			arch.close();
			remove("temp");
		}
		else{
			textinit(arch);
		}
		arch.close();
		return true;
	}
	else{
		std::cout<<"Error de archivo.";
		return false;
	}
}

void Juego::textinit(std::ifstream& arch){

	unsigned int sz;
	unsigned int tts=0,tjs=0;
	std::string line,f;
	std::vector<std::string> in,sp;
	Territorio* t0=NULL;
	std::vector<Tarjeta> vt,tarjetas=allTarjetas(tablero),jt;
	bool c;

	getline(arch,line);
	sz=atoi(line.c_str());
	jugadores.resize(sz);
	for(unsigned int i=0;i<sz;i++)	{

			//datos
			Jugador auxj;
			jugadores[i].setID(i+1);
			getline(arch,line);
			jugadores[i].setNombre(line);
			getline(arch,line);
			jugadores[i].setColor(line);

			//territorios
			getline(arch,line);
			tts=atoi(line.c_str());
			for(unsigned int j=0;j<tts;j++){
				getline(arch,line);
				in=splitstring(line,' ');
				t0=tablero->searchTerritorio(atoi(in[0].c_str()));
				t0->setEjercito(atoi(in[1].c_str()));
				jugadores[i].addTerritorio(t0);
			}

			//tarjetas
			getline(arch,line);
			tjs=atoi(line.c_str());
			jt.resize(tjs);
			for(unsigned int j=0;j<tjs;j++){
				getline(arch,line);
				in=splitstring(line,' ');
				if(in[1]=="A")
					f="Artilleria";
				else if(in[1]=="C")
					f="Caballeria";
				else
					f="Infanteria";
				c=(in[2]=="0"?false:true);

				Tarjeta auxt(in[0],f,c);
				jt[i]=auxt;
				vt.push_back(auxt);
			}
			jugadores[i].setTarjetas(jt);

		}
		tablero->setTarjetas(compararTarjetas(vt,tarjetas));
		estado=0;
}

bool Juego::comprimir(std::string in){
    ofstream salida(in+".bin", std::ios_base::binary|ios::ate);
	if (!salida){
		cout<<"Could not save loaded sequences into "<<in+".bin";
		return false;
	}
	salida<<"1"<<std::endl;
    string cadenaCompleta;
	cadenaCompleta = this->llenarMapaCaracteres(in);
	this->raiz = crearArbol(caracteres);
	this->codificar(raiz,"");
	unsigned long numeroSimbolos = (unsigned long)this->caracteres.size();
	salida.write(reinterpret_cast<char*>(& numeroSimbolos),sizeof(numeroSimbolos));

	string mensajeBinario="";
	std::map<char,string>::iterator ot;
	unsigned long cnt=0;

	for (unsigned int i=0;i<cadenaCompleta.size();i++){
        ot = this->codificacion.find(cadenaCompleta[i]);
         if(ot != codificacion.end()){
                mensajeBinario += ot->second;
         }
	}

	std::string data = mensajeBinario;
    std::stringstream sstream(data);
    std::string output;
    while(sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

	cnt=output.size();
	salida.write(reinterpret_cast<char*>(&cnt),sizeof(cnt));

	char caracter= ' ';
	int frecuencia = 0;

	std::map<char,int>::iterator it;

	for (it = caracteres.begin(); it != caracteres.end(); it++){
        caracter = it->first;
        frecuencia = it->second;
        salida.write((char *)&caracter,sizeof(caracter));
        salida.write((char *)& frecuencia,sizeof(frecuencia));
	}

	salida.write(output.c_str(),output.size());
	salida.close();
	return true;
}

/*
bool Juego::decode(std::string in){
		//test
	ifstream test("test1.in",ios::binary);
	if (!test){
		cout<<"Could not load file from "<<in;
		return false;
	}
	this->caracteres.clear();
	unsigned long x,n;
	char y;
	int f;
	test.read((char*)&x,sizeof(x));
	test.read((char*)&n,sizeof(n));
	for(unsigned int i=0;i<x;i++){
		test.read((char *)&y,sizeof(char));
        test.read((char *)& f,sizeof(int));
        caracteres.insert (std::pair<char,int>(y,f));
	}

	while(no haya mas por leer){
        string camino;
        test.read((char *)&camino, 8);
        std::map<char,string>::iterator it;
        for(it = codificacion.begin(); it != codificacion.end();it++){
            if(camino == it->second){
                //escribir it->first;
                break;
            }
        }
    }
	char* buff=new char[n];
	test.read(buff,n);
	std::cout<<buff;
	return true;
}*/

bool decode(std::string in){
	//test
	ifstream test(in,std::ios_base::binary);
	getline(test,in);
	unsigned long x,n;
	char y;
	int f;
	test.read((char*)&x,sizeof(x));
	std::cout<<"numchars: "<<x<<std::endl;
	test.read((char*)&n,sizeof(n));
	std::cout<<"tam: "<<n<<std::endl;
	for(unsigned int i=0;i<x;i++){
		test.read((char *)&y,sizeof(char));
        test.read((char *)& f,sizeof(int));
		std::cout<<y<<": "<<f<<std::endl;
	}
	unsigned long buff;
	test.read((char*)&buff,8);
	std::cout<<buff<<std::endl;
	std::string huff;
	std::bitset<8> bits;
	unsigned long aa;
	/*istringstream iss(buff);
	std::cout<<iss.gcount()<<std::endl;
	while(iss.good()){
		iss>>aa;
		std::cout<<aa<<" ";
	}*/
	test.close();
	return true;
}

bool compare(NodoHuffman *x,  NodoHuffman *y ){
	if ( x->getFrecuencia() < y->getFrecuencia() )
		return true;
	else if ( x->getFrecuencia() > y->getFrecuencia() )
		return false;
	return 0;
}
std::string Juego::llenarMapaCaracteres(std::string nombreArchivo){

    string cadena;
    string archivoCompleto = "";
    ifstream archivo(nombreArchivo);

    if(!archivo.fail()){
        while(getline(archivo,cadena)){
            archivoCompleto += cadena;
            archivoCompleto+='\n';
        }
        archivo.close();
    }

    std::map<char,int>::iterator it;
    for(unsigned int i =0;i<archivoCompleto.size();i++){
        it = this->caracteres.find(archivoCompleto[i]);
        if(it != this->caracteres.end()){
            this->caracteres[archivoCompleto[i]] = this->caracteres[archivoCompleto[i]]+1;
        }
        else{
            caracteres.insert (std::pair<char,int>(archivoCompleto[i],1));
        }
    }
	std::map<char,int>m=caracteres;
	/*
	for(const auto&p:m){
		std::cout << "m[" << p.first << "] = " << p.second << '\n';
	}
	 * */

    return archivoCompleto;
}

NodoHuffman * Juego::crearArbol(map<char, int> caracteres){
	NodoHuffman *nodo, *nodo1, *nodo2;
	list<NodoHuffman *> lista;
	typename map<char, int>::iterator it;
	for (it = caracteres.begin(); it != caracteres.end(); it++){
		nodo = new NodoHuffman();
		nodo->setLetra(it->first);
		nodo->setFrecuencia(it->second);
		lista.push_back(nodo);
	}
	while (lista.size()>1){
		lista.sort(compare);
		nodo1 = lista.front();
		lista.pop_front();
		nodo2 = lista.front();
		lista.pop_front();
		nodo = new NodoHuffman();
		nodo->setIzq(nodo1);
		nodo->setDer(nodo2);
		nodo->setFrecuencia(nodo1->getFrecuencia() + nodo2->getFrecuencia());
		lista.push_back(nodo);
	}
	return lista.front();
}
void Juego::codificar(NodoHuffman *nodo, string codigo){
    if (nodo->getLetra() != '?')
		codificacion[nodo->getLetra()] = codigo;
	if (nodo->getIzq() != NULL)
		codificar(nodo->getIzq(), codigo + '0');
	if (nodo->getDer() != NULL)
		codificar(nodo->getDer(), codigo + '1');
}

//EOF
