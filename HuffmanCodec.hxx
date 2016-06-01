#include "HuffmanCodec.h"

HuffmanCodec::HuffmanCodec(){
	raiz=NULL;
}

HuffmanCodec::HuffmanCodec(std::map<char,int> m){
	raiz=NULL;
	caracteres=m;
}

HuffmanCodec::~HuffmanCodec(){
	if(raiz!=NULL)
		delete (raiz);
}

bool HuffmanCodec::comprimir(std::string in){

    std::ofstream salida(in+".bin", std::ios::binary|std::ios::ate);
	if (!salida){
		std::cout<<"Could not save loaded sequences into "<<in+".bin";
		return false;
	}

	salida<<"1"<<std::endl;
    std::string cadenaCompleta;
	cadenaCompleta = this->llenarMapaCaracteres(in);
	this->raiz = crearArbol();
	this->codificar(raiz,"");
	unsigned int numeroSimbolos = (unsigned int)this->caracteres.size();
	salida.write((char*)& numeroSimbolos,sizeof(numeroSimbolos));

	std::string mensajeBinario="";
	std::map<char,std::string>::iterator ot;
	unsigned long cnt=0;
	
	for (unsigned int i=0;i<cadenaCompleta.size();i++){
        ot = this->codificacion.find(cadenaCompleta[i]);
         if(ot != codificacion.end()){
                mensajeBinario += ot->second;
         }
	}

	cnt=mensajeBinario.size()/8 +1;
	salida<<cnt;
	//salida.write(reinterpret_cast<char*>(&cnt),sizeof(cnt));

	char caracter= ' ';
	int frecuencia = 0;

	std::map<char,int>::iterator it;

	for (it = caracteres.begin(); it != caracteres.end(); it++){
        caracter = it->first;
        frecuencia = it->second;
		salida<<caracter<<" "<<frecuencia<<std::endl;
	}

    std::stringstream sstream(mensajeBinario);
    std::string output;
    while(sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
		char n=bits.to_ulong();
		salida.write((char*)&n,sizeof(n));
    }

	salida.close();
	return true;
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

std::string HuffmanCodec::llenarMapaCaracteres(std::string nombreArchivo){

    std::string cadena;
    std::string archivoCompleto = "";
    std::ifstream archivo(nombreArchivo);

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

	return archivoCompleto;
}

void HuffmanCodec::decodificarCaracteres(std::ifstream& arch,unsigned int x){

	std::string in,aux;
	std::vector<std::string> datosMapa;

	for(unsigned int i=0;i<x;i++){

		getline(arch,in);
		if(in.empty()){ // si es endline o espacio
			arch>>aux;
			arch.ignore();
			in+=aux;
		}

		datosMapa=splitstring(in,' ');

		if(datosMapa.size()==1){ //si es endline o espacio
			if(in[0]==' ')
				caracteres[' ']=atoi(datosMapa[0].c_str());
			else
				caracteres['\n']=atoi(datosMapa[0].c_str());
		}
		else{ //si es otro caracter
			caracteres[datosMapa[0][0]]=atoi(datosMapa[1].c_str());
		}
	}
}

bool HuffmanCodec::decode(std::string in){

	//test
	std::ifstream arch(in,std::ios::binary);
	std::ofstream temparch("temp");
	unsigned long numChars,tamanoCadena;
	char buff;
	std::string cadenaCompleta="",archivoCompleto="";
	NodoHuffman* nodo;
	if(!arch.is_open())
		return false;
	
	getline(arch,in); //obviando la linea para identificar tipo de archivo

	arch.read((char*)&numChars,sizeof(unsigned int)); //no se por que a veces toca con .read o con >> 
	arch>>tamanoCadena;

	decodificarCaracteres(arch,numChars);	//llena mapa de caracteres

	for(unsigned int i=0;i<tamanoCadena;i++){
		arch.read((char*)&buff,sizeof(char)); //lee un char que tiene el valor en bits como unsigned long
		std::bitset<8> TEST(buff);  //vuelve el ulong a bits
		cadenaCompleta+=TEST.to_string();
	}
	this->raiz = crearArbol();
	nodo = this->raiz;
    
	for(unsigned int i=0;i<cadenaCompleta.size();i++){		
        if(nodo->isLeaf()){
            archivoCompleto += nodo->getLetra();
            nodo=this->raiz;
        }
        if(cadenaCompleta[i]=='0')
			nodo = nodo->getIzq();		
		else
			nodo = nodo->getDer();
	}    

	if(temparch.is_open())
		temparch<<archivoCompleto;
	else return false;
	
	temparch.close();
	arch.close();
	return true;
}


bool compare(NodoHuffman *x,  NodoHuffman *y ){
	if ( x->getFrecuencia() < y->getFrecuencia() )
		return true;
	else if ( x->getFrecuencia() > y->getFrecuencia() )
		return false;
	return 0;
}

NodoHuffman* HuffmanCodec::crearArbol(){
	NodoHuffman *nodo, *nodo1, *nodo2;
	std::list<NodoHuffman *> lista;
	typename std::map<char, int>::iterator it;
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

void HuffmanCodec::codificar(NodoHuffman *nodo, std::string codigo){
    if (nodo->getLetra() != '?')
		codificacion[nodo->getLetra()] = codigo;
	if (nodo->getIzq() != NULL)
		codificar(nodo->getIzq(), codigo + '0');
	if (nodo->getDer() != NULL)
		codificar(nodo->getDer(), codigo + '1');
}
