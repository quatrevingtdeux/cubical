#ifndef COMPLEXECUBIQUE_H
#define COMPLEXECUBIQUE_H

#include <set>
#include <stdarg.h>
#include "Conteneur.h"

template<int n, int k, class T>
class ComplexeCubique
{
	public:
		ComplexeCubique();
                ~ComplexeCubique();
		bool estValide();
                //template<int i> Cellule<i>* trouverCellule(Cellule<i>* cellule);
                //template<int i> std::vectorCellule<i>* trouverIPlus1Cellule(Cellule<i>* cellule);
                template<int i> bool estDansBord(Cellule<i>* c1, Cellule<i>* c2);
                template<int i> void creerCellule(Cellule<i>* cellule, ...);
                void creerCellule(Point<k,T>* point);
                template<int i> void detruire(Cellule<i>* cellule);
		template<int i> bool reduction(Cellule<i,k,T>* c1, Cellule<i+1,k,T>* c2);
	private:
                ConteneurVirtuel conteneur;
};

template<int n, int k, class T>
ComplexeCubique<n,k,T>::ComplexeCubique()
{
}

template<int n, int k, class T>
ComplexeCubique<n,k,T>::~ComplexeCubique()
{
	ensemblesCellules.clear();
}

#endif
