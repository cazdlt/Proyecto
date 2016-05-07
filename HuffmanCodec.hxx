#include "HuffmanCodec.h"

HuffmanCodec::HuffmanCodec(){
	//pass
}

HuffmanCodec::HuffmanCodec(std::map<char,int> m){
	caracteres=m;
}

bool HuffmanCodec::comprimir(std::string in){
    std::ofstream salida(in+".bin", std::ios_base::binary|std::ios::ate);
	if (!salida){
		std::cout<<"Could not save loaded sequences into "<<in+".bin";
		return false;
	}
	salida<<"1"<<std::endl;
    std::string cadenaCompleta;
	cadenaCompleta = this->llenarMapaCaracteres(in);
	this->raiz = crearArbol(caracteres);
	this->codificar(raiz,"");
	unsigned long numeroSimbolos = (unsigned long)this->caracteres.size();
	salida.write(reinterpret_cast<char*>(& numeroSimbolos),sizeof(numeroSimbolos));

	std::string mensajeBinario="";
	std::map<char,std::string>::iterator ot;
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

bool HuffmanCodec::decode(std::string in){
	//test
	std::ifstream test(in,std::ios_base::binary);
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
	/*std::string huff;
	std::bitset<8> bits;
	unsigned long aa;
	istringstream iss(buff);
	std::cout<<iss.gcount()<<std::endl;
	while(iss.good()){
		iss>>aa;
		std::cout<<aa<<" ";
	}
	 * */
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
	std::map<char,int>m=caracteres;
	/*
	for(const auto&p:m){
		std::cout << "m[" << p.first << "] = " << p.second << '\n';
	}
	 * */

    return archivoCompleto;
}

NodoHuffman* HuffmanCodec::crearArbol(std::map<char, int> caracteres){
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