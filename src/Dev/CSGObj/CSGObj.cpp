#include "CSGObj.h"

CSGObj::CSGObj(Figure& figure)
{
    node = new Node;
    node->data.figure = &figure;
    node->leftChild = NULL;
    node->rightChild = NULL;
}

CSGObj& CSGObj::operator=(const CSGObj& C)
{
    node = C.node;
    return *this;
}

CSGObj CSGObj::operator|(const CSGObj& C)
{
    CSGObj R;
    R.node = new Node;
    R.node->data.operate = '|';
    R.node->leftChild = this->node;
    R.node->rightChild = C.node;
    return R;
}

CSGObj CSGObj::operator&(const CSGObj& C)
{
    CSGObj R;
    R.node = new Node;
    R.node->data.operate = '&';
    R.node->leftChild = this->node;
    R.node->rightChild = C.node;
    return R;
}

CSGObj CSGObj::operator~()
{
    CSGObj R;
    R.node = new Node;
    R.node->data.operate = '~';
    R.node->leftChild = NULL;
    R.node->rightChild = this->node;
    return R;
}

CSGObj CSGObj::getLeftChild()
{
    return node->leftChild;
}

CSGObj CSGObj::getRightChild()
{
    return node->rightChild;
}

bool CSGObj::isLeaf()
{
    return !(node->leftChild) && !(node->rightChild);
}

CSGObj::Node CSGObj::getData()
{
    return *node;
}

CSGObj::SDFData CSGObj::SDF(Vector pos)
{
    SDFData result;
    if (isLeaf())
    {
        result.distance = node->data.figure->tSDF(pos);
        result.figure = node->data.figure;
        return result;
    }
    else
    {
        switch (node->data.operate)
        {
        case '|':
        {
            SDFData leftSDF = getLeftChild().SDF(pos);
            SDFData rightSDF = getRightChild().SDF(pos);
            return leftSDF.distance > rightSDF.distance ? rightSDF : leftSDF;
            break;
        }
        case '&':
        {
            SDFData leftSDF = getLeftChild().SDF(pos);
            SDFData rightSDF = getRightChild().SDF(pos);
            return leftSDF.distance > rightSDF.distance ? leftSDF : rightSDF;
            break;
        }
        case '~':
        {
            SDFData rightSDF = getRightChild().SDF(pos);
            rightSDF.distance = -rightSDF.distance;
            return rightSDF;
        }
        }
    }
}
