#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
//#include "ComplexeCubique.h"
#include "Cellule.h"

//#include "testPoint.cpp"

#define DIMENSION_COMPLEXE 3
#define DIMENSION_POINTS 3
#define NOMBRE_0_CELLULES 10
#define NOMBRE_1_CELLULES 10
#define NOMBRE_2_CELLULES 1

#include "testPoint.cpp"

using namespace std;

int main(int argc, char** argv)
{
    /*
    //Test de Point
    vector<int> tab;
    tab.push_back(10);
    tab.push_back(14);
    tab.push_back(2);
    Point<3,int> point(tab);
    point[1] = 28;
    cout << point << endl;
    tab.~vector();
    */

    //Test de Cellule
    //ComplexeCubique<3,3,int> complexe;
    //complexe.creerCellule(new Point<3,int>());
    vector<Cellule<0>* > vec;
    vec.push_back(new Cellule<0>());
    vec.push_back(new Cellule<0>());
    Cellule<1> c3(vec);
    //(cellule.getBord())[1]->getPoint()[1] = 666;
    c3.~Cellule();


    //(cellule.getBord()[0])->getSommet()[0] = 999;
    //cout << point << endl;
    //cellule.~Cellule();
    /*if(complexe.trouverCellule(&cellule) != NULL)
        cout << "Found" << endl;
    else
        cout << "Not found" << endl;*/
    //complexe.~ComplexeCubique();




    exit(EXIT_SUCCESS);
/*

        if(argc != 2)
	{
		cout << "Usage: " << argv[0] << " " << "descripteur" << endl;
		exit(EXIT_FAILURE);
	}
	
	ifstream fichier(argv[1]);
	
	testPoint();

	if(fichier)
        {
		string input;
                getline(fichier,input);
                istringstream ligne(input);

                int bidon;
                ligne >> bidon;
                if(bidon != DIMENSION_COMPLEXE)
                {
                    cout << "Dimensions du complexe non concordantes : " << bidon << " != " << DIMENSION_COMPLEXE << endl;
                    exit(EXIT_FAILURE);
                }

                ligne >> bidon;
                if(bidon != DIMENSION_POINTS)
                {
                    cout << "Dimensions des points non concordantes : " << bidon << " != " << DIMENSION_POINTS << endl;
                    exit(EXIT_FAILURE);
                }

                getline(fichier, input);
                istringstream ligne2(input);

                ligne2 >> bidon;
                if(bidon != NOMBRE_0_CELLULES)
                {
                    cout << "Nombres de 0-cellules non concordants : " << bidon << " != " << NOMBRE_0_CELLULES << endl;
                    exit(EXIT_FAILURE);
                }

                ligne2 >> bidon;
                if(bidon != NOMBRE_1_CELLULES)
                {
                    cout << "Nombres de 1-cellules non concordants : " << bidon << " != " << NOMBRE_1_CELLULES << endl;
                    exit(EXIT_FAILURE);
                }

                ligne2 >> bidon;
                if(bidon != NOMBRE_2_CELLULES)
                {
                    cout << "Nombres de 2-cellules non concordants : " << bidon << " != " << NOMBRE_2_CELLULES << endl;
                    exit(EXIT_FAILURE);
                }

                //Créer le complexe
                ComplexeCubique<DIMENSION_COMPLEXE,DIMENSION_POINTS,int> complexe;

                for(int i = 0; i < NOMBRE_0_CELLULES; i++)
                {
                    //Lire et créer point
                    Point<DIMENSION_POINTS,int>* point = new Point<DIMENSION_POINTS,int>();
                    getline(fichier, input);
                    istringstream ligne3(input);
                    for(int j = 0; j < DIMENSION_POINTS; j++)
                    {
                        int coordonnee;
                        ligne3 >> coordonnee;
                        (*point)[j] = coordonnee;
                    }
                    //Ajouter 0-cellule au complexe
                    complexe.creerCellule(point);
                }

                for(int i = 0; i < NOMBRE_1_CELLULES; i++)
                {
                    //Lire et récupérer 0-cellules
                    //Ajouter 1-cellule au complexe attachée à son bord
                }

                for(int i = 0; i < NOMBRE_2_CELLULES; i++)
                {
                    //Lire et récupérer 1-cellules
                    //Ajouter 2-cellule au complexe attachée à son bord
                }

                complexe.~ComplexeCubique();
                fichier.~ifstream();


        }

        exit(EXIT_SUCCESS);*/
}
