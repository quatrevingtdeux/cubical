#ifndef PARSER_H
#define PARSER_H


#include <iostream>
#include <fstream>
#include <string>
#include "ComplexeCubique.h"

class Parser
{
    public:
        Parser(ComplexeCubique<DIM_C,DIM_P,TYPE> complexe, std::string nomFichier);
        ~Parser();
};

Parser::Parser(std::string nomFichier)
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

        //TODO


        fichier.~ifstream();
    }
}

#endif
