#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>

struct archi
{
    int verso;
    int peso;
};


class Class_graph
{
private:
    int Vertici;
public:
    std::vector<std::vector<archi>> adj; //Liste di adiacenza vector di vector di tipo archi
    std::vector<std::tuple<int,int,int>> lista_archi; //lista degli archi con (u,v,w) = (partenza, arrivo, peso)
    Class_graph(int n_nodi): Vertici(n_nodi), adj(n_nodi){};
    
    //metodi
    void add_arco(int u, int v, int w){
        adj[u].push_back({v,w});
        lista_archi.push_back(std::make_tuple(u,v,w));
    }

    void display(){
        std::cout<< "Liste di adiacenza" << std::endl;
        for (int i = 0; i < Vertici; i++)
        {
            std::cout<<"Nodo"<<i<<":";
            for(auto& arco : adj[i]){
                std::cout<<"->"<<"(nodo:"<<arco.verso <<" peso:"<<arco.peso<<")";
            }
            std::cout<<std::endl;
        }
        
    }

};


