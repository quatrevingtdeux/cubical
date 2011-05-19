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
	int indice;

	for (int i = 0; i < nombreCellules[Indice]; ++i)
	{
		std::getline(fichier, input);

		ligne.clear();
		ligne.str(input);

		if (input.empty())
			--i;
		else
		{
			for (int i = 0; i < Indice*2; ++i)
			{
				ligne >> indice;
				indiceCellules.push_back(indice);
			}

			complexe.creerCellule<Indice>(indiceCellules);
			indiceCellules.clear();
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

		ligne.clear();
		ligne.str(input);

		if (input.empty())
			i--;
		else
		{
			TYPE valeur;
			val.clear();
			for (int p = 0; p < DIM_P; ++p)
			{
				ligne >> valeur;
				val.push_back(valeur);
			}

			Point<DIM_P,TYPE>* nouveauPoint = new Point<DIM_P,TYPE>(val);

			complexe.creerCellule(nouveauPoint);
			delete nouveauPoint;
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
		{ /*pas de code redondant*/
			(void) complexe;
			(void) fichier;
			(void) nombreCellules;
		}
};


#endif
