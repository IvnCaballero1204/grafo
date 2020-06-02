#include <fstream>
#include "grafo.h"

int main() {
    std::ifstream file("entrada.txt");
    Grafo grafo;
    std::string aux;
    int contador = 0, opc;

    std::cout << "CONSTRUYENDO GRAFO INICIAL" << std::endl;

    if (file.is_open()) {
        std::string v1Aux, v2Aux;

        ///MI GRAFO TODO EL TIEMPO ES DIRIGIDO
        file >> aux;

        file >> aux;
        contador = stoi(aux);

        try{
            while(contador != 0){
                file >> aux;

                v1Aux = aux[0];
                v2Aux = aux[2];

                if(!grafo.buscaVertice(v1Aux)) {
                    std::cout << "Insertando vertice " << v1Aux << " al grafo" << std::endl;
                    grafo.insertaVertice(v1Aux);
                }

                if(!grafo.buscaVertice(v2Aux)) {
                    std::cout << "Insertando vertice " << v2Aux << " al grafo" << std::endl;
                    grafo.insertaVertice(v2Aux);
                }

                Vertice *v1 = grafo.buscaVertice(v1Aux);
                Vertice *v2 = grafo.buscaVertice(v2Aux);

                std::cout << "Creando arista " << v1Aux << "->" << v2Aux << std::endl;
                grafo.insertaArista(v1, v2);

                contador--;
            }
        }catch(std::invalid_argument){ }

        std::cout << std::endl;
        file >> aux;

        contador = stoi(aux);

        while(contador != 0){
            std::string auxOpc = "";
            int i;
            file >> aux;

            for(i = 0; i < aux.length(); i++) {
                if (auxOpc == "MOSTRAR") {
                    opc = 1;
                    break;
                } else {
                    if (auxOpc == "EXISTE") {
                        opc = 2;
                        break;
                    } else {
                        if(auxOpc == "ELIMINA"){
                            opc = 3;
                            break;
                        }
                    }
                }
                auxOpc += aux[i];
            }

            switch(opc) {
                case 1:
                    if(aux.length() - i != 5){
                        auxOpc = "";
                        auxOpc = aux[i+1];

                        std::cout << "Mostrando Vertice: " << grafo.buscaVertice(auxOpc)->toString() << std::endl;
                    } else{
                        std::cout << "GRAFO ACTUAL" << std::endl;
                        std::cout << grafo.toString();
                    }
                    break;

                case 2:
                    auxOpc = "";

                    for(i = i+1; i < aux.length(); i++)
                        auxOpc += aux[i];

                    if(auxOpc.length() == 3){
                        if(grafo.existeArista(auxOpc))
                            std::cout << "EXISTE ARISTA " << auxOpc << std::endl;
                        else
                            std::cout << "NO EXISTE ARISTA " << auxOpc << std::endl;
                    } else
                        if(grafo.buscaVertice(auxOpc))
                            std::cout << "EXISTE VERTICE " << auxOpc << std::endl;
                        else
                            std::cout << "NO EXISTE VERTICE " << auxOpc << std::endl;

                    break;

                case 3:
                    auxOpc = "";

                    for(i = i+1; i < aux.length(); i++)
                        auxOpc += aux[i];

                    if(auxOpc.length() == 3){
                        if(grafo.existeArista(auxOpc))
                            grafo.eliminaArista(auxOpc);
                        else
                            std::cout << "NO EXISTE ARISTA " << auxOpc << " PARA ELIMINAR" << std::endl;
                    } else {
                        if (grafo.buscaVertice(auxOpc)) {
                            Vertice *vAux = grafo.buscaVertice(auxOpc);
                            grafo.eliminaVertice(vAux);
                        } else
                            std::cout << "NO EXISTE VERTICE " << auxOpc << "PARA ELIMINAR" << std::endl;
                    }

                    break;
            }
            contador--;
        }

    }
    else
        std::cout << "HUBO UN ERROR AL CONSTRUIR EL GRAFO" << std::endl;

    file.close();
}