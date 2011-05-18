#ifndef BOUCLEPARSER_H
#define BOUCLEPARSER_H


#include "ComplexeCubique.h"

template <int Start, int End>
class BoucleParser
{
	public:
		BoucleParser();
		BoucleParser(	ComplexeCubique complexe<DIM_C,DIM_P,TYPE>, 
					std::ifstream fichier);
		~BoucleParser() {}
};

template <int Start, int End>
BoucleParser<Start,End>::BoucleParser(	ComplexeCubique complexe<DIM_C,DIM_P,TYPE>, 
								std::ifstream fichier)
{
	
	
	
}



#endif
