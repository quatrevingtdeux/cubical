#ifndef CELLULE_H
#define CELLULE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Point.h"

#define DIM 3
#define TYPE int

// ============================================================
//  Classe fille Cellule (taille > 0)
// ============================================================

template<int i>
class Cellule
{
    public:
        Cellule();
        Cellule(std::vector<Cellule<i-1>*>& cellules);
        ~Cellule();
        int getDimension() const;
        bool estValide() const;
        bool hasIMoins1Cellule(Cellule<i-1>* cellule) const;
        std::vector<Cellule<i-1>*>& getBords();
        Cellule<i-1>& operator[](int indice);
        template<int _i> friend std::ostream& operator<<(std::ostream& sortie, const Cellule<_i>& cellule);
    private:
        std::vector<Cellule<i-1>*> bords;
};

template<int i>
Cellule<i>::Cellule()
{
    for(int j = 0; j < 2*i; j++)
        bords.push_back(new Cellule<i-1>());
}

template<int i>
Cellule<i>::Cellule(std::vector<Cellule<i-1>*>& cellules)
{
    bords = cellules;
}

template<int i>
Cellule<i>::~Cellule()
{
    for(int j=0; j < 2*i; j++)
        delete bords[j];
}

template<int i>
int Cellule<i>::getDimension() const
{
    return i;
}

template<int i>
bool Cellule<i>::estValide() const
{
    return bords.size() == 2*i;
}

template<int i>
bool Cellule<i>::hasIMoins1Cellule(Cellule<i-1>* cellule) const
{
    return std::find(bords.begin(), bords.end(), cellule) != bords.end();
}

template<int i>
std::vector<Cellule<i-1>*>& Cellule<i>::getBords()
{
    return bords;
}

template<int i>
Cellule<i-1>& Cellule<i>::operator[](int indice)
{
    assert(indice >= 0 && indice < 2*getDimension());
    return *bords[indice];
}

template<int i>
std::ostream& operator<<(std::ostream& sortie, const Cellule<i>& cellule)
{
    sortie << "Cellule :" << std::endl;
    sortie << "\tDimension = " << cellule.getDimension() << std::endl;
    sortie << "\tAdresse = " << &cellule << std::endl;
    return sortie;
}

// ============================================================
//  Classe fille Cellule (taille = 0)
// ============================================================

template <>
class Cellule<0>
{
    public:
        Cellule();
        Cellule(Point<DIM,TYPE>& point);
        ~Cellule();
        int getDimension() const;
        bool estValide() const;
        Point<DIM,TYPE>& getPoint();
        TYPE& operator[](int indice);
        friend std::ostream& operator<<(std::ostream& sortie, const Cellule<0>& cellule);
    private:
        Point<DIM,TYPE> point;
};

Cellule<0>::Cellule()
{
}

Cellule<0>::Cellule(Point<DIM,TYPE>& point)
{
    this->point = point;
}

Cellule<0>::~Cellule()
{
    point.~Point();
}

int Cellule<0>::getDimension() const
{
    return 0;
}

bool Cellule<0>::estValide() const
{
    return true;
}

Point<DIM,TYPE>& Cellule<0>::getPoint()
{
    return point;
}

TYPE& Cellule<0>::operator[](int indice)
{
    return point[indice];
}

std::ostream& operator<<(std::ostream& sortie, const Cellule<0>& cellule)
{
    sortie << "Cellule :" << std::endl;
    sortie << "\tDimension = " << cellule.getDimension() << std::endl;
    sortie << "\tAdresse = " << &cellule << std::endl;
    sortie << "\tContenu {\n " << cellule.point << "}" << std::endl;
    return sortie;
}

#endif
