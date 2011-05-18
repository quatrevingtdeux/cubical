#ifndef BOUCLEPARSER_H
#define BOUCLEPARSER_H

#include <vector>
#include <fstream>
#include <sstream>
#include "ComplexeCubique.h"

#define DIM_C 3
#define DIM_P 3
#define TYPE int

template <int Indice, int Dimension>
class BoucleParser
{
	public:
		BoucleParser() {}
		BoucleParser(	ComplexeCubique<DIM_C,DIM_P,TYPE>& complexe,
					std::ifstream& fichier,
					const std::vector<int>& nombreCellules);
		~BoucleParser() {}
};

template <int Indice, int Dimension>
BoucleParser<Indice, Dimension>::BoucleParser(
							ComplexeCubique<DIM_C,DIM_P,TYPE>& complexe,
							std::ifstream& fichier,
							const std::vector<int>& nombreCellules)
{
	// traitement pour l'ajout de chaque ligne du fichier dans le complexe
	std::string input;
	std::istringstream ligne;
     std::vector<int> indiceCellules;
	
	for (int i = 0; i < nombreCellules[Indice]; ++i)
	{
		std::getline(fichier, input);
		if (input != "")
			--i;
		else
		{
			std::string indice;
			ligne.str(input);
			for (int i = 0; i < Indice*2; ++i)
			{
				ligne >> indice;
                    indiceCellules.push_back(atoi(indice.c_str()));
               }

               complexe.creerCellule<Indice>(indiceCellules);
          }
	}
	
	BoucleParser<Indice+1, Dimension> traiter(complexe, fichier, nombreCellules);
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
			TYPE valeur;
			ligne.str(input);
			for (int p = 0; p < DIM_P; ++p)
			{
				ligne >> valeur;
				val.push_back(valeur); // TODO PROBLEME ne donne que des zeros
			}
               Point<DIM_P,TYPE>* nouveauPoint = new Point<DIM_P,TYPE>(val);
               val.clear();

               complexe.creerCellule(nouveauPoint);
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
