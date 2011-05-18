
#include <iostream>
#include <string>
#include <stdlib.h>
#include "ComplexeCubique.h"
#include "Cellule.h"

//#include "Parser.h"

using namespace std;

int main(int argc, char** argv)
{
    ComplexeCubique<3,3,int> comp;
    comp.creerCellule(new Point<3,int>());
    comp.getCellule(0,0);
    comp.~ComplexeCubique();
}
