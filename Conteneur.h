#ifndef CONTENEUR_H_
#define CONTENEUR_H_

#include <iostream>
#include <cstdlib>

#include <vector>
#include "Cellule.h"

template <int k>
class Conteneur
{
	public:
		Conteneur();
		~Conteneur();
		
		template <int n>
		std::vector<Cellule<n,3, int> * >& GetVector();
		
	private:
		std::vector<Cellule<k,3, int>* > cellules;
		Conteneur<k - 1>* suivant;
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

template <int k>
template <int n>
std::vector<Cellule<n, 3, int>* >& Conteneur<k>::GetVector()
{
	if (n == 0)
		exit(1);
	
	if (n == k)
		return cellules;
	else
		return suivant.GetVector();
}


#endif
