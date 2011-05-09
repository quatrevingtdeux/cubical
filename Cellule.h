#ifndef CELLULE_H
#define CELLULE_H

#include <iostream>
#include "Point.h"

class VirtualCellule
{
};

template<int i, int k, typename T>
class Cellule : virtual VirtualCellule
{
	public:
		Cellule();
		~Cellule();
		Cellule<i-1,k,T>** getBord();
		
	private:
		Cellule<i-1,k,T>* bord[2*i];
};


template<int k, typename T>
class Cellule<0,k,T> : virtual VirtualCellule
{
	public:
		Cellule() : sommet(new Point<k,T>()) {
	std::cout << "Création 0-Cellule" << std::endl;}
		~Cellule();
		
	private:
		Point<k,T>* sommet;
};

template<int i, int k, typename T>
Cellule<i,k,T>::Cellule()
{
	std::cout << "Création " << i << "-Cellule" << std::endl;
	for(int j = 0; j < 2*i; j++)
		bord[j] = new Cellule<i-1,k,T>();
}

template<int i, int k, typename T>
Cellule<i,k,T>::~Cellule()
{
	for(int j = 0; j < 2*i; j++)
		delete bord[j];
}

template<int i, int k, typename T>
Cellule<i-1,k,T>** Cellule<i,k,T>::getBord()
{
	return bord;
}

template<int k, typename T>
Cellule<0,k,T>::~Cellule()
{
	delete sommet;
}

#endif
