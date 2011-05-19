#ifndef CELLULE_H
#define CELLULE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Point.h"

#define DIM 3
#define TYPE int

// ============================================================
// Classe virtuelle CelluleVirtuelle
// ============================================================

class CelluleVirtuelle
{
	public:
		virtual ~CelluleVirtuelle();
		int getDimension() const;
		std::vector<CelluleVirtuelle*>* getBords();
		bool hasIMoins1Cellule(CelluleVirtuelle* cellule);
		friend std::ostream& operator<<(std::ostream& sortie, const CelluleVirtuelle& cellule);
	protected:
		std::vector<CelluleVirtuelle*> bords;
};

int CelluleVirtuelle::getDimension() const
{
	return bords.size() / 2;
}

std::vector<CelluleVirtuelle*>* CelluleVirtuelle::getBords()
{
	return &bords;
}

bool CelluleVirtuelle::hasIMoins1Cellule(CelluleVirtuelle* cellule)
{
	return find(bords.begin(), bords.end(), cellule) != bords.end();
}

std::ostream& operator<<(std::ostream& sortie, const CelluleVirtuelle& cellule)
{
	sortie << "Cellule :" << std::endl;
	sortie << "\tDimension = " << cellule.getDimension() << std::endl;
	sortie << "\tAdresse = " << &cellule << std::endl;
	return sortie;
}

CelluleVirtuelle::~CelluleVirtuelle()
{
}

// ============================================================
// Classe fille Cellule (taille > 0)
// ============================================================

template<int i>
class Cellule : public CelluleVirtuelle
{
	public:
		Cellule();
		Cellule(std::vector<Cellule<i-1>*>* cellulesbords);
		~Cellule();
};

template<int i>
Cellule<i>::Cellule()
{
	for(int j = 0; j < 2*i; j++)
	{
		bords.push_back(new Cellule<i-1>());
	}
}

template<int i>
Cellule<i>::Cellule(std::vector<Cellule<i-1>*>* cellulesbords)
{
	typename std::vector<Cellule<i-1>*>::iterator it;
	for(it = cellulesbords->begin(); it != cellulesbords->end(); ++it)
		bords.push_back(*it);
}

template<int i>
Cellule<i>::~Cellule()
{
}

// ============================================================
// Classe fille Cellule (taille = 0)
// ============================================================
template<>
class Cellule<0> : public CelluleVirtuelle
{
	public:
		Cellule();
		Cellule(Point<DIM,TYPE>& point);
		~Cellule();
		Point<DIM,TYPE>& getSommet();
	private:
		Point<DIM,TYPE> sommet;
};

Cellule<0>::Cellule()
{
}

Cellule<0>::Cellule(Point<DIM,TYPE>& point)
{
	sommet = point;
}

Cellule<0>::~Cellule()
{
	sommet.~Point();
}

Point<DIM,TYPE>& Cellule<0>::getSommet()
{
	return sommet;
}

#endif
