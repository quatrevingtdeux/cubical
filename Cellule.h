#ifndef CELLULE_H
#define CELLULE_H

#include <iostream>
#include "Point.h"

class VirtualCellule
{
	public:

                virtual ~VirtualCellule() {}
                virtual VirtualCellule** getBord() = 0;
                virtual bool estValide() = 0;
                virtual int getDimension() = 0;
		
		struct PointerCelluleGreater
		{
			bool operator()(VirtualCellule* c1, VirtualCellule* c2)
			{
				return c1->getDimension() > c2->getDimension();
			}
		};
};

template<int i, int k, typename T>
class Cellule : public VirtualCellule
{
	public:
		Cellule();
		~Cellule();
		VirtualCellule** getBord();
		bool estValide();
		int getDimension();
		
	private:
		Cellule<i-1,k,T>* bord[2*i];
};

template<int k, typename T>
class Cellule<0,k,T> : public VirtualCellule
{
	public:
                Cellule() : VirtualCellule() { std::cout << "FAIL" << std::endl; }
                Cellule(Point<k,T>* point) : VirtualCellule(), sommet(point) { std::cout << "Création 0-Cellule" << std::endl; }
		~Cellule();
		VirtualCellule** getBord();
		bool estValide();
		int getDimension();
		
	private:
		Point<k,T>* sommet;
};

template<int i, int k, typename T>
Cellule<i,k,T>::Cellule(): VirtualCellule()
{
	std::cout << "Création " << i << "-Cellule" << std::endl;
	for(int j = 0; j < 2*i; j++)
        {
		bord[j] = new Cellule<i-1,k,T>();
                std::cout << "Taille=" << i-1 << std::endl;
        }
}

template<int i, int k, typename T>
Cellule<i,k,T>::~Cellule()
{
	for(int j = 0; j < 2*i; j++)
		delete bord[j];
}

template<int i, int k, typename T>
VirtualCellule** Cellule<i,k,T>::getBord()
{
	return bord;
}

template<int i, int k, typename T>
bool Cellule<i,k,T>::estValide()
{
	return true;
}

template<int i, int k, typename T>
int Cellule<i,k,T>::getDimension()
{
	return i;
}

template<int k, typename T>
Cellule<0,k,T>::~Cellule()
{
	delete sommet;
}

template<int k, typename T>
VirtualCellule** Cellule<0,k,T>::getBord()
{
	return NULL;
}

template<int k, typename T>
bool Cellule<0,k,T>::estValide()
{
	return true;
}

template<int k, typename T>
int Cellule<0,k,T>::getDimension()
{
	return 0;
}

#endif
