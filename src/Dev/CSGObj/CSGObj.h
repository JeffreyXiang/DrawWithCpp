#ifndef CSGOBJ_H
#define CSGOBJ_H

#include <Figure/Figure.h>
#include <Vector/Vector.h>

class CSGObj
{
    private:
        typedef union Data
        {
            char operate;
            Figure* figure;
        }Data;

        typedef struct Node
        {
            Data data;
            struct Node* leftChild;
            struct Node* rightChild;
        }Node;

        Node* node;

    public:
        typedef struct SDFData
        {
            double distance;
            Figure* figure;
        }SDFData;

        CSGObj() : node(NULL) {}
        CSGObj(const CSGObj& C) : node(C.node) {}
        CSGObj(Node* node) : node(node) {}

        CSGObj(Figure& figure);
        CSGObj& operator=(const CSGObj& C);
        CSGObj operator|(const CSGObj& C);
        CSGObj operator&(const CSGObj& C);
        CSGObj operator~();
        CSGObj getLeftChild();
        CSGObj getRightChild();
        bool isLeaf();
        Node getData();
        SDFData SDF(Vector pos);
};

#endif