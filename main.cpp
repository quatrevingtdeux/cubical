
#include <iostream>
#include <string>
#include <stdlib.h>
#include "ComplexeCubique.h"
#include "Cellule.h"

#include "Parser.h"

using namespace std;

int main(int argc, char** argv)
{
    ComplexeCubique<DIM_C,DIM_P,TYPE> comp;
    if (argc == 2)
    {
        Parser parseCeFichier(comp, argv[1]);
        std::cout << comp << std::endl;
    }

    comp.~ComplexeCubique();
}
