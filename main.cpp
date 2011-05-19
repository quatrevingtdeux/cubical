
#include <QApplication>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "ComplexeCubique.h"
#include "Cellule.h"
#include "Viewer.h"
#include "Parser.h"

using namespace std;

int main(int argc, char** argv)
{
    ComplexeCubique<DIM_C,DIM_P,TYPE> complexe;

    /*Point<3,int> p1;
    p1[0] = 0;
    p1[1] = 0;
    p1[2] = 0;
    Point<3,int> p2;
    p2[0] = 0;
    p2[1] = 1;
    p2[2] = 0;
    complexe.creerCellule(&p1);
    complexe.creerCellule(&p2);

    vector<int> vecIndices;
    vecIndices.push_back(0);
    vecIndices.push_back(1);
    complexe.creerCellule<1>(vecIndices);*/

    if (argc == 2)
    {
        Parser parseCeFichier(complexe, argv[1]);
    }

    glutInit(&argc, argv);
    QApplication app(argc, argv);
    app.setApplicationName("Cubical");

    Viewer<3,3,int> viewer(&complexe);
    viewer.show();
    app.exec();

    complexe.~ComplexeCubique();

    return EXIT_SUCCESS;
}
