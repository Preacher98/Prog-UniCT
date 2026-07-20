#include "Class_graph.h"
#include <cstdlib> 
void Floyd_Warshall(int Vertici, Class_graph grafo){
    const long long inf = 1e15; //infinito per evitare gli overflow
    std::vector<std::vector<long long>> distanze(Vertici, std::vector<long long>(Vertici,inf)); //Creazione della matrice che contiene array di long long inizializzata ad infinito

    //caso base nodo uguale
    for (int i = 0; i < Vertici; i++)
    {
        distanze[i][i] = 0; //diagonale principale
    }
    
    //riempiamo la matrice con i pesi dati
    for (int p = 0; p < Vertici; p++)
    {
        for (auto& ark : grafo.adj[p]) //stiamo iterando gli archi
        {
            distanze[p][ark.verso] = ark.peso;
        }
    }

    //cicli annidati che compongono l'algoritmo
    for (int k = 0; k < Vertici; k++) //ciclo esterno per il nodo intermedio
    {
        for (int i = 0; i < Vertici; i++)
        {
            for (int j = 0; j < Vertici; j++)
            {
                if(distanze[i][k] != inf && distanze[k][j] != inf){
                    distanze[i][j] = std::min(distanze[i][j], distanze[i][k]+distanze[k][j]);  //formula ricorsiva di floyd warshall
                    //cerchiamo il minimo tra la distanza i,j non utilizzando il nodo k come intermendio e invece la somma delle distanze utilizzando k come intermedio.
                }
            }   
        }        
    }
    //fine cicli annidati

    //print matrix
    for (int i = 0; i < Vertici; i++)
    {
        std::cout<<i<< " \t";
        for (int j = 0; j < Vertici; j++)
        {
            std::cout<<distanze[i][j]<<" \t";
        }
        std::cout<<std::endl;
    }
    
    
}