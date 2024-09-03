#pragma once
#include"Cat_class.h"
#include"Dog_class.h"
#include"Animal_class.h"

using namespace std;

class Node_class
{
    public:
    Animal_class* obj;
    Node_class* left;
    Node_class* right;

};