#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include "ComplexeCubique.h"

class Parser
{
    public:
        Parser(std::string nomFichier);
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
        if (dim_complex != DIMENSION_COMPLEXE)
        {
            std::cout << "Dimensions du complexe non concordantes : " << dim_complex << " != " << DIMENSION_COMPLEXE << std::endl;
            fichier.~ifstream();
            exit(EXIT_FAILURE);
        }
        else if (dim_points != DIMENSION_POINTS)
        {
            std::cout << "Dimensions des points non concordantes : " << dim_points << " != " << DIMENSION_POINTS << std::endl;
            fichier.~ifstream();
            exit(EXIT_FAILURE);
        }

        //TODO


        fichier.~ifstream();
    }
}

#endif
