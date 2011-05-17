#ifndef PARSER_H
#define PARSER_H


#include <iostream>
#include <fstream>
#include <string>

#include "ComplexeCubique.h"
#include "ParserBoucle.h"
#include "BoucleParser.h"

class Parser
{
    public:
        Parser(ComplexeCubique<DIM_C,DIM_P,TYPE> complexe, std::string nomFichier);
        ~Parser();
};

Parser::Parser(ComplexeCubique<DIM_C,DIM_P,TYPE> complexe, std::string nomFichier)
{
    std::ifstream fichier(nomFichier);

    if (fichier)
    {
        std::string input;
        getline(fichier,input);
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
            fichier.~ifstream();
            exit(EXIT_FAILURE);
	   }
	   
	   std::vector<int> nombreCellules;
        getline(fichier,input);
	   ligne.str(input);
	   // remplissage des nombres maximum de cellules
	   for (int i = 0; !ligne.eof; ++i)
		ligne >> nombreCellules[i];

        //TODO
        // on va faire boucler la classe BoucleParse 
        // pour qu'il récupére les cellules à mettre dans complexe
        // et evitez d'avoir une macro toute moche
		for (int i = 0; i < nombreCellules.size(); ++i)
		{
			BoucleParser<1,nombreCellules[i]> cellulei(complexe, fichier);
		}


        fichier.~ifstream();
    }
}

#endif
