#include "Class_graph.h"
#include "Floyd_Warshall.h"
#include "Bellman_Ford.h"
#include <cstdlib>

// void Floyd_Warshall(int Vertici, Class_graph grafo);

int main()
{
    int vertici = 5;
    Class_graph grafo(vertici);

    // nodo 0
    grafo.add_arco(0, 1, rand() % 10);
    grafo.add_arco(0, 2, rand() % 10);

    // nodo 1
    grafo.add_arco(1, 2, rand() % 10);
    grafo.add_arco(1, 4, rand() % 10);
    grafo.add_arco(1, 3, rand() % 10);

    // nodo 2
    grafo.add_arco(2, 4, rand() % 10);
    grafo.add_arco(2, 3, rand() % 10);

    // nodo 3
    grafo.add_arco(3, 0, rand() % 10);

    // nodo 4
    grafo.add_arco(4, 2, rand() % 10);
    grafo.add_arco(4, 1, rand() % 10);
    grafo.add_arco(4, 3, rand() % 10);

    // display
    grafo.display();

    // Floyd Warshall
    Floyd_Warshall(vertici, grafo);
    Bellman_ford(vertici, grafo, 1);
    return 0;
}
