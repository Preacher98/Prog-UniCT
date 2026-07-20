#include "Class_graph.h"
using namespace std;
void Bellman_ford(int Vertici, Class_graph grafo, int sorgente)
{
    const long long inf = 1e15;
    std::vector<long long> distanze(Vertici, inf); // creiamo un vettore di lungezza "vertici" long long inizializzati ad infinito
    distanze[sorgente] = 0;

    // Parte iniziale di bellman ford dove applichiamo la relax
    for (int i = 1; i < Vertici - 1; i++)
    {
        bool flag = false; // Flag che ci permette di uscire prima dal ciclo se effettivamente non ci sono cambiamenti

        for (auto &arco : grafo.lista_archi)
        {
            // dato che abbiamo inserito le nostre informazioni in una tupla adesso le dobbiamo spacchettare
            int u = std::get<0>(arco); // nodo partenza
            int v = std::get<1>(arco); // nodo destinazione
            int w = std::get<2>(arco); // peso dell'arco

            // applichiamo la relax
            if (distanze[u] != inf && distanze[u] + w < distanze[v])
            {
                distanze[v] = distanze[u] + w; // se la condizione è soddisfatta allora possiamo aggiornare l'arco con un nuovo peso
                flag = true;
            }
        }
        cout << "Archi considerati: " << i << ": " << endl;
        for (int l = 0; l < Vertici; l++)
        {
            cout << "Nodo: " << l << " ";
            if (distanze[l] == inf)
            {
                cout << " inf " << endl;
            }
            else
                cout << distanze[i] << endl;
            ;
        }
        if (!flag)
            break;
    }

    // Una volta uscito dal ciclo per la ricerca del cammino minimo l'algoritmo fa un ultimo controllo per verificare che non ci siano cicli di peso negativo
    for (auto &arco : grafo.lista_archi)
    {
        // dato che abbiamo inserito le nostre informazioni in una tupla adesso le dobbiamo spacchettare
        int u = std::get<0>(arco); // nodo partenza
        int v = std::get<1>(arco); // nodo destinazione
        int w = std::get<2>(arco); // peso dell'arco

        // applichiamo la relax
        if (distanze[u] != inf && distanze[u] + w < distanze[v])
        {
            cout << "Ulteriore relax rilevata, presenza di ciclo negativo!" << endl;
            return;
        }
    }

    // Stampiamo le distanze minime trovate
    cout << "Distanze rilevate dalla sorgente " << sorgente << ": " << endl;
    for (int i = 0; i < Vertici; i++)
    {
        cout << "Nodo: " << i << " ";
        if (distanze[i] == inf)
        {
            cout << "Non raggiungibile!" << endl;
        }
        else
            cout << distanze[i] << endl;
        ;
    }
}