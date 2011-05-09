#ifndef CELLULE_H
#define CELLULE_H

#include <iostream>

#include "Point.h"

template<int i, int k, typename T>
class Cellule
{
	public:
		Cellule();
		~Cellule();
		
	private:
		Cellule<i-1,k,T>* bord[2*i];
};


template<int k, typename T>
class Cellule<0, k, T>
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

template<int k, typename T>
Cellule<0,k,T>::~Cellule()
{
	delete sommet;
}

#endif

