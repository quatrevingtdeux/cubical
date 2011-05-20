#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "ComplexeCubique.h"
#include "ParserBoucle.h"

class Parser
{
public:
	Parser(	ComplexeCubique<DIM_C,DIM_P,TYPE>& complexe,
			char* nomFichier);
	~Parser() {}
};

Parser::Parser(ComplexeCubique<DIM_C,DIM_P,TYPE>& complexe, char* nomFichier)
{
	std::ifstream fichier(nomFichier, std::ifstream::in);

	if (fichier)
	{
		std::string input;
		std::getline(fichier,input);
		std::istringstream ligne(input);

		int dim_complex, dim_points;
		ligne >> dim_complex >> dim_points;
		ligne.clear();
		if (dim_complex != DIM_C || dim_points != DIM_P)
		{
			std::cout << "Dimensions du complexe, des points";
			std::cout << " ou type des points non concordants." << std::endl;
			std::cout << "Dimension complexe : " << dim_complex << " != " << DIM_C<< std::endl;
			std::cout << "Dimension points : " << dim_points << " != " << DIM_P << std::endl;
			fichier.std::ifstream::~ifstream();
			exit(EXIT_FAILURE);
		}

		std::vector<int> nombreCellules;
		std::getline(fichier,input);
		ligne.str(input);
		// remplissage des nombres maximum de cellules
		int nb;
		while (ligne >> nb)
			nombreCellules.push_back(nb);

		// DIM_C+1 : evite d'avoir du code redondant
		BoucleParser<0,DIM_C+1> boucle(complexe, fichier, nombreCellules);

		fichier.std::ifstream::~ifstream();
	}
	else
	{
		std::cout << "Impossible de trouver le fichier " << nomFichier << std::endl;
		fichier.std::ifstream::~ifstream();
		exit(EXIT_FAILURE);
	}
}

#endif

