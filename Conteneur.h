#ifndef CONTENEUR_H
#define CONTENEUR_H

#include <iostream>
#include <cstdlib>

#include <vector>
#include "Cellule.h"

class ConteneurVirtuel
{
};

template <int k>
class Conteneur : public ConteneurVirtuel
{
    public:
        Conteneur();
        ~Conteneur();

    private:
        std::vector<Cellule<k,3, int>* > cellules;
        Conteneur<k-1>* suivant;
};

template <int k>
Conteneur<k>::Conteneur()
{
    suivant = new Conteneur<k - 1>();
}

template <>
Conteneur<0>::Conteneur()
{
    suivant = 0;
}

#endif
