#pragma once
#include <iostream>
#include "Node_class.h"

using namespace std;

class BST_class
{
    private:
    Node_class* radice;
    int n_nodi;
    public:
    BST_class(): radice(NULL), n_nodi(0){};
    Node_class* getRadice(){return radice;};
    Node_class* insert_node(Node_class* node, const Animal_class& obj);
    Node_class* newNode(const Animal_class& ob);
    void print_BST(Node_class* node);

};
Node_class* BST_class::newNode(const Animal_class& ob)
{
    Node_class* new_node = new Node_class;
    new_node->obj= dynamic_cast<Animal_class*>(ob);
    new_node->left=new_node->right=NULL;
    return new_node;

}
Node_class* BST_class::insert_node(Node_class* node, const Animal_class& obj)
{
    if(node==NULL)
    {
        node=newNode(obj);
    }

    if(obj->getNome() == node->obj->getNome())
    {
        node->left=insert_node(node->left,obj);
    }
    else
    {
        node->right=insert_node(node->right,obj);
    }
    return node;
}
void BST_class::print_BST(Node_class* node)
{
    if(node != nullptr)
    {
        print_BST(node->left);
        node->obj->stampa_animale();
        print_BST(node->right);
    }
}