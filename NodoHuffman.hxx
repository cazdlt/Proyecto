NodoHuffman::NodoHuffman(){
	letra = '?';
	frecuencia = 0;
	izq = NULL;
	der = NULL;
}
NodoHuffman::~NodoHuffman(){
}
char NodoHuffman::getLetra(){
	return letra;
}
void NodoHuffman::setLetra(char letr){
	letra = letr;
}
int NodoHuffman::getFrecuencia(){
	return frecuencia;
}
void NodoHuffman::setFrecuencia(int frecuenci){
	frecuencia = frecuenci;
}
NodoHuffman * NodoHuffman::getIzq(){
	return izq;
}
void NodoHuffman::setIzq(NodoHuffman * iz){
	izq = iz;
}
NodoHuffman * NodoHuffman::getDer(){
	return der;
}
void NodoHuffman::setDer(NodoHuffman * de){
	der = de;
}
void NodoHuffman::preOrden(){
    std::cout<<this->letra<< " : " << this->frecuencia<<std::endl;
    if(this->izq != NULL)
        this->izq->preOrden();
    if(this->der != NULL)
        this->der->preOrden();
}
bool NodoHuffman::isLeaf(){
    if(this->getIzq() == NULL && this->getDer() == NULL ){
      return true;
    }
    return false;
}
