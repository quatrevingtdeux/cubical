#ifndef COMPLEXECUBIQUE_H
#define COMPLEXECUBIQUE_H

template<int n, int k, class T>
class ComplexeCubique
{
	public:
		bool estValide();
		Cellule::iterator trouverCellule(Cellule*);
		Cellule::iterator trouverIPlus1Cellule(Cellule*);
		bool estDansBord(Cellule*, Cellule*);
		void creeBord(Cellule*, 2i pointeurs);
		Cellule* creerCellule(Point);
		void detruire(Cellule *);
		void reduction(Cellule*, Cellule*);
	private:
		vector<Cellule> ensemblesCellules;//TODO virtual cellule
};

#endif
