#ifndef COMPLEXECUBIQUE_H
#define COMPLEXECUBIQUE_H

#include <set>
#include <stdarg.h>
#include "Conteneur.h"
#include "Cellule.h"

#define DIMENSION_COMPLEXE 3
#define DIMENSION_POINTS 3

template<int n, int k, class T>
class ComplexeCubique
{
	public:
		ComplexeCubique();
                ~ComplexeCubique();
		bool estValide();
                template<int i> typename std::vector<Cellule<i>*>::iterator trouverCellule(Cellule<i>* cellule);
                template<int i> typename std::vector<Cellule<i+1>*>::iterator trouverIPlus1Cellule(Cellule<i>* cellule);
                template<int i> bool estDansBord(Cellule<i>* c1, Cellule<i>* c2);
                template<int i> void creerCellule(std::vector<Cellule<i>*>& cellules);
                void creerCellule(std::vector<Cellule<0>*>& cellules);
                Cellule<0>* creerCellule(Point<k,T>& point);
                template<int i> void supprimerCellule(Cellule<i>& cellule);
                //template<int i> bool reduction(Cellule<i,k,T>* c1, Cellule<i+1,k,T>* c2);
	private:
                Conteneur<n> conteneur;
};

template<int n, int k, class T>
ComplexeCubique<n,k,T>::ComplexeCubique()
{
}

template<int n, int k, class T>
ComplexeCubique<n,k,T>::~ComplexeCubique()
{
    conteneur.~Conteneur();
}

template<int n, int k, class T>
bool ComplexeCubique<n,k,T>::estValide()
{
    return conteneur.estValide();
}

template<int n, int k, class T>
template<int i>
typename std::vector<Cellule<i>*>::iterator ComplexeCubique<n,k,T>::trouverCellule(Cellule<i>* cellule)
{
    return conteneur.trouverCellule(cellule);
}

template<int n, int k, class T>
template<int i>
typename std::vector<Cellule<i+1>*>::iterator ComplexeCubique<n,k,T>::trouverIPlus1Cellule(Cellule<i>* cellule)
{
    return conteneur.trouverIPlus1Cellule(cellule);
}

template<int n, int k, class T>
template<int i>
bool ComplexeCubique<n,k,T>::estDansBord(Cellule<i>* c1, Cellule<i>* c2)
{
    return c2->hasIMoins1Cellule(c1);
}

template<int n, int k, class T>
template<int i>
void ComplexeCubique<n,k,T>::creerCellule(std::vector<Cellule<i>*>& cellules)
{
    Cellule<i/2>* cellule = new Cellule<i/2>(cellules);
    //conteneur.ajouterCellule();
}

template<int n, int k, class T>
void ComplexeCubique<n,k,T>::creerCellule(std::vector<Cellule<0>*>& cellules)
{
    Cellule<1>* cellule = new Cellule<1>(cellules);
    //conteneur.ajouterCellule();
}

template<int n, int k, class T>
Cellule<0>* ComplexeCubique<n,k,T>::creerCellule(Point<k,T>& point)
{
    Cellule<0>* cellule = new Cellule<0>(point);
    conteneur.ajouterCellule(cellule);
    return cellule;
}

template<int n, int k, class T>
template<int i> void ComplexeCubique<n,k,T>::supprimerCellule(Cellule<i>& cellule)
{
    conteneur.supprimerCellule(&cellule);
}

#endif
