#ifndef BOUCLEPARSER_H
#define BOUCLEPARSER_H

#include <vector>
#include <fstream>
#include <sstream>
#include "ComplexeCubique.h"

template <int Start, int Dimension>
class BoucleParser
{
	public:
		BoucleParser() {}
		BoucleParser(	ComplexeCubique<DIM_C,DIM_P,TYPE>& complexe,
					std::ifstream& fichier,
					const std::vector<int>& nombreCellules);
		~BoucleParser() {}
};

template <int Start, int Dimension>
BoucleParser<Start, Dimension>::BoucleParser(
							ComplexeCubique<DIM_C,DIM_P,TYPE>& complexe,
							std::ifstream& fichier,
							const std::vector<int>& nombreCellules)
{
	// traitement pour l'ajout de chaque ligne du fichier dans le complexe
	std::string input;
	std::istringstream ligne;
	std::vector<int> val;
	
	for (int i = 0; i < nombreCellules[Start]; ++i)
	{
		std::getline(fichier, input);
		if (input != "")
		{
			ligne.str(input);
			for (int i = 0; i < Start*2; ++i)
				ligne >> val[i];
			
			//Cellule<Start> nouvelleICellule(val);
			
			//complexe.ajouterCellule(
			//	&static_cast<CelluleVirtuelle>(nouvelleICellule));
		}
		
	}
	
	BoucleParser<Start+1, Dimension> traiter(complexe, fichier, nombreCellules);
}



template <int Dimension>
class BoucleParser<0,Dimension>
{
	public:
		BoucleParser() {}
		BoucleParser(	ComplexeCubique<DIM_C,DIM_P,TYPE>& complexe,
					std::ifstream& fichier,
					const std::vector<int>& nombreCellules);
		~BoucleParser() {}
};

template <int Dimension>
BoucleParser<0, Dimension>::BoucleParser(
							ComplexeCubique<DIM_C,DIM_P,TYPE>& complexe,
							std::ifstream& fichier,
							const std::vector<int>& nombreCellules)
{
	// traitement pour l'ajout de chaque ligne du fichier dans le complexe
	std::string input;
	std::istringstream ligne;
	std::vector<TYPE> val;
	
	for (int i = 0; i < nombreCellules[0]; ++i)
	{
		std::getline(fichier, input);
		if (input != "")
		{
			ligne.str(input);
			for (int p = 0; p < DIM_P; ++p)
				ligne >> val[p];
			Point<DIM_P, TYPE> nouveauPoint(val);
			Cellule<0> nouvelle0Cellule(nouveauPoint);
			
			complexe.ajouterCellule(
				&static_cast<CelluleVirtuelle>(nouvelle0Cellule));
		}
		
	}
	
	BoucleParser<1, Dimension> traiter(complexe, fichier, nombreCellules);
}

template <int Dimension>
class BoucleParser<Dimension, Dimension>
{
	public:
		BoucleParser(	ComplexeCubique<DIM_C,DIM_P,TYPE>& complexe,
					std::ifstream& fichier,
					const std::vector<int>& nombreCellules) 
		{ /*pas de code redondant*/ }
};


#endif