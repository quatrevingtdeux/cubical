#ifndef COMPLEXECUBIQUE_H
#define COMPLEXECUBIQUE_H

#include "Cellule.h"

template<int n, int k, class T>
class ComplexeCubique
{
	public:
		bool estValide();
		/*VirtualCellule::iterator trouverCellule(VirtualCellule*);
		VirtualCellule::iterator trouverIPlus1Cellule(VirtualCellule*);
		bool estDansBord(VirtualCellule*, VirtualCellule*);
		void creeBord(VirtualCellule*, 2i pointeurs);
		Cellule* creerCellule(Point);
		void detruire(VirtualCellule *);
		void reduction(VirtualCellule*, Cellule*);*/
	private:
		VirtualCellule* ensemblesCellules[n];
};

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
		for(int i = 1; i <= n; i++)
		{
			Cellule<i,k,T>* cellule = this->ensemblesCellules[i];
			for(int j = 0; j < 2*i; j++)
			{
				if(cellule->getBord()[j] == NULL)
					return false;
			}
		}
		return true;
	}
}

#endif