#ifndef CELLULE_H
#define CELLULE_H

#include <iostream>
#include <vector>
#include "Point.h"

// ============================================================
//  Classe virtuelle VirtualCellule
// ============================================================

class VirtualCellule
{
    public:
        virtual ~VirtualCellule();
        int getDimension() const;
        friend std::ostream& operator<<(std::ostream& sortie, const VirtualCellule& cellule);
    protected:
        std::vector<VirtualCellule*> bord;

    struct PointerCelluleGreater
    {
        bool operator()(VirtualCellule* c1, VirtualCellule* c2)
        {
                return c1->getDimension() > c2->getDimension();
        }
    };
};

int VirtualCellule::getDimension() const
{
    return bord.size() / 2;
}

std::ostream& operator<<(std::ostream& sortie, const VirtualCellule& cellule)
{
    sortie << "Cellule :" << std::endl;
    sortie << "\tDimension = " << cellule.getDimension() << std::endl;
    sortie << "\tAdresse = " << &cellule << std::endl;
    return sortie;
}

VirtualCellule::~VirtualCellule()
{
    std::cout << "VirtualCellule::~VirtualCellule()" << std::endl;
    for(unsigned int i=0; i < bord.size(); i++)
    {
        delete bord[i];
    }
}

// ============================================================
//  Classe fille Cellule (taille > 0)
// ============================================================

template<int i, int k, typename T>
class Cellule : public VirtualCellule
{
    public:
        Cellule();
        Cellule(std::vector<Cellule<i-1,k,T>*> cellulesBord);
        ~Cellule();
        VirtualCellule& getBord(int indice);
};

template<int i, int k, typename T>
Cellule<i,k,T>::Cellule()
{
    std::cout << "Cellule<i,k,T>::Cellule(): VirtualCellule()" << std::endl;
    for(int j = 0; j < 2*i; j++)
    {
        bord.push_back(new Cellule<i-1,k,T>());
    }
}

template<int i, int k, typename T>
Cellule<i,k,T>::Cellule(std::vector<Cellule<i-1,k,T>* > cellulesBord)
{
    std::cout << "Cellule<i,k,T>::Cellule(std::vector<Cellule<i-1,k,T>* > cellulesBord): VirtualCellule()" << std::endl;
    this->bord = cellulesBord;
}

template<int i, int k, typename T>
Cellule<i,k,T>::~Cellule()
{
    std::cout << "Cellule<i,k,T>::~Cellule()" << std::endl;
}

template<int i, int k, typename T>
VirtualCellule& Cellule<i,k,T>::getBord(int indice)
{
    assert(indice >= 0 && indice < 2*getDimension());
    return *(bord[indice]);
}

// ============================================================
//  Classe fille Cellule (taille = 0)
// ============================================================
template<int k, typename T>
class Cellule<0,k,T> : public VirtualCellule
{
    public:
        Cellule();
        Cellule(Point<k,T>& point);
        ~Cellule();
        Point<k,T>& getSommet();
    private:
        Point<k,T> sommet;
};

template<int k, typename T>
Cellule<0,k,T>::Cellule()
{
    std::cout << "Cellule<0,k,T>::Cellule(): VirtualCellule()" << std::endl;
}

template<int k, typename T>
Cellule<0,k,T>::Cellule(Point<k,T>& point)
{
    sommet = point;
}

template<int k, typename T>
Cellule<0,k,T>::~Cellule()
{
    std::cout << "Cellule<0,k,T>::~Cellule()" << std::endl;
    sommet.~Point();
}

template<int k, typename T>
Point<k,T>& Cellule<0,k,T>::getSommet()
{
    return sommet;
}

#endif
