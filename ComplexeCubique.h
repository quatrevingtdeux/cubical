#ifndef COMPLEXECUBIQUE_H
#define COMPLEXECUBIQUE_H

#include <set>
#include <stdarg.h>
#include "Cellule.h"
#include "Conteneur.h"

template<int n, int k, class T>
class ComplexeCubique
{
	public:
		ComplexeCubique();
		bool estValide();
		std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator trouverCellule(VirtualCellule* cellule);
		std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator trouverIPlus1Cellule(VirtualCellule* cellule);
		bool estDansBord(VirtualCellule* c1, VirtualCellule* c2);
		template<int i> void creeBord(Cellule<i,k,T>* cellule, ...);
		void creerCellule(Point<k,T> point);
		void detruire(VirtualCellule* cellule);
		template<int i> bool reduction(Cellule<i,k,T>* c1, Cellule<i+1,k,T>* c2);
	private:
		//Conteneur<Cellule<n>* > conteneur;
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

template<int n, int k, class T>
template<int i>
void ComplexeCubique<n,k,T>::creeBord(Cellule<i,k,T>* cellule, ...)
{
	va_list pa;
	va_start(pa, cellule);
	for(int j = 0; j < i-1; j++)
	{
		cellule.getBord()[j] = va_arg(pa, VirtualCellule*);
		std::cout << "Lecture d'un bord" << std::endl;
	}
 	va_end(pa);
}

template<int n, int k, class T>
void ComplexeCubique<n,k,T>::creerCellule(Point<k,T> point)
{
	Cellule<0,k,T> cellule(point);
	ensemblesCellules.insert(cellule);
}

template<int n, int k, class T>
void ComplexeCubique<n,k,T>::detruire(VirtualCellule* cellule)
{
	std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator it = ensemblesCellules.find(cellule);
	for(it; it != ensemblesCellules.end(); it++)
	{
		if(*it == cellule)
		{
			ensemblesCellules.erase(it);
			break;
		}
	}
	//TODO vérifier validité du complexe en mode debug
}

template<int n, int k, class T>
template<int i>
bool ComplexeCubique<n,k,T>::reduction(Cellule<i,k,T>* c1, Cellule<i+1,k,T>* c2)
{
	// c1 soit dans le bord de c2 ;
	bool valide = false;
	for(int j = 0; j < 2*(i+1); j++)
	{
		if(c2->getBord()[j] == c1)
		{
			valide = true;
			break;
		}
	}
	
	if(!valide)
		return false;
	
	// Il n’existe pas de (i + 1)-cellule (à part c2) ayant c1 dans son bord
	Cellule<i+1,k,T> bidon;
	std::multiset<VirtualCellule*,VirtualCellule::PointerCelluleGreater>::iterator it = ensemblesCellules.find(bidon);
	for(it; it != ensemblesCellules.end() && (*it)->getDimension() == i+1; it++)
	{
		for(int j = 0; j < 2*(i+1); j++)
		{
			if((*it)->getBord()[j] == c1 && *it != c2)
			{
				return false;
			}
		}
	}
	
	// Il n’existe pas de (i + 2)-cellule ayant c2 dans son bord
	Cellule<i+2,k,T> bidon2;
	it = ensemblesCellules.find(bidon2);
	for(it; it != ensemblesCellules.end() && (*it)->getDimension() == i+2; it++)
	{
		for(int j = 0; j < 2*(i+2); j++)
		{
			if((*it)->getBord()[j] == c2)
			{
				return false;
			}
		}
	}
	
	return true;
	//TODO vérifier validité du complexe en mode debug
}

#endif
