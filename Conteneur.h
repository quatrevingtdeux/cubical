#ifndef CONTENEUR_H
#define CONTENEUR_H

#include <iostream>
#include <cstdlib>

#include <vector>
#include <iterator>
#include "Cellule.h"

class ConteneurVirtuel
{
};

template<int k>
class Conteneur : public ConteneurVirtuel
{
    public:
        Conteneur();
        ~Conteneur();
        bool estValide();
        template<int i> void ajouterCellule(Cellule<i>* cellule);
        void ajouterCellule(Cellule<k>* cellule);
        template<int i> typename std::vector<Cellule<i>*>::iterator trouverCellule(Cellule<i>* cellule);
        typename std::vector<Cellule<k>*>::iterator trouverCellule(Cellule<k>* cellule);
        template<int i> typename std::vector<Cellule<i>*>::iterator trouverIPlus1Cellule(Cellule<i-1>* cellule);
        typename std::vector<Cellule<k>*>::iterator trouverIPlus1Cellule(Cellule<k-1>* cellule);

    private:
        std::vector<Cellule<k>*> cellules;
        Conteneur<k-1>* suivant;
};

template<int k>
Conteneur<k>::Conteneur()
{
    suivant = new Conteneur<k-1>();
}

template<>
Conteneur<0>::Conteneur()
{
    cellules.clear();
    suivant = NULL;
}

template<int k>
Conteneur<k>::~Conteneur()
{
    typename std::vector<Cellule<k>*>::iterator it;
    for(it = cellules.begin(); it != cellules.end(); ++it)
        delete *it;
    cellules.clear();
    delete suivant;
}

template<>
Conteneur<0>::~Conteneur()
{
    typename std::vector<Cellule<0>*>::iterator it;
    for(it = cellules.begin(); it != cellules.end(); ++it)
        delete *it;
    cellules.clear();
}

template<int k>
template<int i>
void Conteneur<k>::ajouterCellule(Cellule<i>* cellule)
{
    suivant->ajouterCellule(cellule);
}

template<int k>
void Conteneur<k>::ajouterCellule(Cellule<k>* cellule)
{
    cellules.push_back(cellule);
}

template<int k>
bool Conteneur<k>::estValide()
{
    typename std::vector<Cellule<k>*>::iterator it;
    for(it = cellules.begin(); it != cellules.end(); ++it)
    {
        if ((*it)->estValide())
            return false;
    }
    return suivant->estValide();
}

template<>
bool Conteneur<0>::estValide()
{
    typename std::vector<Cellule<0>*>::iterator it;
    for(it = cellules.begin(); it != cellules.end(); ++it)
    {
        if ((*it)->estValide())
            return false;
    }
    return true;
}

template<int k>
template<int i>
typename std::vector<Cellule<i>*>::iterator Conteneur<k>::trouverCellule(Cellule<i>* cellule)
{
    typename std::vector<Cellule<k>*>::iterator it;
    for(it = cellules.begin(); it != cellules.end(); ++it)
    {
        if (*it == cellule)
            return it;
    }
    return suivant->trouverIPlus1Cellule<i>(cellule);
}

template<int k>
typename std::vector<Cellule<k>*>::iterator Conteneur<k>::trouverCellule(Cellule<k>* cellule)
{
    return std::find(cellules.begin(), cellules.end(), cellule);
}

template<int k>
template<int i>
typename std::vector<Cellule<i>*>::iterator Conteneur<k>::trouverIPlus1Cellule(Cellule<i-1>* cellule)
{
    return suivant->trouverIPlus1Cellule<i-1>(cellule);
}

template<int k>
typename std::vector<Cellule<k>*>::iterator Conteneur<k>::trouverIPlus1Cellule(Cellule<k-1>* cellule)
{
    typename std::vector<Cellule<k>*>::iterator it;
    for(it = cellules.begin(); it != cellules.end(); ++it)
    {
        std::cout << "BOUCLE\n";
        if ((*it)->hasIMoins1Cellule(cellule))
        {
            std::cout << "GAGNE\n";
            return it;
        }
    }
    std::cout << "FIN FONCTION OK\n";
    return cellules.end();
}

#endif
