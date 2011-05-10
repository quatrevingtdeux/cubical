#ifndef COMPLEXECUBIQUE_H
#define COMPLEXECUBIQUE_H

#include <set>
#include "Cellule.h"

template<int n, int k, class T>
class ComplexeCubique
{
	public:
		ComplexeCubique();
		bool estValide();
		std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator trouverCellule(VirtualCellule* cellule);
		std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator trouverIPlus1Cellule(VirtualCellule* cellule);
		bool estDansBord(VirtualCellule* c1, VirtualCellule* c2);
		/*void creeBord(VirtualCellule*, 2i pointeurs);
		Cellule* creerCellule(Point);
		void detruire(VirtualCellule *);
		void reduction(VirtualCellule*, Cellule*);*/
	private:
		std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater> ensemblesCellules;
};

template<int n, int k, class T>
ComplexeCubique<n,k,T>::ComplexeCubique()
{
}

template<int n, int k, class T>
bool ComplexeCubique<n,k,T>::estValide()
{
	//Vérifie que chaque i-cellule possède bien 2*i (i-1)-cellules dans son bord (des pointeurs non NULL)
	if(n == 0)
	{
		return true;
	}
	else
	{
		for(int i = 1; i < n; i++)
		{
			std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator it;
			for(it = ensemblesCellules.begin(); it != ensemblesCellules.end(); it++)
			{
				if(!(*it)->estValide())
					return false;
			}
		}
		return true;
	}
}

template<int n, int k, class T>
std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator ComplexeCubique<n,k,T>::trouverCellule(VirtualCellule* cellule)
{
	std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator it = ensemblesCellules.find(cellule);
	for(it; it != ensemblesCellules.end() && (*it)->getDimension() == cellule->getDimension(); it++)
	{
		if(*it == cellule)
			return it;
	}
	return ensemblesCellules.end();
}

template<int n, int k, class T>
std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator ComplexeCubique<n,k,T>::trouverIPlus1Cellule(VirtualCellule* cellule)
{
	//const int dimension = cellule->getDimension()+1;
	//Cellule<dimension,k,T> jump;
	//std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator it = ensemblesCellules.find(jump);
	std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator it = ensemblesCellules.begin();
	for(it; it != ensemblesCellules.end() && (*it)->getDimension() == cellule->getDimension()+1; it++)
	{
		for(int i = 0; i < 2*cellule->getDimension()+1; i++)
		{
			if((*it)->getBord()[i] == cellule)
				return it;
		}
	}
	return ensemblesCellules.end();
}

template<int n, int k, class T>
bool ComplexeCubique<n,k,T>::estDansBord(VirtualCellule* c1, VirtualCellule* c2)
{
	for(int i = c2->getDimension(); i < 2*c2->getDimension(); i++)
	{
		if(c2->getBord()[i] == c1)
			return true;
	}
	return false;
}

#endif
