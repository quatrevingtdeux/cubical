#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "ComplexeCubique.h"
#include "ParserBoucle.h"
#include "BoucleParser.h"

class Parser
{
	public:
		Parser( 	ComplexeCubique<DIM_C,DIM_P,TYPE> complexe,
				char* nomFichier);
		~Parser() {}
};

Parser::Parser(ComplexeCubique<DIM_C,DIM_P,TYPE> complexe, char* nomFichier)
{
	std::ifstream fichier(nomFichier, std::ifstream::in);

	if (fichier)
	{
		std::string input;
		std::getline(fichier,input);
		std::istringstream ligne(input);

		int dim_complex, dim_points;
		ligne >> dim_complex >> dim_points;
		if (dim_complex != DIM_C || dim_points != DIM_P)
		{
			std::cout << "Dimensions du complexe, des points";
			std::cout << " ou type des points non concordantes :" << std::endl;
			std::cout << "Vérifiez les valeurs et recompilez" << std::endl;
			std::cout << "dim comple:" << dim_complex << " != " << DIM_C<< std::endl;
			std::cout << "dim points:" << dim_points << " != " << DIM_P << std::endl;
			fichier.std::ifstream::~ifstream();
			exit(EXIT_FAILURE);
		}

		std::vector<int> nombreCellules;
		std::getline(fichier,input);
		ligne.str(input);
		// remplissage des nombres maximum de cellules
		int nb;
		while (!ligne.eof())
		{
			ligne >> nb;
			nombreCellules.push_back(nb);
		}

		//TODO
		// on va faire boucler la classe BoucleParse
		// pour qu'il récupére les cellules à mettre dans complexe
		// et evitez d'avoir une macro toute moche
			
		// DIM_C+1 : evite d'avoir du code redondant
		BoucleParser<0,DIM_C+1> cellulei(complexe, fichier, nombreCellules);

		fichier.std::ifstream::~ifstream();
	}
}

#endif

