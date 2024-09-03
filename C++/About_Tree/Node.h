#pragma once
#include<iostream>
class Node
{
private:
    int key;
public:
    Node* sx=nullptr;
    Node* dx=nullptr;
    Node* parent;
    Node(){};
    //Node(Node* s, Node* d, int k): sx(s), dx(d), key(k){};
    Node(int k):key(k){};
    /*Node(Node* s,int k):sx(s),key(k){};
    Node(Node* d,int k):dx(d),key(k){};*/
    int getKey(){return key;};
    void setKey(int k){key=k;};
    ~Node();
};

