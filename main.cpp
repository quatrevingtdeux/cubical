#include <iostream>
#include "Point.h"
#include "ComplexeCubique.h"
#include "Cellule.h"

using namespace std;

int main()
{
	/*int tab[5] = {31,32,33,34,35};
	Point<5,int> p(tab);
	std::cout << "Dimension=" << p.getDimension() << std::endl;
	//p[0] = 28;
	std::cout << "p[0]=" << p[0] << std::endl;
	return 0;*/
	
	//Cellule<4,3,int> c;
	ComplexeCubique<3,3,int> c;
	cout << c.estValide() << endl;
	c.~ComplexeCubique();
	return 0;
}

