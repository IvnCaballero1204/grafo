//
// Created by ivan on 5/4/20.
//

#ifndef ACTIVIDAD_4_GRAFO_H
#define ACTIVIDAD_4_GRAFO_H

#include <iostream>
#include <sstream>
#include <string>

class Vertice;

class Arista {
private:
    Vertice* v2;
    Arista* sigArista;
public:
    Arista(Vertice* v2);
    void setSig(Arista* arista);
    Arista* getSig();
    Vertice* getDato();
    std::string toString();
};

class Vertice {
private:
    std::string dato;
    Arista* primerArista;
    Vertice* sigVertice;
    int contAristas;
public:
    Vertice(std::string& dato);

    void insertaArista(Vertice* v_2);
    void eliminaArista(Arista* elemento);
    void setSig(Vertice* vertice);

    Arista* ultimaArista();
    Arista* buscaArista(Vertice* v);
    Arista* anterior(Arista *e);
    Arista* recupera(int indice);
    Arista* operator[](int indice);

    Vertice* getSig();

    int getContador();

    std::string getDato();
    std::string toString();
};

class Grafo {
private:
    Vertice* primerVertice;
    int contVertices;
public:
    Grafo();

    void insertaVertice(std::string& dato);
    void insertaArista(Vertice* v1, Vertice* v2);
    void eliminaVertice(Vertice* elemento);
    void eliminaArista(std::string &arista);

    bool existeArista(std::string& arista);

    Vertice* buscaVertice(std::string& buscado);
    Vertice* recupera(int indice);
    Vertice* ultimoVertice();
    Vertice* anterior(Vertice* e);
    Vertice* operator[](int indice);

    std::string toString();
};

#endif //ACTIVIDAD_4_GRAFO_H