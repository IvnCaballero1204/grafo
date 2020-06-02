//
// Created by ivan on 5/4/20.
//

#include "grafo.h"

///IMPLEMENTACIÓN VERTICE

Vertice::Vertice(std::string &dato) {
    this->dato = dato;
    sigVertice = nullptr;
    primerArista = nullptr;
    contAristas = 0;
}

void Vertice::insertaArista(Vertice* v_2) {
    Arista* newArista = new Arista(v_2);

    if(this->contAristas == 0){
        this->primerArista = newArista;
        contAristas++;
    } else{
        ultimaArista()->setSig(newArista);
        contAristas++;
    }
}

void Vertice::eliminaArista(Arista* elemento) {

    ///SI ES LA PRIMERA ARISTA
    if(elemento == primerArista){
        ///SI TIENE MÁS DE UNA ARISTA HACEMOS EL CAMBIO DE LA PRIMERA ARISTA HACIA LA SIGUIENTE ARISTA
        if(contAristas != 1)
            primerArista = primerArista->getSig();
        else
            primerArista = nullptr;
    }

    ///SI NO ES LA PRIMERA ARISTA
    else{
        Arista* aristaAnterior = anterior(elemento);

        ///SI NO EXISTE LA ARISTA
        if(!aristaAnterior){
            std::cout << "NO EXISTE ARISTA" << std::endl;
            return;
        }
        else
            aristaAnterior->setSig(elemento->getSig());
    }

    /// 1. YA UNA VEZ HECHO LOS CAMBIOS SE ELIMINA LA ARISTA.
    /// 2. EN DADO CASO QUÉ SOLO TUVIERA UNA ARISTA, NO SE HACE NINGÚN CAMBIO Y SOLO SE ELIMINA.
    delete elemento;
    contAristas--;
}

void Vertice::setSig(Vertice* vertice) {
    sigVertice = vertice;
}

Arista* Vertice::ultimaArista() {
    Arista* aux(primerArista);

    while(aux->getSig())
        aux = aux->getSig();

    return aux;
}

Arista* Vertice::buscaArista(Vertice* v) {
    Arista* aux(primerArista);

    while(aux){
        if(aux->getDato() == v)
            break;
        aux = aux->getSig();
    }
    return aux;
}

Arista* Vertice::anterior(Arista* e) {
    Arista* aux = primerArista;

    if(aux != e){
        while(aux){
            if(aux->getSig() == e)
                break;
            aux = aux->getSig();
        }
    }
    return aux;
}

Arista* Vertice::recupera(int indice){
    Arista* aux = primerArista;
    int i = 0;

    while(aux){
        if(i == indice)
            break;
        aux = aux->getSig();
        i++;
    }
    return aux;
}

Arista* Vertice::operator[](int indice) {
    Arista* aux = primerArista;
    int i = 0;

    while(aux){
        if(i == indice)
            break;
        aux = aux->getSig();
        i++;
    }
    return aux;
}

Vertice* Vertice::getSig() {
    return sigVertice;
}

int Vertice::getContador() {
    return contAristas;
}

std::string Vertice::getDato() {
    return dato;
}

std::string Vertice::toString() {
    std::stringstream ss;
    Arista* aAux(primerArista);

    ss << this->getDato();

    while(aAux){
        ss << "->" << aAux->toString();
        aAux = aAux->getSig();
    }

    return ss.str();
}

///IMPLEMENTACIÓN ARISTA

Arista::Arista(Vertice* v) {
    v2 = v;
    sigArista = nullptr;
}

void Arista::setSig(Arista* arista){
    sigArista = arista;
}

Arista* Arista::getSig() {
    return sigArista;
}

Vertice* Arista::getDato() {
    return v2;
}

std::string Arista::toString() {
    return v2->getDato();
}

///IMPLEMENTACIÓN GRAFO

Grafo::Grafo() {
    primerVertice = nullptr;
    contVertices = 0;
}

void Grafo::insertaVertice(std::string &dato) {
    Vertice* newVertice = new Vertice(dato);

    if (!primerVertice) {
        primerVertice = newVertice;
        std::cout << "VERTICE " << primerVertice->getDato()<< " CREADO CON EXITO" << std::endl;
        contVertices++;
    } else {
        ultimoVertice()->setSig(newVertice);
        std::cout << "VERTICE " << newVertice->getDato()<< " CREADO CON EXITO" << std::endl;
        contVertices++;
    }
}

void Grafo::insertaArista(Vertice* v1, Vertice* v2) {
    if(!v1 || !v2)
        std::cout << "ERROR AL INSERTAR LA ARISTA" << std::endl;
    else
        v1->insertaArista(v2);
}

void Grafo::eliminaVertice(Vertice *elemento) {

    Vertice* verticeAnterior = anterior(elemento);

    if(!verticeAnterior) {
        std::cout << "NO EXISTE VERTICE" << std::endl;
        return;
    }

    else {
        int numeroAristas = elemento->getContador(), i = 0;

        ///ELIMINA TODAS LAS ARISTAS DE ESTE VERTICE
        while(i < numeroAristas){
            int j = 0;
            Arista *aAux = elemento->recupera(j);
            elemento->eliminaArista(aAux);
            i++;
        }

        int numeroVertices = contVertices;
        i = 0;

        ///ELIMINA SU CONEXIÓN HACIA OTROS VERTICES EN DADO CASO DE QUE ÉSTE SEA UNA ARISTA DE ALGUNO
        while(i < numeroVertices){
            Vertice *vAux = recupera(i);

            if(vAux->buscaArista(elemento)){
                Arista *aAux = vAux->buscaArista(elemento);
                vAux->eliminaArista(aAux);
            }
            i++;
        }

        verticeAnterior->setSig(elemento->getSig());

        if(elemento == primerVertice){
            if(contVertices != 1)
                primerVertice = primerVertice->getSig();
            else
                primerVertice = nullptr;
        }
    }

    std::cout << "VERTICE " << elemento->getDato() << " ELIMINADO CON EXITO" << std::endl;
    delete elemento;
    contVertices--;
}

void Grafo::eliminaArista(std::string &arista){
    std::string v1Aux, v2Aux;
    v1Aux = arista[0];
    v2Aux = arista[2];

    Vertice* origen = buscaVertice(v1Aux);
    Vertice* destino = buscaVertice(v2Aux);

    if(origen->buscaArista(destino)){
        Arista* aux = origen->buscaArista(destino);
        origen->eliminaArista(aux);
        std::cout << "ARISTA " << v1Aux << "->" << v2Aux << " ELIMINADA CON EXITO" << std::endl;
    }

    else
        std::cout << "NO EXISTE ARISTA " << v1Aux << "->" << v2Aux << std::endl;
}

bool Grafo::existeArista(std::string &arista) {
    std::string v1Aux, v2Aux;
    v1Aux = arista[0];
    v2Aux = arista[2];

    Vertice* v1 = buscaVertice(v1Aux);
    Vertice* v2 = buscaVertice(v2Aux);

    return v1->buscaArista(v2) != nullptr;
}

Vertice* Grafo::buscaVertice(std::string& buscado) {
    Vertice* aux = primerVertice;

    while(aux) {
        if (aux->getDato() == buscado)
            break;
        aux = aux->getSig();
    }

    return aux;
}

Vertice* Grafo::recupera(int indice) {
    Vertice* aux = primerVertice;
    int i = 0;

    while(aux){
        if(i == indice)
            break;
        aux = aux->getSig();
        i++;
    }
    return aux;
}

Vertice* Grafo::ultimoVertice() {
    Vertice* aux(primerVertice);

    while(aux->getSig())
        aux = aux->getSig();

    return aux;
}

Vertice* Grafo::anterior(Vertice* e) {
    Vertice* aux = primerVertice;

    if(aux != e){
        while(aux){
            if(aux->getSig() == e)
                break;
            aux = aux->getSig();
        }
    }
    return aux;
}

Vertice* Grafo::operator[](int indice) {
    Vertice* aux = primerVertice;
    int i = 0;

    while(aux){
        if(i == indice)
            break;
        aux = aux->getSig();
        i++;
    }
    return aux;
}

std::string Grafo::toString() {
    std::stringstream ss;

    Vertice* aux = primerVertice;

    while(aux){
        ss << aux->toString() << std::endl;
        aux = aux->getSig();
    }

    return ss.str();
}