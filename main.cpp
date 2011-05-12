#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "ComplexeCubique.h"

using namespace std;

int main2(int argc, char** argv)
{
	/*int tab[5] = {31,32,33,34,35};
	Point<5,int> p(tab);
	std::cout << "Dimension=" << p.getDimension() << std::endl;
	//p[0] = 28;
	std::cout << "p[0]=" << p[0] << std::endl;
	return 0;*/
	
	//Cellule<4,3,int> c;
	/*ComplexeCubique<3,3,int> c;
	cout << c.estValide() << endl;
	c.~ComplexeCubique();
	
	ComplexeCubique<1,1,float>::builder();*/
	
        /*if(argc != 2)
	{
		cout << "Usage: " << argv[0] << " " << "descripteur" << endl;
		exit(EXIT_FAILURE);
	}
	
	ifstream fichier(argv[1]);
	if(fichier)
	{
		string input;
		getline(fichier, input);
		istringstream ligne(input);
		int dimensionComplexe;
		int dimensionPoint;
		ligne >> dimensionComplexe >> dimensionPoint;
		
		ComplexeCubique<dimensionComplexe,dimensionPoint,int> complexe;
		
		while(getline(fichier, input))
		{
			
		}
        }*/
	
	exit(EXIT_SUCCESS);
}
